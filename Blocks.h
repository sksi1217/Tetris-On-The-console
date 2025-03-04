#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <random>
#include <deque>

class Blocks
{
public:

    char _blockSprite = '#';

    std::deque<std::deque<COORD>> deliveredBlocks;

    std::deque<std::deque<COORD>> blocks = {
        {{0, 0}, {2, 0}, {1, 0}},
        {{0, 0}, {3, 0}, {0, 1}},
        {{0, 0}, {123, 0}, {0, 1}},
    };



    std::deque<COORD> blockPosition = { {0, 0}, {1, 0}, {-1, 0} };

    

};