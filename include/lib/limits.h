#ifndef MCC_LIB_LIMITS_H
#define MCC_LIB_LIMITS_H

#define CHAR_BIT 8            /* 8 bits */

#define SCHAR_MIN  (-128)     /* 8 bits */
#define SCHAR_MAX  127        /* 8 bits */
#define UCHAR_MAX  255        /* 8 bits */

#if __CHAR_UNSIGNED__
#define CHAR_MIN 0            /* 8 bits */
#define CHAR_MAX UCHAR_MAX    /* 8 bits */
#else
#define CHAR_MIN SCHAR_MIN    /* 8 bits */
#define CHAR_MAX SCHAR_MAX    /* 8 bits */
#endif

#define SHRT_MIN  (-32768)        /* 16 bits */
#define SHRT_MAX  32767           /* 16 bits */
#define USHRT_MAX 65535           /* 16 bits */

#define INT_MIN   (-2147483648)   /* 32 bits */
#define INT_MAX   2147483647      /* 32 bits */
#define UINT_MAX  4294967295U     /* 32 bits */

#define LONG_MIN  (-9223372036854775807L - 1) /* 64 bits */
#define LONG_MAX  9223372036854775807L       /* 64 bits */
#define ULONG_MAX 18446744073709551615UL     /* 64 bits */

#define LLONG_MIN  (-9223372036854775807LL - 1) /* 64 bits */
#define LLONG_MAX  9223372036854775807LL       /* 64 bits */
#define ULLONG_MAX 18446744073709551615ULL     /* 64 bits */

#define MB_LEN_MAX 16          /* max bytes in multibyte char */


#endif // MCC_LIB_LIMITS_H

