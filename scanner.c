#include "kalc.h"

// typedef struct {
//     int    tok;        /* currrent token. */
//     int    
// } Token;

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
        t = getchar(); /* Always advance the scanner. */
    }
    return DONE;
}