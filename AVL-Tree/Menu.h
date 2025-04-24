#pragma once

#include <iostream>
#include <fstream>
#include <limits>
#include "BST.h"
#include "AVLTree.h"
#include "Test.h"

class Menu
{
private:
    std::string menuInfo;

public:
    Menu();
    void start();
};