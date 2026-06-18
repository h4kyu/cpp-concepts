#include <iostream>
#include <vector>

/**
 * References produce aliases.
 * Expressions are not references.
 * lvalue expressions designate objects.
 * A function that returns T& produces an lvalue expression designating a T object.
 *
 * References are handled under the hood with hidden pointers.
 */

std::vector<int> v{1, 2, 3, 4};

int main() {
    int x = v[0];
    /**
     * v[0] calls std::vector<int>::operator[](std::size_t) -> int&.
     * Critically, expressions themselves are not references.
     * So v[0] is an lvalue expression designating the first element of v.

    mov     esi, 0
    mov     edi, OFFSET FLAT:"v"
    call    "std::vector<int, std::allocator<int>>::operator[](unsigned long)"  <-- stores &v[0] in rax

     * The reference to v[0] is stored as a ptr in rax.
     * The pointer is dereferenced and its value is stored in x.

    mov     eax, DWORD PTR [rax]       <-- loads v[0] into eax
    mov     DWORD PTR [rbp-4], eax     <-- stores v[0] at memory location of x
     */

    int& r = v[0];
    /**
     * r is an lvalue reference bound to the first int object in v.
     * r aliases v[0], whos reference is handled by hidden pointers.

    mov     esi, 0
    mov     edi, OFFSET FLAT:"v"
    call    "std::vector<int, std::allocator<int>>::operator[](unsigned long)"  <-- stores &v[0] in rax

     * ptr &v[0] is stored at stack slot for r, ie. r is bound to v[0].

    mov     QWORD PTR [rbp-16], rax     <-- stores &v[0] at stack slot used for reference r
     */
    r = 5;
    /**
    mov     rax, QWORD PTR [rbp-16]  <-- loads &v[0] into rax
    mov     DWORD PTR [rax], 5       <-- stores 5 in int object v[0] (at memory location of v[0]), referred to by r
     */
}
