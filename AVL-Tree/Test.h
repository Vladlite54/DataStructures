#pragma once

#include <time.h>
#include <math.h>
#include <iostream>
#include "BST.h"

using namespace std;

typedef unsigned long long INT_64;

//переменная и константы генератора LineRand()
static INT_64 RRand = 15750; 
const INT_64 mRand = (1 << 63) -1;
const INT_64 aRand = 6364136223846793005;
const INT_64 cRand = 1442695040888963407;

void sRand();
INT_64 LineRand();
void test_rand(int n);
void test_ord(int n);