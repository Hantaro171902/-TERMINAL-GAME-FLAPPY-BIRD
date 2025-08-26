#include "utils.hpp"
#include <iostream>

using namespace std;

void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void moveCursor(int x, int y) {
    cout << "\033[" << y << ";" << x << "H";
}

void hideCursor() {
    cout << "\033[?25l";
}

void showCursor() {
    cout << "\033[?25h";
}
