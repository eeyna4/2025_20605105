#pragma once

#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef maths_STATIC
#define MATHSLIB_API
#else
#ifdef maths_EXPORTS
#define MATHSLIB_API __declspec(dllexport)
#else
#define MATHSLIB_API __declspec(dllimport)
#endif
#endif
#else
#define MATHSLIB_API
#endif

MATHSLIB_API int add(int a, int b);
