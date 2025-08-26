#include "utils.hpp"
#include <iostream>

using namespace std;

Utils utils; // single definition here

void Utils::clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void Utils::moveCursor(int x, int y) {
    cout << "\033[" << y << ";" << x << "H";
}

void Utils::hideCursor() {
    cout << "\033[?25l";
}

void Utils::showCursor() {
    cout << "\033[?25h";
}
