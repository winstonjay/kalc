#ifndef kalc_h
#define kalc_h

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

int tok; // will be more than single chars in future.
int tokenval;
bool numbertok;

/* Scanner functions */
int scanner_next();

/* Parser functions */
int calculate(), expr(), term(), exponent(), factor();
void match(int t), error();

#endif