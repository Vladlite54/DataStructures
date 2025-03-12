#include <iostream>
#include "ArrayList.h"
#include "Menu.h"
#include <vector>


int main() {

    //ArrayList<int> list(4);
    // list.add(1);
    // list.add(2);
    // list.add(5);
    // list.add(1);
    // list.add(4);
    // list.erase(1);
    
    
    // ArrayList<int>::iterator it = list.begin();
    // for (auto it = list.begin(); it != list.end(); ++it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << "\n";
  
    // list.clear();
   
    // list.print();
    // list.printFull();
    Menu menu{};
    menu.start();

    return 0;
}