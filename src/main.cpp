#include <iostream>
#include <cstdlib>
#include <csignal>
#include <vector>
#include "game.hpp"
#include "color.hpp"
#include "utils.hpp"

using namespace std;

void cleanup(int signum) {
    showCursor();  // restore cursor on exit (even if Ctrl+C)
    exit(signum);
}

int main() {
    signal(SIGINT, cleanup);    
    signal(SIGTERM, cleanup);

    hideCursor();

    Game game;
    game.run();

    showCursor();
    return 0;
}