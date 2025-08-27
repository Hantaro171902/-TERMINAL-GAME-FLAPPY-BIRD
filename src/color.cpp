#include "color.hpp"
#include <string>

std::string getTextColor(TextColor color) {
    return "\033[" + std::to_string(color) + "m";
}

std::string getResetColor() {
    return "\033[0m";
}