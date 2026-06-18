#ifndef CPP_CONCEPTS_ODR_INLINE_VS_STATIC_VS_NAMESPACE_H
#define CPP_CONCEPTS_ODR_INLINE_VS_STATIC_VS_NAMESPACE_H

#include <iostream>

/**
 * non-inlined.
 * If multiple Translation Units (TU) include main.h,
 * linker fails because duplicate function names exist.
 * Fails the One Definition Rule (ODR)
*/
// void f() {
//     std::cout << "cheese" << std::endl;
// }

/**
 * inlined.
 * TUs including main.h share reference to f, passes ODR.
 * Note that inline keyword does not guarantee f is
 * inlined, compiler may choose otherwise.
 */
inline void f() {
    std::cout << "cheese" << std::endl;
}

/**
 * static.
 * TUs including main.h each own a separate, distinct f, passes ODR.
 */
// static void f() {
//     std::cout << "cheese" << std::endl;
// }

/**
 * anonymous namespace.
 * TUs including main.h each own a separate, distinct f, passes ODR.
 * Preferred way to hide helpers in one .cpp
 */
// namespace {
//  void f() {
//   std::cout << "cheese" << std::endl;
//  }
// }

#endif //CPP_CONCEPTS_ODR_INLINE_VS_STATIC_VS_NAMESPACE_H