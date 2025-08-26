#include "pipe.hpp"
#include "utils.hpp"
#include <iostream>

using namespace std;

Pipe::Pipe(int startCols, int rows, int cols) 
    : center(startCols), screenRows(rows), screenCols(cols), width(6) {
    openingHeight = rand() % (rows - 10) + 5;
}

void Pipe::update() {
    center--;
    if (center < 0) {
        center = screenCols;
        openingHeight = rand() % (screenRows - 10) + 5;
    }
}

void Pipe::draw() const {
    Utils::moveCursor(center - width / 2, 1);
    for (int r = 1; r < openingHeight - 3; r++) {
        Utils::moveCursor(center - width / 2, r);
        cout << "||";
        Utils::moveCursor(center + width / 2, r);
        cout << "||";
    }
    for (int r = openingHeight + 3; r < screenRows; r++) {
        Utils::moveCursor(center - width / 2, r);
        cout << "||";
        Utils::moveCursor(center + width / 2, r);
        cout << "||";
    }
}

bool 