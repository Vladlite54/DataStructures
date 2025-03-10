#include <iostream>
#include "ArrayList.h"
#include <vector>


int main() {

    ArrayList<int> list(4);
    list.add(1);
    list.add(2);
    list.add(5);
    list.add(10);
    list.add(4);

    int get = list.getAt(2);

    list.print();
    list.printFull();
    return 0;
}