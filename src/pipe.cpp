#include "pipe.hpp"
#include "utils.hpp"
#include <iostream>

using namespace std;

Utils utils;

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
    utils.moveCursor(center - width / 2, 1);
    for (int r = 1; r < openingHeight - 3; r++) {
        utils.moveCursor(center - width / 2, r);
        cout << "||";
        utils.moveCursor(center + width / 2, r);
        cout << "||";
    }
    for (int r = openingHeight + 3; r < screenRows; r++) {
        utils.moveCursor(center - width / 2, r);
        cout << "||";
        utils.moveCursor(center + width / 2, r);
        cout << "||";
    }
}

bool Pipe::collidesWith(const Bird& bird) const {
    // int birdCol = bird.getCol();
    // int birdRow = bird.getRow();
    // return (birdCol >= center - width / 2 && birdCol <= center + width / 2 &&
    //         birdRow >= getOpeningTopRow() && birdRow <= getOpeningBottomRow());
    if (bird.getCol() == center) {
        if (bird.getRow() < openingHeight - 3 || bird.getRow() > openingHeight + 3) {
            return true;
        }
    }
    return false;
}

int Pipe::getCenter() const {
    return center;
}



