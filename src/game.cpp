#include "game.hpp"
#include "utils.hpp"
#include <iostream>
#include <unistd.h> // for usleep
#include "input.hpp"
using namespace std;

Utils utils;

Game::Game(int r, int c) 
    : bird(10, r / 2), pipe1(c + 20, r, c), pipe2(c + 60, r, c), rows(r), cols(c), score(0), gameOver(false) {
    utils.clearScreen();
    utils.hideCursor();
}

void Game::run() {
    utils.hideCursor();
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
            utils.moveCursor(cols / 2 - 5, rows / 2);
            cout << "Game Over! Score: " << score;
            utils.moveCursor(0, rows + 1);
            break;
        }
    }
    utils.showCursor();
}

void Game::processInput(char input) {
    if (input == ' ') bird.flap();
    else if (input == 'q' || input == 'Q') gameOver = true;
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
    utils.clearScreen();
    bird.draw();
    pipe1.draw();
    pipe2.draw();

    // Update score
    if (pipe1.getCenter() == bird.getCol() || pipe2.getCenter() == bird.getCol()) {
        score++;
    }

    utils.moveCursor(1, 1);
    cout << "Score: " << score;
    cout.flush();
}

