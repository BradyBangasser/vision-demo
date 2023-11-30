#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <fmt/format.h>
#include <wpi/StringExtras.h>

// Creates a new error, logs it, and continues
template <typename ...Args>
void ParseError(fmt::string_view format, Args &&...args);

// Creates a new Fatal error and logs it
template <typename ...Args>
void ParseFatalError(fmt::string_view format, Args &&...args);

#endif