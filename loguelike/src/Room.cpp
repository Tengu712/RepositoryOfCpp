#include "../include/Header.hpp"

#include <random>

Room::Room():left(0U),up(0U),width(0U),height(0U),points(0U){

}

Room::~Room(){
    if(points!=nullptr)
        delete points;
}

void Room::init(unsigned int curLeft, unsigned int curUp, unsigned int spanCol, unsigned int spanRow){
    std::random_device rnd;
    const unsigned int shiftCol = rnd() % (spanCol - 3U);
    const unsigned int shiftRow = rnd() % (spanRow - 3U);
    left = curLeft + shiftCol;
    up = curUp + shiftRow;
    width = (spanCol - shiftCol - 3U) * (rnd() % 100U) / 100U + 3U;
    height = (spanRow - shiftRow - 3U) * (rnd() % 100U) / 100U + 3U;
}

std::string Room::getChar(unsigned int x, unsigned int y){
    if (x >= left && x <= left+width && y >= up && y <= up + height){
        return " ";
    } else {
        return "X";
    }
}