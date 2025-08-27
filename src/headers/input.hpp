#pragma once


#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include "color.hpp"
    class Input {
    private:
        struct termios oldt, newt;
        int oldf;

    public:
        Input();
        ~Input();
        void init_terminal();
        void reset_terminal();
    };


    // inline int kbhit() {
    //     termios oldt, newt;
    //     int ch;
    //     int oldf;

    //     tcgetattr(STDIN_FILENO, &oldt);
    //     newt = oldt;
    //     newt.c_lflag &= ~(ICANON | ECHO);
    //     tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    //     oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    //     fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    //     ch = getchar();

    //     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    //     fcntl(STDIN_FILENO, F_SETFL, oldf);

    //     if (ch != EOF) {
    //         ungetc(ch, stdin);
    //         return 1;
    //     }
    //     return 0;
    // }

    // inline int getch() {
    //     struct termios oldt, newt;
    //     int ch;
    //     tcgetattr(STDIN_FILENO, &oldt);
    //     newt = oldt;
    //     newt.c_lflag &= ~(ICANON | ECHO);
    //     tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    //     ch = getchar();
    //     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    //     return ch;
    // }
#endif
