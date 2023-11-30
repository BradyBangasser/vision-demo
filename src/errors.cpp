#include "errors.hpp"

// Add insults to this
void InternalParseError(bool fatal, fmt::string_view format, fmt::format_args args) {
    fmt::vprint(stderr, format, args);
    fmt::print(stderr, "Warning: Insults not implemented yet");
    fmt::print(stderr, "\n");
    
    if (fatal) {
        exit(1);
    }
} // InternalParseError

template <typename ...Args>
void ParseFatalError(fmt::string_view format, Args &&...args) {
    InternalParseError(true, format, args);
}

template <typename ...Args>
void ParseError(fmt::string_view format, Args &&...args) {
    InternalParseError(false, format, args);
}