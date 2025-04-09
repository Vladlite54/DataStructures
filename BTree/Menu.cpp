#include "Menu.h"

Menu::Menu() {
    menuInfo =
    "------BST menu------\n"
    "Operations:\n"
    "-1) Exit menu\n"
    "0) Show this menu\n"
    "1) Copy constructor\n"
    "2) Insert by key\n"
    "3) Remove by key\n"
    "4) Acces data by key\n"
    "5) Set value by key\n"
    "6) Get size of tree\n"
    "7) Check if tree is empty\n"
    "8) Clear\n"
    "9) Print tree\n"
    "10) Get keys in post-order (Lt → Rt → t)\n"
    "11) Merge with another tree\n"
    "12) iterator travesal\n"
    "13) reverse iterator travesal\n"
    "14) iterator begin\n"
    "15) reverse iterator begin\n"
    "16) end iterator\n"
    "17) rend iterator\n"
    "18) ++iterator\n"
    "19) ++riterator\n"
    "20) --iterator\n"
    "21) --riterator\n"
    "22) compare iterators == \n"
    "23) compare riterators == \n"
    "24) compare iterators != \n"
    "25) compare riterators != \n"
    "26) get iterator value\n"
    "27) get riterator value\n"
    "28) set iterator value\n"
    "29) set riterator value\n"
    "30) Big O testing\n";
}

