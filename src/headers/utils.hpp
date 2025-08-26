#pragma once 
#include <iostream>

class Utils {
public:    
    static void clearScreen();
    static void moveCursor(int x, int y);
    static void hideCursor();
    static void showCursor();
};

extern Utils utils;