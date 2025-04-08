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
    "begin iterator\n"
    "rbegin iterator\n"
    "end iterator\n"
    "rend iterator"
    "++iterator\n"
    "++riterator\n"
    "--iterator\n"
    "--riterator\n"
    "compare iterators == \n"
    "compare riterators == \n"
    "compare iterators != \n"
    "compare riterators != \n"
    "get iterator value\n"
    "get riterator value\n"
    "set iterator value\n"
    "set riterator value\n";
}

void Menu::start() {
    BST<int, std::string> tree;
    BST<int, std::string> tree2;
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
                    
                default:
                    std::cout << "Invalid choice. Try again.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
        
    } while (choice != -1);
}
