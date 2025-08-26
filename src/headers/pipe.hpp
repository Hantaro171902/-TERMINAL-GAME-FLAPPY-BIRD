#pragma once
#include "bird.hpp"

class Pipe {
private:
    int center;
    float openingHeight; // As a fraction of the console height
    // static const int PIPE_RADIUS = 3;
    // static const int NUM_ROWS = 24;
    // static const int NUM_COLS = 80;
    int width;
    int screenRows, screenCols;

public:
    Pipe(int center, float openingHeight);
    void update();
    void draw() const;
    bool collidesWith(const Bird& bird) const;
    int getCenter() const;
}

