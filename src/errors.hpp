#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <fmt/format.h>
#include <wpi/StringExtras.h>

// Add insults to this
void _internalParseError(bool fatal, fmt::string_view format, fmt::format_args args) {
    fmt::vprint(stderr, format, args);
    fmt::print(stderr, "Warning: Insults not implemented yet");
    fmt::print(stderr, "\n");
    
    if (fatal) {
        exit(1);
    }
} // _internalParseError

template <typename ...Args>
void ParseFatalError(fmt::string_view format, Args &&...args) {
    _internalParseError(true, format, fmt::make_format_args(args...));
}

template <typename ...Args>
void ParseError(fmt::string_view format, Args &&...args) {
    _internalParseError(false, format, fmt::make_format_args(args...));
}

#endif