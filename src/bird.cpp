#include "bird.hpp"
#include "pipe.hpp"
#include "color.hpp"
#include "game.hpp"

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

void Bird::draw(std::vector<std::vector<Pixel>>& screen, int frame) const {
    int h = get_position();

    if (h < 0 || h >= NUM_ROWS) return;

    if (GRAV * t + V0 > 0) { // Going down
        if (h >= 0 && h < NUM_ROWS && FLAPPY_COL - 1 >= 0 && FLAPPY_COL - 1 < NUM_COLS)
            screen[h][FLAPPY_COL - 1] = { '\\', BRIGHT_YELLOW };
        if (h - 1 >= 0 && h - 1 < NUM_ROWS && FLAPPY_COL - 2 >= 0 && FLAPPY_COL - 2 < NUM_COLS)
            screen[h - 1][FLAPPY_COL - 2] = { '\\', BRIGHT_YELLOW };
        if (h >= 0 && h < NUM_ROWS && FLAPPY_COL >= 0 && FLAPPY_COL < NUM_COLS)
            screen[h][FLAPPY_COL] = { '0', BRIGHT_YELLOW };
        if (h >= 0 && h < NUM_ROWS && FLAPPY_COL + 1 >= 0 && FLAPPY_COL + 1 < NUM_COLS)
            screen[h][FLAPPY_COL + 1] = { '/', BRIGHT_YELLOW };
        if (h - 1 >= 0 && h - 1 < NUM_ROWS && FLAPPY_COL + 2 >= 0 && FLAPPY_COL + 2 < NUM_COLS)
            screen[h - 1][FLAPPY_COL + 2] = { '/', BRIGHT_YELLOW };
    } else { // Going up, flap wings
        // Left wing
        if (frame % 6 < 3) {
            if (h >= 0 && h < NUM_ROWS && FLAPPY_COL - 1 >= 0 && FLAPPY_COL - 1 < NUM_COLS)
                screen[h][FLAPPY_COL - 1] = { '/', BRIGHT_YELLOW };
            if (h + 1 >= 0 && h + 1 < NUM_ROWS && FLAPPY_COL - 2 >= 0 && FLAPPY_COL - 2 < NUM_COLS)
                screen[h + 1][FLAPPY_COL - 2] = { '/', BRIGHT_YELLOW };
        } else {
            if (h >= 0 && h < NUM_ROWS && FLAPPY_COL - 1 >= 0 && FLAPPY_COL - 1 < NUM_COLS)
                screen[h][FLAPPY_COL - 1] = { '\\', BRIGHT_YELLOW };
            if (h - 1 >= 0 && h - 1 < NUM_ROWS && FLAPPY_COL - 2 >= 0 && FLAPPY_COL - 2 < NUM_COLS)
                screen[h - 1][FLAPPY_COL - 2] = { '\\', BRIGHT_YELLOW };
        }
        // Body
        if (h >= 0 && h < NUM_ROWS && FLAPPY_COL >= 0 && FLAPPY_COL < NUM_COLS)
            screen[h][FLAPPY_COL] = { '0', BRIGHT_YELLOW };
        // Right wing
        if (frame % 6 < 3) {
            if (h >= 0 && h < NUM_ROWS && FLAPPY_COL + 1 >= 0 && FLAPPY_COL + 1 < NUM_COLS)
                screen[h][FLAPPY_COL + 1] = { '\\', BRIGHT_YELLOW };
            if (h + 1 >= 0 && h + 1 < NUM_ROWS && FLAPPY_COL + 2 >= 0 && FLAPPY_COL + 2 < NUM_COLS)
                screen[h + 1][FLAPPY_COL + 2] = { '\\', BRIGHT_YELLOW };
        } else {
            if (h >= 0 && h < NUM_ROWS && FLAPPY_COL + 1 >= 0 && FLAPPY_COL + 1 < NUM_COLS)
                screen[h][FLAPPY_COL + 1] = { '/', BRIGHT_YELLOW };
            if (h - 1 >= 0 && h - 1 < NUM_ROWS && FLAPPY_COL + 2 >= 0 && FLAPPY_COL + 2 < NUM_COLS)
                screen[h - 1][FLAPPY_COL + 2] = { '/', BRIGHT_YELLOW };
        }
    }
}