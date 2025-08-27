#pragma once
#include <string>

// ANSI color constants for Linux/Unix
enum TextColor {
    DEFAULT = 0,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    GRAY = 30,
    CYAN = 36,
    WHITE = 37,
    BG_GREEN = 42,
    BRIGHT_RED = 91,
    BRIGHT_GREEN = 92,
    BRIGHT_YELLOW = 93,
    BRIGHT_BLUE = 94,
    BRIGHT_MAGENTA = 95,
    BRIGHT_CYAN = 96,
    BRIGHT_WHITE = 97
};

// A struct to hold both a character and its color
struct Pixel {
    char ch;
    TextColor color;
};

std::string getTextColor(TextColor color);
std::string getResetColor();