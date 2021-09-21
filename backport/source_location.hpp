// SPDX-FileCopyrightText: 2021 Robin Lindén <dev@robinlinden.eu>
//
// SPDX-License-Identifier: BSD-2-Clause

#ifndef BACKPORT_SOURCE_LOCATION_HPP_
#define BACKPORT_SOURCE_LOCATION_HPP_

#include <cstdint>

namespace backport {

// https://en.cppreference.com/w/cpp/utility/source_location
struct source_location {
    constexpr source_location() noexcept = default;
    constexpr source_location(source_location const &other) :
            line_{other.line_},
            column_{other.column_},
            file_name_{other.file_name_},
            function_name_{other.function_name_} {}
    constexpr source_location(source_location &&other) noexcept :
            line_{other.line_},
            column_{other.column_},
            file_name_{other.file_name_},
            function_name_{other.function_name_} {}

    // Not consteval since this needs to work in codebases not using C++20.
    static constexpr source_location current(
            std::uint_least32_t line = __builtin_LINE(),
#ifndef __GNUC__ // GCC doesn't support column numbers.
            std::uint_least32_t column = __builtin_COLUMN(),
#else
            std::uint_least32_t column = 0,
#endif
            char const *file_name = __builtin_FILE(),
            char const *function_name = __builtin_FUNCTION()) noexcept {
        return {line, column, file_name, function_name};
    }

    constexpr std::uint_least32_t line() const noexcept { return line_; }
    constexpr std::uint_least32_t column() const noexcept { return column_; }
    constexpr char const *file_name() const noexcept { return file_name_; }
    constexpr char const *function_name() const noexcept { return function_name_; }

private:
    std::uint_least32_t line_{0};
    std::uint_least32_t column_{0};
    char const *file_name_{nullptr};
    char const *function_name_{nullptr};

    constexpr source_location(
            std::uint_least32_t line,
            std::uint_least32_t column,
            char const *file_name,
            char const *function_name) noexcept :
            line_{line},
            column_{column},
            file_name_{file_name},
            function_name_{function_name} {}
};

} // namespace backport

#endif
