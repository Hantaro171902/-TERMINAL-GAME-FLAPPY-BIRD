#pragma once

#include <string>
#include <vector>

class Pipe;

class Bird {
private:
    int width, height;
    float velocity;
    float gravity;
    float flapStrength;

public:
    Bird(int startX, int startY);
    void flap();
    void update();
    void draw() const;
    int getRow() const;
    int getCol() const;
};