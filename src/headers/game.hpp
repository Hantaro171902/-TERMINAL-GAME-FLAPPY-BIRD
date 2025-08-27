#pragma once 
#include "bird.hpp"
#include "pipe.hpp"
#include "color.hpp"
#include <vector>
#include <string>

// Global constants
const float GRAV = 0.05f;
const float V0 = -0.5f;
const int NUM_ROWS = 24;
const int NUM_COLS = 80;
const int PIPE_RADIUS = 3;
const int OPENING_WIDTH = 7;
const int FLAPPY_COL = 10;
const float TARGET_FPS = 24;
const float START_TIME_SEC = 3.0f;
const int PROG_BAR_LEN = 76;
const int PROG_BAR_ROW = 22;
const int SCORE_START_COL = 62;

class Game {
private:
    Bird bird;
    Pipe p1, p2;
    int frame;
    int score;
    int best_score;
    // std::vector<std::string> screen;
    std::vector<std::vector<Pixel>> screen;
public:
    Game();
    void run();
    void draw(int ceil_row, int floor_row, char ch, int spacing, int col_start);
    bool crashed() const;
    void draw_score();
    void render() const;
    void splash_screen();
    int failure_screen();
    // void processInput(char input);
    // void update();
    // void render();
    // void reset();
};