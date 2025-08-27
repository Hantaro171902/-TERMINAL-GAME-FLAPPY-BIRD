#pragma once

#include <vector>
#include <string>
#include "color.hpp"

class Pipe {
private:
    float opening_height;
    int center;

public:
    Pipe();
    Pipe(int initial_center, float initial_height); 
    void refresh(int& score);
    void draw(std::vector<std::vector<Pixel>>& screen, int ceiling_row, int floor_row) const;
    int get_orow(int top) const;
    int get_center() const;
};
