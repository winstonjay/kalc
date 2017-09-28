#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define BSIZE 128 // buffer size.
#define NONE  -1
#define EOS   '\0'

#define NUM   256
#define ID    257
#define DONE  248

typedef struct {
    int tok;
    int toktype;
} Scanner;

int tok; // will be more than single chars in future.
int result = 0;
int tokenval;
bool numbertok;

int scanner_next();

int parse();
int expr();
int term();
int exponent();
int factor();
void match(int t);

void error();

int history[2] = {-1, -1};

// Run basic REPL.
int main() {
    while (true) {
        printf(">>> ");
        result = parse();
        history[1] = history[0];
        history[0] = result;
        printf("%d\n", result);
    }
}

int parse() {
    tok = scanner_next();
    result = expr();
    return result;
}

int expr() {
    int result = term();
    while (true) {
        switch (tok) {
        case '+':
            match('+');
            result += term();
            break;
        case '-':
            match('-'); 
            result -= term();
            break;
        default:
            return result;
        }
    }
}

int term() {
    int result = exponent();
    while (true) {
        switch (tok) {
        case '*':
            match('*'); 
            result *= exponent();
            break;
        case '/':
            match('/'); 
            result /= exponent();
            break;
        case '%':
            match('%'); 
            result %= exponent();
            break;
        default:
            return result;
        }
    }
}

int exponent() {
    int result = factor();
    while (true) {
        switch (tok) {
        case '^':
            match('^');
            int n = factor();
            for (int i = 1; i < n; i++) {
                result *= result;
            }
            break;
        default:
            return result;
        }
    }
}

int factor() {
    int result;
    switch (tok) {
    case '?':
        match('?');
        result = history[0];
        return result;
    case '(':
        match('(');      
        result = expr();
        match(')');
        return result;
    case '-':
        match('-');
        return - expr();
    default:
        if (numbertok) {
            result = tok;
            match(tok);
            return result;
        } else {
            error("Unkown Atom.");
            return NONE;
        }
    }
}

void match(int t) {
    if (tok == t) {
        tok = scanner_next();
    } else {
        error("Parse Syntax error");
    }
}

void error(char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

// scannernext : Lexical analyzer, return the next token found.
int scanner_next() {
    int t = getchar();
    // Each expression can be just one line.
    while (t != '\n' && t != '\r') {
        if (t == ' ' || t == '\t') {
            /* skip whitespace; */
            t = getchar();
            continue; 
        } else if (isdigit(t)) {
            /* Read number. */
            tokenval = t - '0';
            t = getchar();
            while (isdigit(t)) {
                tokenval = tokenval*10 + (t - '0');
                t = getchar();
            }
            ungetc(t, stdin);
            numbertok = true;
            return tokenval;
         } else {
            /* operator or could be error handled later in parser. */
            numbertok = false;
            tokenval = NONE;
            return t;
        }
        t = getchar(); // Always advance the scanner.
    } // endwhile
    return DONE;
}