#ifndef _LIMITS_H_
#define _LIMITS_H_

#define CHAR_BIT   sizeof(char)
#define SCHAR_MIN (-128)
#define SCHAR_MAX ( 127)
#define UCHAR_MAX ( 255)

#define SHRT_BIT   sizeof(short)
#define SSHRT_MIN (-32768)
#define SSHRT_MAX ( 32767)
#define USHRT_MAX ( 65535)

#define LONG_BIT   sizeof(long)
#define SLONG_MAX (9223372036854775807L)
#define SLONG_MIN (-SLONG_MAX - 1L)
#define ULONG_MAX (4294967295UL)

#define INT_BIT   sizeof(int)
#define INT_MAX  (2147483647)
#define INT_MIN  (-INT_MAX - 1)
#define UINT_MAX (4294967295U)

#define LLONG_BIT    sizeof(long long)
#define LLONG_MAX   (9223372036854775807LL)
#define LLONG_MIN   (-LLONG_MAX - 1LL)
#define ULLONG_MAX  (18446744073709551615ULL)

#endif