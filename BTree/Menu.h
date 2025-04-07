#pragma once

#include <iostream>
#include <fstream>
#include <limits>
#include "BTree.h"

class Menu
{
private:
    std::string menuInfo;

public:
    Menu();
    void start();
};