#pragma once

#include <vector>
#include <string>

struct PointInf{
    unsigned int kind;
};

class Room {
public:
    unsigned int left, up, width, height;
    PointInf* points;
    Room();
    ~Room();
    void init(unsigned int curLeft, unsigned int curUp, unsigned int spanCol, unsigned int spanRow);
    std::string getChar(unsigned int x, unsigned int y);
};

class Floor {
private:
    unsigned int width, height;
    std::vector<Room> rooms;
public:
    std::string maps;
    Floor();
    void init(unsigned int w, unsigned int h, unsigned int row, unsigned int col);
    void draw();
};

