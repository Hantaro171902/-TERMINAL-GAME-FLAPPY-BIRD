#include "bird.hpp"
#include "pipe.hpp"
#include "game.hpp"  // For constants like GRAV, V0, FLAPPY_COL, etc.

Bird::Bird() : h0(NUM_ROWS / 2), t(0) {}

void Bird::update(bool jump) {
    if (jump) {
        h0 = get_position();
        t = 0;
    } else {
        t++;
    }
}

int Bird::get_position() const {
    return h0 + V0 * t + 0.5 * GRAV * t * t;
}

bool Bird::crashed(int ceiling, int floor) const {
    int h = get_position();
    return h <= ceiling || h >= floor;
}

bool Bird::crashed_into(const Pipe& p) const {
    if (FLAPPY_COL >= p.get_center() - PIPE_RADIUS - 1 &&
        FLAPPY_COL <= p.get_center() + PIPE_RADIUS + 1) {
        if (get_position() >= p.get_orow(1) + 1 &&
            get_position() <= p.get_orow(0) - 1) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

void Bird::draw(std::vector<std::string>& screen, int frame) const {
    int h = get_position();
    if (GRAV * t + V0 > 0) {  // Going down
        if (h >= 0 && h < NUM_ROWS && FLAPPY_COL - 1 >= 0 && FLAPPY_COL - 1 < NUM_COLS)
            screen[h][FLAPPY_COL - 1] = '\\';
        if (h - 1 >= 0 && h - 1 < NUM_ROWS && FLAPPY_COL - 2 >= 0 && FLAPPY_COL - 2 < NUM_COLS)
            screen[h - 1][FLAPPY_COL - 2] = '\\';
        if (h >= 0 && h < NUM_ROWS && FLAPPY_COL >= 0 && FLAPPY_COL < NUM_COLS)
            screen[h][FLAPPY_COL] = '0';
        if (h >= 0 && h < NUM_ROWS && FLAPPY_COL + 1 >= 0 && FLAPPY_COL + 1 < NUM_COLS)
            screen[h][FLAPPY_COL + 1] = '/';
        if (h - 1 >= 0 && h - 1 < NUM_ROWS && FLAPPY_COL + 2 >= 0 && FLAPPY_COL + 2 < NUM_COLS)
            screen[h - 1][FLAPPY_COL + 2] = '/';
    } else {  // Going up, flap wings
        // Left wing
        if (frame % 6 < 3) {
            if (h >= 0 && h < NUM_ROWS && FLAPPY_COL - 1 >= 0 && FLAPPY_COL - 1 < NUM_COLS)
                screen[h][FLAPPY_COL - 1] = '/';
            if (h + 1 >= 0 && h + 1 < NUM_ROWS && FLAPPY_COL - 2 >= 0 && FLAPPY_COL - 2 < NUM_COLS)
                screen[h + 1][FLAPPY_COL - 2] = '/';
        } else {
            if (h >= 0 && h < NUM_ROWS && FLAPPY_COL - 1 >= 0 && FLAPPY_COL - 1 < NUM_COLS)
                screen[h][FLAPPY_COL - 1] = '\\';
            if (h - 1 >= 0 && h - 1 < NUM_ROWS && FLAPPY_COL - 2 >= 0 && FLAPPY_COL - 2 < NUM_COLS)
                screen[h - 1][FLAPPY_COL - 2] = '\\';
        }
        // Body
        if (h >= 0 && h < NUM_ROWS && FLAPPY_COL >= 0 && FLAPPY_COL < NUM_COLS)
            screen[h][FLAPPY_COL] = '0';
        // Right wing
        if (frame % 6 < 3) {
            if (h >= 0 && h < NUM_ROWS && FLAPPY_COL + 1 >= 0 && FLAPPY_COL + 1 < NUM_COLS)
                screen[h][FLAPPY_COL + 1] = '\\';
            if (h + 1 >= 0 && h + 1 < NUM_ROWS && FLAPPY_COL + 2 >= 0 && FLAPPY_COL + 2 < NUM_COLS)
                screen[h + 1][FLAPPY_COL + 2] = '\\';
        } else {
            if (h >= 0 && h < NUM_ROWS && FLAPPY_COL + 1 >= 0 && FLAPPY_COL + 1 < NUM_COLS)
                screen[h][FLAPPY_COL + 1] = '/';
            if (h - 1 >= 0 && h - 1 < NUM_ROWS && FLAPPY_COL + 2 >= 0 && FLAPPY_COL + 2 < NUM_COLS)
                screen[h - 1][FLAPPY_COL + 2] = '/';
        }
    }
}