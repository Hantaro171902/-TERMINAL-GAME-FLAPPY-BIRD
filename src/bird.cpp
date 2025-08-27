#include "bird.hpp"
#include "pipe.hpp"
#include "color.hpp"
#include "game.hpp" // For constants like GRAV, V0, FLAPPY_COL, etc.

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
        // Adjust collision detection for the new bat size if needed.
        // For now, keeping the same logic based on FLAPPY_COL.
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
    int h = get_position(); // Vertical center of the bat
    int col = FLAPPY_COL; // Horizontal center of the bat

    // Check if the bat's drawing area is within screen bounds
    // The bat is about 4 rows tall and 9-10 columns wide (including wings)
    // We'll consider 'h' as the center-ish row for the bat's body.
    // Adjust these based on how you want to vertically align the bat.
    int top_row = h - 2; // Bat starts 2 rows above 'h'
    int bottom_row = h + 1; // Bat ends 1 row below 'h'

    if (top_row < 0 || bottom_row >= NUM_ROWS) return; // Bat entirely off-screen vertically

    TextColor bat_color = BRIGHT_MAGENTA; // A good color for a bat!

    // Helper lambda to safely set pixels
    auto set_pixel = [&](int r_offset, int c_offset, char character) {
        int r = h + r_offset;
        int c_actual = col + c_offset;
        if (r >= 0 && r < NUM_ROWS && c_actual >= 0 && c_actual < NUM_COLS) {
            screen[r][c_actual] = { character, bat_color };
        }
    };

    if (GRAV * t + V0 > 0) { // Going down (wings down)
        // Bat going down ASCII art:
        //    __     __
        //   )  \_V_/  (
        //  )_ \    / _(
        //   \  )`-'(  /
        //    `'    `'

        // Row 0 (relative to 'h')
        set_pixel(-2, -3, '_');
        set_pixel(-2, -2, '_');
        set_pixel(-2, 4, '_');
        set_pixel(-2, 5, '_');

        // Row 1
        set_pixel(-1, -4, ')');
        set_pixel(-1, -1, '\\');
        set_pixel(-1, 0, '_');
        set_pixel(-1, 1, 'V');
        set_pixel(-1, 2, '_');
        set_pixel(-1, 3, '/');
        set_pixel(-1, 6, '(');

        // Row 2
        set_pixel(0, -5, ')');
        set_pixel(0, -4, '_');
        set_pixel(0, -3, ' '); // gap
        set_pixel(0, -2, '\\');
        set_pixel(0, 4, '/');
        set_pixel(0, 5, ' '); // gap
        set_pixel(0, 6, '_');
        set_pixel(0, 7, '(');

        // Row 3
        set_pixel(1, -4, ')');
        set_pixel(1, -3, ' ');
        set_pixel(1, -2, '/');
        set_pixel(1, -1, ' ');
        set_pixel(1, 0, '`');
        set_pixel(1, 1, '-');
        set_pixel(1, 2, '\'');
        set_pixel(1, 3, ' ');
        set_pixel(1, 4, '\\');
        set_pixel(1, 5, ' ');
        set_pixel(1, 6, '(');

        // Row 4
        set_pixel(2, -3, '`');
        set_pixel(2, -2, '\'');
        set_pixel(2, 5, '`');
        set_pixel(2, 6, '\'');

    } else { // Going up, flap wings (wings up)
        // Bat going up ASCII art:
        //    __     __
        //    ) \   / (
        //   )_ \_V_/ _(
        //     )__  __(
        //        `-'

        // Row 0 (relative to 'h')
        set_pixel(-2, -3, '_');
        set_pixel(-2, -2, '_');
        set_pixel(-2, 6, '_');
        set_pixel(-2, 7, '_');

        // Row 1
        set_pixel(-1, -3, ')');
        set_pixel(-1, -2, ' ');
        set_pixel(-1, -1, '\\');
        set_pixel(-1, 5, '/');
        set_pixel(-1, 6, ' ');
        set_pixel(-1, 7, '(');

        // Row 2
        set_pixel(0, -4, ')');
        set_pixel(0, -3, '_');
        set_pixel(0, -2, ' ');
        set_pixel(0, 0, '\\');
        set_pixel(0, 1, '_');
        set_pixel(0, 2, 'V');
        set_pixel(0, 3, '_');
        set_pixel(0, 4, '/');
        set_pixel(0, 5, ' ');
        set_pixel(0, 6, ' ');
        set_pixel(0, 7, '_');
        set_pixel(0, 8, '(');

        // Row 3
        set_pixel(1, -2, ')');
        set_pixel(1, -1, '_');
        set_pixel(1, 0, '_');
        set_pixel(1, 4, '_');
        set_pixel(1, 5, '_');
        set_pixel(1, 6, '(');

        // Row 4
        set_pixel(2, 1, '`');
        set_pixel(2, 2, '-');
        set_pixel(2, 3, '\'');
    }
}