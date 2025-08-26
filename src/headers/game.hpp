#pragma once 
#include "bird.hpp"
#include "pipe.hpp"

class Game {
private:
    Bird bird;
    Pipe pipe1, pipe2;
    int score;
    bool gameOver;
    int rows, cols;

public:
    Game(int rows, int cols);
    void run();
    void processInput(char input);
    void update();
    void render();
    void reset();
}