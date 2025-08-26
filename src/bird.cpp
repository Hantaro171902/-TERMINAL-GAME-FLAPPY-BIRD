#include "bird.hpp"
#include "utils.hpp"
#include <iostream>

using namespace std;


Bird::Bird(int startX, int startY) 
    : width(startX), height(startY), velocity(0), gravity(0.3f), flapStrength(-1.2f) {
    // Initialize bird position
}

void Bird::flap() {
    velocity = flapStrength;
}

void Bird::update() {
    velocity += gravity;
    width += (int)velocity;
    if (width < 1) {
        width = 1;
    }

}

void Bird::draw() const {
    moveCursor(width, height);
    cout << "🐦";
}

int Bird::getRow() const {
    return width;
}

int Bird::getCol() const {
    return height;
}