#include "kalc.h"

int result = 0;
int history[2] = {NONE};

// Run basic REPL.
int main() {
    while (true) {
        printf("klc> ");
        result = calculate();
        printf("%d\n", result);
    }
}

int calculate() {
    tok = scanner_next();
    while (tok != DONE) {
        result = expr();
        history[0] = result;
        if (tok == ',') {
            match(',');
            printf("%d, ", result);
        } else {
            break;
        }
    }
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