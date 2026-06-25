/**
 * [[nodiscard]] specifier on function return type helps disambiguate a function's intended purpose.
 */

#include <vector>

template <typename T>
struct Box {
    std::vector<T> v;

    // bool empty() {
    //     return v.empty();
    // }
    [[nodiscard]] bool empty() {
        return v.empty();
    }
};

int main() {
    Box box{std::vector{1, 2, 3}};

    // box.empty();    // incorrectly interpreted as a function to empty box
    bool is_empty = box.empty();

    return 0;
}

