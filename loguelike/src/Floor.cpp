#include "../include/Header.hpp"

#include <iostream>

Floor::Floor(): width(0U), height(0U), rooms(std::vector<Room>()), maps("") { 
}

void Floor::init(unsigned int w, unsigned int h, unsigned int row, unsigned int col) {
    width = w;
    height = h;

    const unsigned int kSpanCol = width / col;
    const unsigned int kSpanRow = height / row;

    for(unsigned int curUp = 0U; curUp < height - 1; curUp += kSpanRow){
        for(unsigned int curLeft = 0U; curLeft < width - 1; curLeft += kSpanCol){
            rooms.push_back(Room());
            rooms.back().init(curLeft, curUp, kSpanCol, kSpanRow);
        }
    }

    for(int i=0; i<width*height; ++i)
        maps += "X";

    for (int i=0; i < width; ++i){
        for(int j=0; j< height; ++j){
            if(maps.at(j*width+i)!='X')
                continue;
            for(Room n : rooms){
                std::string tmp = n.getChar(i, j);
                if(tmp != "X"){
                    maps.replace(j * width + i, 1, tmp);
                    break;
                }
            }
        }
    }
}

void Floor::draw(){
    for(int i=0; i < width*height; ++i){
        std::cout << maps.at(i);
        if((i+1) % width == 0)
            std::cout << std::endl;
    }
}