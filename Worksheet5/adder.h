#pragma once

#ifdef _WIN32
#ifdef mathsEXPORTS
#define MATHS_API __declspec(dllexport)
#else
#define MATHS_API __declspec(dllimport)
#endif
#else
#define MATHS_API
#endif

extern "C" MATHS_API int add(int a, int b);
