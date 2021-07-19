#include "../include/Header.hpp"
#include <Windows.h>

int main(){

    Floor floor = Floor();
    floor.init(60, 60, 3, 3);

    floor.draw();

    return 0;
}