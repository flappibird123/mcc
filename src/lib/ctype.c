#include "lib/ctype.h"


/* Character property bits */
#define _U 0x01  /* Uppercase */
#define _L 0x02  /* Lowercase */
#define _D 0x04  /* Digit */
#define _S 0x08  /* Space */
#define _P 0x10  /* Punctuation */
#define _X 0x20  /* Hex digit */

/* Lookup table for ASCII characters 0..255 */
static const unsigned char _ctype_table[256] = {
    /* 0x00 - 0x0F */
    0,0,0,0,0,0,0,0,0, _S, _S,0,0, _S,0,0,
    /* 0x10 - 0x1F */
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    /* 0x20 - 0x2F: ' ' ! " # $ % & ' ( ) * + , - . / */
    _S, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P,
    /* 0x30 - 0x39: '0'-'9' */
    _D | _X, _D | _X, _D | _X, _D | _X, _D | _X, _D | _X, _D | _X, _D | _X, _D | _X, _D | _X,
    /* 0x3A - 0x40: : ; < = > ? @ */
    _P, _P, _P, _P, _P, _P, _P,
    /* 0x41 - 0x46: A-F */
    _U | _X, _U | _X, _U | _X, _U | _X, _U | _X, _U | _X,
    /* 0x47 - 0x5A: G-Z */
    _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U,
    /* 0x5B - 0x60: [ \ ] ^ _ ` */
    _P, _P, _P, _P, _P, _P,
    /* 0x61 - 0x66: a-f */
    _L | _X, _L | _X, _L | _X, _L | _X, _L | _X, _L | _X,
    /* 0x67 - 0x7A: g-z */
    _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L,
    /* 0x7B - 0x7E: { | } ~ */
    _P, _P, _P, _P,
    /* 0x7F: DEL */
    0,
    /* 0x80 - 0xFF: Extended ASCII (all 0 for simplicity) */
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

/* --- Classification functions --- */

int isalpha(int c)  { 
    return _ctype_table[(unsigned char)c] & (_U | _L); 
}

int isdigit(int c)  {
    return _ctype_table[(unsigned char)c] & _D; 
}

int isalnum(int c)  {
    return _ctype_table[(unsigned char)c] & (_U | _L | _D); 
}

int isspace(int c)  { 
    return _ctype_table[(unsigned char)c] & _S; 
}

int isupper(int c)  { 
    return _ctype_table[(unsigned char)c] & _U; 
}

int islower(int c)  { 
    return _ctype_table[(unsigned char)c] & _L; 
}

int ispunct(int c)  { 
    return _ctype_table[(unsigned char)c] & _P; 
}

int isxdigit(int c) { 
    return _ctype_table[(unsigned char)c] & (_D | _X); 
}

/* --- Conversion functions --- */

int toupper(int c) {
    if (islower(c)) { 
        return c - ('a' - 'A');
    }
    return c;
}

int tolower(int c) {
    if (isupper(c)) {
        return c + ('a' - 'A');
    }
    return c;
}
