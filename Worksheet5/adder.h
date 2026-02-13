#pragma once

/**
 * @file adder.h
 * @brief Public API for the add function.
 */

#ifdef _WIN32
#ifdef mathsEXPORTS
#define MATHS_API __declspec(dllexport)
#else
#define MATHS_API __declspec(dllimport)
#endif
#else
#define MATHS_API
#endif

 /**
  * @brief Adds two integers.
  * @param a First integer.
  * @param b Second integer.
  * @return The sum a + b.
  */
extern "C" MATHS_API int add(int a, int b);
