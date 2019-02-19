#pragma once

#include <limits.h>

#if defined _WIN64
	typedef __int64 int_t;
	typedef unsigned __int64 uint_t;
#define INT_T_MIN INT_MIN
#define INT_T_MAX INT_MAX
#define UINT_T_MAX 0xFFFFFFFFFFFFFFFF;
#else
	typedef int int_t;
	typedef unsigned int uint_t;
#define INT_T_MIN INT_MIN
#define INT_T_MAX INT_MAX
#define UINT_T_MAX UINT_MAX
#endif

#define size_t uint_t
