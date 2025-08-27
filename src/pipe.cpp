#include "pipe.hpp"
#include "game.hpp"
#include "color.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

Pipe::Pipe() : opening_height(0.0f), center(0) {}

Pipe::Pipe(int initial_center, float initial_height) : opening_height(initial_height), center(initial_center) {}

void Pipe::refresh(int& score) {
    if (center + PIPE_RADIUS < 0) {
        center = NUM_COLS + PIPE_RADIUS;
        opening_height = std::rand() / static_cast<float>(RAND_MAX) * 0.5f + 0.25f;
        score++;
    }
    center--;
}

int Pipe::get_orow(int top) const {
    return opening_height * (NUM_ROWS - 1) - (top ? 1 : -1) * OPENING_WIDTH / 2;
}

int Pipe::get_center() const {
    return center;
}

void Pipe::draw(std::vector<std::vector<Pixel>>& screen, int ceiling_row, int floor_row) const {
    int upper_terminus, lower_terminus;

    // Vertical part of upper pipe
    for (int i = ceiling_row + 1; i < get_orow(1); i++) {
        if (center - PIPE_RADIUS >= 0 && center - PIPE_RADIUS < NUM_COLS)
            screen[i][center - PIPE_RADIUS] = { '|', BG_GREEN };
        if (center + PIPE_RADIUS >= 0 && center + PIPE_RADIUS < NUM_COLS)
            screen[i][center + PIPE_RADIUS] = { '|', BG_GREEN };
    }
    upper_terminus = get_orow(1);

    // Horizontal part of upper pipe
    for (int j = -PIPE_RADIUS; j <= PIPE_RADIUS; j++) {
        if (center + j >= 0 && center + j < NUM_COLS)
            screen[upper_terminus][center + j] = { '=', BG_GREEN };
    }

    // Vertical part of lower pipe
    for (int i = floor_row - 1; i > get_orow(0); i--) {
        if (center - PIPE_RADIUS >= 0 && center - PIPE_RADIUS < NUM_COLS)
            screen[i][center - PIPE_RADIUS] = { '|', BG_GREEN };
        if (center + PIPE_RADIUS >= 0 && center + PIPE_RADIUS < NUM_COLS)
            screen[i][center + PIPE_RADIUS] = { '|', BG_GREEN };
    }
    lower_terminus = get_orow(0);

    // Horizontal part of lower pipe
    for (int j = -PIPE_RADIUS; j <= PIPE_RADIUS; j++) {
        if (center + j >= 0 && center + j < NUM_COLS)
            screen[lower_terminus][center + j] = { '=', BG_GREEN };
    }
}