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
    screen = std::vector<std::vector<Pixel>>(NUM_ROWS, std::vector<Pixel>(NUM_COLS, { ' ', DEFAULT }));
}

void Game::render() const {
    clearTerminal();
    for (const auto& row : screen) {
        TextColor current_color = DEFAULT;
        std::cout << getTextColor(DEFAULT); // Reset at the start of each row
        
        for (const auto& pixel : row) {
            if (pixel.color != current_color) {
                std::cout << getTextColor(pixel.color);
                current_color = pixel.color;
            }
            std::cout << pixel.ch;
        }
        std::cout << getResetColor() << std::endl;
    }
}

void Game::draw(int ceil_row, int floor_row, char ch, int spacing, int col_start) {
    int sdigs = std::to_string(score).length();
    int bdigs = std::to_string(best_score).length();
    int limit = SCORE_START_COL - sdigs - bdigs;
    for (int i = col_start; i < NUM_COLS; i += spacing) {
        if (i < limit && i >= 0 && i < NUM_COLS)
            screen[ceil_row][i] = { ch, CYAN };
        if (i < NUM_COLS && i >= 0 && i < NUM_COLS)
            screen[floor_row][i] = { ch, CYAN };
    }
}

void Game::draw_score() {
    char buf[50];
    sprintf(buf, " Score: %d  Best: %d", score, best_score);
    int sdigs = std::to_string(score).length();
    int bdigs = std::to_string(best_score).length();
    int start_col = SCORE_START_COL - sdigs - bdigs;
    
    // Draw score
    int i = 0;
    while (buf[i] != '\0') {
        if (start_col + i >= 0 && start_col + i < NUM_COLS) {
            screen[0][start_col + i] = { buf[i], BRIGHT_YELLOW };
        }
        i++;
    }
}


bool Game::crashed() const {
    if (bird.crashed(0, NUM_ROWS - 1)) return true;
    if (bird.crashed_into(p1) || bird.crashed_into(p2)) return true;
    return false;
}

void Game::splash_screen() {
    // Clear the screen buffer once at the start
    for (auto& row : screen) {
        for (auto& pixel : row) {
            pixel = { ' ', DEFAULT };
        }
    }

    // Draw the title
    std::string lines[5] = {
        " ___ _         _         ___ _      _ ",
        "| __| |__ _ _ __ _ __ _  | _ |_)_ _ __| |",
        "| _|| / _` | '_ \\ '_ \\ || | | _ \\ | '_/ _` |",
        "|_| |_\\__,_| .__/ .__/\\_, | |___/_|_| \\__,_|",
        "           |_|  |_|  |__/          "
    };
    int r = NUM_ROWS / 2 - 6;
    int c = NUM_COLS / 2 - 22;
    for (int i = 0; i < 5; ++i) {
        for (size_t j = 0; j < lines[i].length(); ++j) {
            if (c + j >= 0 && c + j < NUM_COLS) screen[r + i][c + j] = { lines[i][j], BRIGHT_CYAN };
        }
    }

    // Draw the message
    std::string msg = "Press <space> to flap!";
    int msg_row = NUM_ROWS / 2 + 1;
    int msg_col = NUM_COLS / 2 - msg.length() / 2;
    for (size_t j = 0; j < msg.length(); ++j) {
        if (msg_col + j >= 0 && msg_col + j < NUM_COLS) screen[msg_row][msg_col + j] = { msg[j], BRIGHT_WHITE };
    }

    // Wait before starting the progress bar animation
    render();
    usleep(500000); // Wait for half a second to show the title screen

    // Animate the progress bar while keeping the title and message
    int bar_col = NUM_COLS / 2 - PROG_BAR_LEN / 2 - 1;
    if (bar_col >= 0 && bar_col < NUM_COLS) screen[PROG_BAR_ROW][bar_col] = { '[', BRIGHT_WHITE };
    int end_col = NUM_COLS / 2 + PROG_BAR_LEN / 2;
    if (end_col >= 0 && end_col < NUM_COLS) screen[PROG_BAR_ROW][end_col] = { ']', BRIGHT_WHITE };
    render(); // Render the bar outline

    for (int i = 0; i < PROG_BAR_LEN; ++i) {
        usleep(static_cast<unsigned int>(1000000 * START_TIME_SEC / PROG_BAR_LEN));
        int fill_col = bar_col + 1 + i;
        if (fill_col >= 0 && fill_col < NUM_COLS) screen[PROG_BAR_ROW][fill_col] = { '=', BRIGHT_CYAN };
        render();
    }
    usleep(500000);
}

int Game::failure_screen() {
    Input input;
    input.init_terminal();
    fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) & ~O_NONBLOCK);

    clearScreen();
    std::string msg = "Flappy died :-(. <Enter> to play again, 'q' to quit.";
    std::cout << getTextColor(BRIGHT_RED); // Set color for the whole message
    for (int i = 0; i < NUM_ROWS / 2 - 1; ++i) std::cout << std::endl;
    for (int i = 0; i < NUM_COLS / 2 - 22; ++i) std::cout << " ";
    std::cout << msg << std::endl;
    std::cout << getResetColor();

    int ch = getchar();
    input.reset_terminal();

    if (ch == 'q') {
        exit(0);
    }

    if (score > best_score) best_score = score;
    score = 0;
    return 1;
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
        for (auto& row : screen) {
            for (auto& pixel : row) {
                pixel = { ' ', DEFAULT };
            }
        }

        draw(0, NUM_ROWS - 1, '/', 2, frame % 2);
        p1.draw(screen, 0, NUM_ROWS - 1);
        p2.draw(screen, 0, NUM_ROWS - 1);
        bird.draw(screen, frame);
        draw_score();

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