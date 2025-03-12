#include "Menu.h"

Menu::Menu() {
    menuInfo =
    "------ArrayList menu------\n"
    "Operations:\n"
    "-1) Exit menu\n"
    "0) Show this menu\n"
    "1) Constructor -> create list\n"
    "2) Copy constructor -> copy old list to new list\n"
    "3) getSize() -> get list size\n"
    "4) clear() -> clear list\n"
    "5) empty() -> is list empty?\n"
    "6) contains(T target) -> check if list contains element\n"
    "7) getAt(int index) -> get element at index\n"
    "8) setAt(int index, T value) -> set value to element at index\n"
    "9) find(T target) -> find target element\n"
    "10) add(T value) -> add new value to list\n"
    "11) insert(int index, T value) -> insert value to position in list\n"
    "12) erase(T target) -> erase target value in list\n"
    "13) eraseAt(int index) -> erase element at index\n"
    "14) print() -> print list\n"
    "15) getCapacity() -> get current capacity\n"
    "16) begin() -> get iterator of begin\n"
    "17) end() -> get iterator at end\n"
    "18) ++iterator -> iterator increment\n"
    "19) --iterator -> iterator decrement\n"
    "20) compare iterators == \n"
    "21) compare iterators != \n"
    "22) get iterator value\n";

}

void Menu::start() {
    bool end = false;
    std::cout << menuInfo << std::endl;
    ArrayList<int> list{}, list2{};
    int command, capacity, element, position, result;
    ArrayList<int>::iterator it, it2;
    while (!end) {
        try {
            std::cout << "Enter command: ";
            std::cin >> command;
            if (std::cin.fail()) {
                throw std::runtime_error("Incorrect input!");
            }
            switch (command) {
            case -1:
                end = true;
                break;
            case 0:
                std::cout << menuInfo << std::endl;
                break;
            case 1:
                std::cout << "Enter the capacity: ";
                std::cin >> capacity;
                if (std::cin.fail()) break;
                list = ArrayList<int>{capacity};
                std::cout << "Created list with capacity " << capacity << std::endl;
                std::cout << "1\n";
                break;
            case 2:
                list2 = list;
                std::cout << "List2 was created by copy of list" << std::endl;
                std::cout << "List: ";
                list.print();
                std::cout << "List2: ";
                list2.print();
                std::cout << "1\n";
                break;
            case 3:
                std::cout << "List size is " << list.getSize() << std::endl;
                std::cout << "1\n";
                break;
            case 4:
                list.clear();
                std::cout << "1\n";
                break;
            case 5:
                std::cout << list.empty() << std::endl;
                break;
            case 6:
                std::cout << "Enter element: ";
                std::cin >> element;
                if (std::cin.fail()) break;
                std::cout << list.contains(element) << std::endl;
                break;
            case 7:
                std::cout << "Enter position: " << std::endl;
                std::cin >> position;
                if (std::cin.fail()) break;
                std::cout << "Element at position " << position << " is " << list.getAt(position) << std::endl;
                std::cout << "1\n";
                break;
            case 8:
                std::cout << "Enter position and element: ";
                std::cin >> position >> element;
                if (std::cin.fail()) break;
                list.setAt(position, element);
                std::cout << "1\n";
                break;
            case 9:
                std::cout << "Enter element you want to find: ";
                std::cin >> element;
                if (std::cin.fail()) break;
                result = list.find(element);
                if (result == -1) {
                    std::cout << "0\n" << std::endl;
                    break;
                }
                else { 
                    std::cout << "Element has been found at position: " << result << std::endl;
                    std::cout << "1\n";
                }
                break;
            case 10:
                std::cout << "Enter element: ";
                std::cin >> element;
                if (std::cin.fail()) break;
                list.add(element);
                std::cout << "1\n";
                break;
            case 11:
                std::cout << "Enter position and element: ";
                std::cin >> position >> element;
                if (std::cin.fail()) break;
                list.insert(position, element);;
                std::cout << "1\n";
                break;
            case 12:
                std::cout << "Enter element: ";
                std::cin >> element;
                if (std::cin.fail()) break;
                std::cout << list.erase(element) << std::endl;
                break;
            case 13:
                std::cout << "Enter position: ";
                std::cin >> position;
                if (std::cin.fail()) break;
                list.eraseAt(position);
                std::cout << "1\n";
                break;
            case 14:
                list.print();
                std::cout << "1\n";
                break;
            case 15:
                std::cout << "Current capacity: " << list.getCapacity() << std::endl;
                std::cout << "1\n";
                break;
            case 16:
                it = list.begin();
                std::cout << "1\n";
                break;
            case 17:
                it = list.end();
                std::cout << "1\n";
                break;
            case 18:
                ++it;
                std::cout << "1\n";
                break;
            case 19:
                --it;
                std::cout << "1\n";
                break;
            case 20:
                it2 = list.end();
                std::cout << (it == it2) << std::endl;
                break;
            case 21:
                std::cout << (it != it2) << std::endl;
                break;
            case 22:
                std::cout << "Iterator value: " << *it << std::endl;
                std::cout << "1\n";
                break;
            default:
                std::cout << "Unknown command!" << std::endl;
                std::cout << "0\n";
                break;
            }
        } catch(const std::exception& e) {
            std::cerr << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "0\n" << std::endl;
        }
    }
}
