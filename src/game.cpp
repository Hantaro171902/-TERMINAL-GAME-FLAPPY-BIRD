#include "game.hpp"
#include "utils.hpp"
#include <iostream>
#include <unistd.h> // for usleep
#include <conio.h>  // if on windows, else implement kbhit/getch for linux

using namespace std;

Game::Game(int r, int c) 
    : bird(10, r / 2), pipe1(c + 20, r, c), pipe2(c + 60, r, c), rows(r), cols(c), score(0), gameOver(false) {
    Utils::clearScreen();
    Utils::hideCursor();
}

void Game::run() {
    Utils::hideCursor();
    char input;
    while (true) {
        if (kbhit()) {
            input = getch();
            processInput(input);
        }
        update();
        render();
        usleep(100000); // Control game speed
        if (gameOver) {
            Utils::moveCursor(cols / 2 - 5, rows / 2);
            cout << "Game Over! Score: " << score;
            Utils::moveCursor(0, rows + 1);
            break;
        }
    }
    Utils::showCursor();
}

void Game::processInput(char input) {
    if (input == ' ') bird.flap();
    else if (input == 'q') gameOver = true;
}

void Game::update() {
    bird.update();
    pipe1.update();
    pipe2.update();

    if (pipe1.collidesWith(bird) || pipe2.collidesWith(bird) || bird.getRow() <= 0 || bird.getRow() >= rows) {
        gameOver = true;
    }
}

void Game::render() {
    Utils::clearScreen();
    bird.draw();
    pipe1.draw();
    pipe2.draw();

    // Update score
    if (pipe1.getCenter() == bird.getCol() || pipe2.getCenter() == bird.getCol()) {
        score++;
    }

    Utils::moveCursor(1, 1);
    cout << "Score: " << score;
    cout.flush();
}

