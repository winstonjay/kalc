#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define BSIZE 128 // buffer size.
#define NONE  -1
#define EOS   '\0'

#define NUM   256 
#define DIV   257
#define MOD   258
#define ID    259
#define DONE  260

int tok; // will be more than single chars in future.
int result = 0;
int tokenval = NONE;

int lexan();
int parse();
int expr();
int term();
int factor();
void match(int t);
void error();

// Run basic REPL.
int main() {
    while (true) {
        printf(">>> ");
        result = parse();
        printf("%d\n", result);
    }
}



int parse() {
    tok = lexan();
    result = expr();
    return result;
}

int expr() {
    int result = term();
    while (true) {
        switch (tok) {
        case '+':
            match('+');
            result = result + term();
            break;
        case '-':
            match('-'); 
            result = result - term();
            break;
        default:
            return result;
        }
    }
}

int term() {
    int result = factor();
    while (true) {
        switch (tok) {
        case '*':
            match('*'); 
            result = result * factor();
            break;
        case '/':
            match('/'); 
            result = result / factor();
            break;
        default:
            return result;
        }
    }
}


int factor() {
    int result = NONE;
    switch (tok) {
    case NUM:
        match(NUM);
        return tokenval;
    case '(':
        match('(');      
        result = expr();
        match(')');
        return result;
    default:
        error("Unkown Atom.");
        return NONE;
    }
}

void match(int t) {
    if (tok == t) {
        tok = scanner();
        if (tok < 256) {
            char c = tok;
            printf("{OP:  '%c'}\n", c);
        } else if (tok == NONE) {
            printf("{None}\n");
        } else {
            printf("{NUM: '%d'}\n", tokenval);
        }
    } else {
        error("Parse Syntax error");
    }
}

void error(char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

// scannernext : Lexical analyzer, return the next token found.
int scannernext() {
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
            return NUM;
         } else if (t == '(' || t == ')' || t == ';' ||
                    t == '+' || t == '-' || t == '*' || t == '/') {
            /* single symbol 
            could be error, handled later in the parser. */
            tokenval = NONE;
            return t;
        } else {
            error("Syntax error");
            return NONE;
        }
        t = getchar(); // Always advance the scanner.
    } // endwhile
    return DONE;
}