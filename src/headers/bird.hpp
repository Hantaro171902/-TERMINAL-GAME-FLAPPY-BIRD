#pragma once

#include <string>
#include <vector>

class Pipe;

class Bird {
private:
    int h0;
    int t;

public:
    Bird();
    void update(bool jump);
    int get_position() const;
    void draw(std::vector<std::string>& screen, int frame) const;
    bool crashed(int ceiling, int floor) const;
    bool crashed_into(const Pipe& p) const;
};