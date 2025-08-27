#pragma once

#include <string>
#include <vector>
#include "color.hpp"

class Pipe;

class Bird {
private:
    int h0;
    int t;

public:
    Bird();
    void update(bool jump);
    int get_position() const;
    void draw(std::vector<std::vector<Pixel>>& screen, int frame) const;
    bool crashed(int ceiling, int floor) const;
    bool crashed_into(const Pipe& p) const;
};