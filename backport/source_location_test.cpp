#include "backport/source_location.hpp"

#include <iostream>
#include <string>

template<typename T>
bool check(T expected, T actual, char const *what) {
    if (expected == actual) {
        return true;
    }

    std::cout << "Incorrect " << what << ", expected " << expected << ", but got " << actual << '\n';
    return false;
}

int main() {
    auto loc = backport::source_location::current();

    constexpr std::uint_least32_t expected_line{17};
    // GCC doesn't support column numbers.
#ifndef __GNUC__
    constexpr std::uint_least32_t expected_column{43};
#else
    constexpr std::uint_least32_t expected_column{0};
#endif
    std::string const expected_file_name{"backport/source_location_test.cpp"};
    std::string const expected_function_name{"main"};

    bool success{true};
    success &= check(expected_line, loc.line(), "line");
    success &= check(expected_column, loc.column(), "column");
    success &= check(expected_file_name, std::string{loc.file_name()}, "file_name");
    success &= check(expected_function_name, std::string{loc.function_name()}, "function_name");
    return success ? 0 : 1;
}
