#include "game.hpp"
#include "utils.hpp"
#include "input.hpp"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

Game::Game() : frame(0), score(0), best_score(0) {
    screen = std::vector<std::string>(NUM_ROWS, std::string(NUM_COLS, ' '));
}


void Game::render() const {
    clearTerminal();
    for (const auto& row : screen) {
        std::cout << row << std::endl;
    }
}

void Game::draw(int ceil_row, int floor_row, char ch, int spacing, int col_start) {
    int sdigs = std::to_string(score).length();
    int bdigs = std::to_string(best_score).length();
    int limit = SCORE_START_COL - sdigs - bdigs;
    for (int i = col_start; i < NUM_COLS; i += spacing) {
        if (i < limit)
            screen[ceil_row][i] = ch;
        if (i < NUM_COLS)
            screen[floor_row][i] = ch;
    }
}

void Game::draw_score() {
    char buf[50];
    sprintf(buf, " Score: %d  Best: %d", score, best_score);
    int sdigs = std::to_string(score).length();
    int bdigs = std::to_string(best_score).length();
    int start_col = SCORE_START_COL - sdigs - bdigs;
    for (int i = 0; buf[i] != '\0'; ++i) {
        if (start_col + i < NUM_COLS)
            screen[0][start_col + i] = buf[i];
    }
}

bool Game::crashed() const {
    if (bird.crashed(0, NUM_ROWS - 1)) return true;
    if (bird.crashed_into(p1) || bird.crashed_into(p2)) return true;
    return false;
}

void Game::splash_screen() {
    // Clear screen vector
    for (auto& row : screen) std::fill(row.begin(), row.end(), ' ');

    // Draw title
    std::string lines[5] = {
        " ___ _                       ___ _        _ ",
        "| __| |__ _ _ __ _ __ _  _  | _ |_)_ _ __| |",
        "| _|| / _` | '_ \\ '_ \\ || | | _ \\ | '_/ _` |",
        "|_| |_\\__,_| .__/ .__/\\_, | |___/_|_| \\__,_|",
        "           |_|  |_|   |__/                  "
    };
    int r = NUM_ROWS / 2 - 6;
    int c = NUM_COLS / 2 - 22;
    for (int i = 0; i < 5; ++i) {
        for (size_t j = 0; j < lines[i].length(); ++j) {
            if (c + j < NUM_COLS) screen[r + i][c + j] = lines[i][j];
        }
    }

    // Draw message
    std::string msg = "Press <space> to flap!";
    int msg_row = NUM_ROWS / 2 + 1;
    int msg_col = NUM_COLS / 2 - msg.length() / 2;
    for (size_t j = 0; j < msg.length(); ++j) {
        if (msg_col + j < NUM_COLS) screen[msg_row][msg_col + j] = msg[j];
    }

    render();

    // Progress bar
    for (auto& row : screen) std::fill(row.begin(), row.end(), ' ');
    int bar_col = NUM_COLS / 2 - PROG_BAR_LEN / 2 - 1;
    if (bar_col >= 0 && bar_col < NUM_COLS) screen[PROG_BAR_ROW][bar_col] = '[';
    int end_col = NUM_COLS / 2 + PROG_BAR_LEN / 2;
    if (end_col >= 0 && end_col < NUM_COLS) screen[PROG_BAR_ROW][end_col] = ']';
    render();

    for (int i = 0; i < PROG_BAR_LEN; ++i) {
        usleep(static_cast<unsigned int>(1000000 * START_TIME_SEC / PROG_BAR_LEN));
        int fill_col = bar_col + 1 + i;
        if (fill_col >= 0 && fill_col < NUM_COLS) screen[PROG_BAR_ROW][fill_col] = '=';
        render();
    }
    usleep(500000);
}

int Game::failure_screen() {
    // Set to blocking
    Input input;
    input.init_terminal(); // Ensure terminal is in correct state
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) & ~O_NONBLOCK);

    clearScreen();
    std::string msg = "Flappy died :-(. <Enter> to play again, 'q' to quit.";
    for (int i = 0; i < NUM_ROWS / 2 - 1; ++i) std::cout << std::endl;
    for (int i = 0; i < NUM_COLS / 2 - 22; ++i) std::cout << " ";
    std::cout << msg << std::endl;

    int ch = getchar();
    input.reset_terminal(); // Reset terminal before checking input

    if (ch == 'q') {
        exit(0);
    }

    if (score > best_score) best_score = score;
    score = 0;
    return 1;  // Restart
}

void Game::run() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    Input input;
    input.init_terminal();
    splash_screen();

    int restart = 1;
    while (true) {
        if (restart) {
            p1 = Pipe(static_cast<int>(1.2 * (NUM_COLS - 1)), std::rand() / static_cast<float>(RAND_MAX) * 0.5f + 0.25f);
            p2 = Pipe(static_cast<int>(1.75 * (NUM_COLS - 1)), std::rand() / static_cast<float>(RAND_MAX) * 0.5f + 0.25f);
            bird = Bird();
            frame = 0;
            restart = 0;
        }

        usleep(static_cast<unsigned int>(1000000 / TARGET_FPS));

        // Process input
        bool jump = false;
        int ch = getchar();
        if (ch != EOF) {
            if (ch == 'q') {
                input.reset_terminal();
                exit(0);
            } else if (ch == ' ') {
                jump = true;
            }
        }

        bird.update(jump);

        // Clear screen buffer
        for (auto& row : screen) std::fill(row.begin(), row.end(), ' ');

        // Draw elements
        draw(0, NUM_ROWS - 1, '/', 2, frame % 2);
        p1.draw(screen, 0, NUM_ROWS - 1);
        p2.draw(screen, 0, NUM_ROWS - 1);
        bird.draw(screen, frame);
        draw_score();

        // Update pipes (after draw, as in reference)
        p1.refresh(score);
        p2.refresh(score);

        if (crashed()) {
            restart = failure_screen();
            continue;
        }

        render();
        frame++;
    }
}