void Menu::start() {
    BST<int, std::string> tree;
    BST<int, std::string> tree2;
    BST<int, std::string> treeCopy;
    BST<int, std::string>::Iterator iter;
    BST<int, std::string>::Iterator iterCompare;
    BST<int, std::string>::ReverseIterator riter;
    BST<int, std::string>::ReverseIterator riterCompare;

    int choice;
    int key;
    std::string data;
    std::cout << menuInfo << std::endl;
    
    do {
        std::cout << "Enter command -> ";
        std::cin >> choice;
        
        try {
            switch (choice) {
                case -1:
                    std::cout << "Exiting...\n";
                    break;

                case 0:
                    std::cout << menuInfo << std::endl;
                    break;
                
                case 1:
                    treeCopy = tree;
                    std::cout << "Tree copy:\n";
                    treeCopy.print();
                    break;

                case 2:
                    std::cout << "Enter key (integer): ";
                    std::cin >> key;
                    std::cout << "Enter data (string): ";
                    std::cin.ignore();
                    std::getline(std::cin, data);
                    std::cout << tree.insert(key, data) << std::endl;
                    break;
                    
                case 3:
                    std::cout << "Enter key to remove: ";
                    std::cin >> key;
                    std::cout << tree.remove(key) << std::endl;
                    break;
                    
                case 4:
                    std::cout << "Enter key to access: ";
                    std::cin >> key;
                    try {
                        std::cout << tree[key] << std::endl;
                    } catch (const std::out_of_range& e) {
                        std::cout << "0\n";
                    }
                    break;
                
                case 5:
                    std::cout << "Enter key to set: ";
                    std::cin >> key;
                    try {
                        std::cout << "Enter data (string): ";
                        std::cin.ignore();
                        std::getline(std::cin, data);
                        tree[key] = data;
                        std::cout << "1\n";
                    } catch (const std::out_of_range& e) {
                        std::cout << "0\n";
                    }
                    break;
                    
                case 6:
                    std::cout << tree.getSize() << std::endl;
                    break;
                    
                case 7:
                    std::cout << tree.isEmpty()  << std::endl;
                    break;
                    
                case 8:
                    tree.clear();
                    std::cout << "1\n";
                    break;
                    
                case 9:
                    std::cout << "Tree structure:\n";
                    tree.print();
                    break;
                    
                case 10: {
                    std::vector<int> keys = tree.getKeysPostOrder();
                    std::cout << "Keys in post-order: ";
                    for (int k : keys) {
                        std::cout << k << " ";
                    }
                    std::cout << "\n";
                    break;
                }
                    
                case 11: {
                    std::cout << "Creating second tree for merge...\n";
                    tree2.clear();
                    int count;
                    std::cout << "How many elements to add to second tree? ";
                    std::cin >> count;
                    for (int i = 0; i < count; i++) {
                        std::cout << "Enter key (integer) for element " << i+1 << ": ";
                        std::cin >> key;
                        std::cout << "Enter data (string): ";
                        std::cin.ignore();
                        std::getline(std::cin, data);
                        tree2.insert(key, data);
                    }
                    tree.merge(tree2);
                    std::cout << "Trees merged successfully.\n";
                    break;
                }

                case 12: {
                    std::cout << "Forward iteration (using iterator):\n";
                    for (auto it = tree.begin(); it != tree.end(); ++it) {
                        std::cout << "Key: " << it.getKey() << ", Data: " << *it << "\n";
                    }
                    break;
                }
                    
                case 13: {
                    std::cout << "Backward iteration (using reverse iterator):\n";
                    for (auto rit = tree.rbegin(); rit != tree.rend(); ++rit) {
                        std::cout << "Key: " << rit.getKey() << ", Data: " << *rit << "\n";
                    }
                    break;
                }

                case 14:
                    try {
                        iter = tree.begin();
                        std::cout << "1\n";
                    }
                    catch(std::exception &e) {
                        std::cout << "0\n";
                    }
                    break;

                case 15:
                    try {
                        riter = tree.rbegin();
                        std::cout << "1\n";
                    }
                    catch(std::exception &e) {
                        std::cout << "0\n";
                    }
                    break;
                
                case 16:
                    iter = tree.end();
                    std::cout << "1\n";
                    break;
                
                case 17:
                    riter = tree.rend();
                    std::cout << "1\n";
                    break;
                
                case 18:
                    try {
                        ++iter;
                        std::cout << "1\n";
                    }
                    catch(std::exception &e) {
                        std::cout << "0\n";
                    }
                    break;
                
                case 19:
                    try {
                        ++riter;
                        std::cout << "1\n";
                    }
                    catch(std::exception &e) {
                        std::cout << "0\n";
                    }
                    break;
                
                case 20:
                    try {
                        --iter;
                        std::cout << "1\n";
                    }
                    catch(std::exception &e) {
                        std::cout << "0\n";
                    }
                    break;
                
                case 21:
                    try {
                        --riter;
                        std::cout << "1\n";
                    }
                    catch(std::exception &e) {
                        std::cout << "0\n";
                    }
                    break;
                
                case 22:
                    iterCompare = tree.begin();
                    std::cout << (iter == iterCompare) << std::endl;
                    break;
                
                case 23:
                    riterCompare = tree.rbegin();
                    std::cout << (riter == riterCompare) << std::endl;
                    break;
                
                case 24:
                    iterCompare = tree.begin();
                    std::cout << (iter != iterCompare) << std::endl;
                    break;
                
                case 25:
                    riterCompare = tree.rbegin();
                    std::cout << (riter != riterCompare) << std::endl;
                    break;
                
                case 26:
                    try {
                        int key = iter.getKey();
                        std::cout << "Key: " << key << ", Data: " << *iter << "\n";
                    }
                    catch(std::exception &e) {
                        std::cout << "0\n";
                    }
                    break;
                
                case 27:
                    try {
                        int key = riter.getKey();
                        std::cout << "Key: " << key << ", Data: " << *riter << "\n";
                    }
                    catch(std::exception &e) {
                        std::cout << "0\n";
                    }
                    break;
                
                case 28:
                    std::cout << "Enter value -> ";
                    std::cin >> data;
                    try {
                        *iter = data;
                        std::cout << "1\n";
                    }
                    catch(std::exception &e) {
                        std::cout << "0\n";
                    }
                    break;
                
                case 29:
                    std::cout << "Enter value -> ";
                    std::cin >> data;
                    try {
                        *riter = data;
                        std::cout << "1\n";
                    }
                    catch(std::exception &e) {
                        std::cout << "0\n";
                    }
                    break;
                
                case 30:
                    std::cout << "Rand tree test: " << std::endl;
                    for (int i = 500, j = 1; i <= 2500; i += 500, j++) {
                        std::cout << "Iteration " << j << std::endl;
                        test_rand(i);
                    }
                    std::cout << "Ord tree test: " << std::endl;
                    for (int i = 500, j = 1; i <= 2500; i += 500, j++) {
                        std::cout << "Iteration " << j << std::endl;
                        test_ord(i);
                    }
                    break;
                
                default:
                    std::cout << "Invalid choice. Try again.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
        
    } while (choice != -1);
}
