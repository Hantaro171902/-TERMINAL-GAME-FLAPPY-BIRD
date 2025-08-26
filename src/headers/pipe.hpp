#pragma once

#include <vector>
#include <string>

class Pipe {
private:
    float opening_height;
    int center;

public:
    Pipe();
    Pipe(int initial_center, float initial_height); 
    void refresh(int& score);
    void draw(std::vector<std::string>& screen, int ceiling_row, int floor_row) const;
    int get_orow(int top) const;
    int get_center() const;
};
