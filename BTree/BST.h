#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <string>
#include <sstream>

template <typename Key, typename Data>
class BST {
private:
    struct Node {   // структура узла списка
        Key key;    // ключ
        Data data;  // данные
        Node* left; // указатеь на левого потомка
        Node* right;    // указатель на правого потомка
        Node* parent;   // указатель на предка
        
        Node(const Key& k, const Data& d) : key(k), data(d), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root; // корень дерева
    size_t size;    // размер дерева

    // Вспомогательные функции
    void clear(Node* node); // очистка поддерева
    Node* copyTree(Node* node, Node* parent);   // копирование дерева
    Node* findMin(Node* node) const;    // найти минимальный узел
    Node* findMax(Node* node) const;    // найти максимальный узел
    void printTree(Node* node, int space) const; // вывод поддерева
    void postOrderTraversal(Node* node, std::vector<Key>& keys) const;  // добавление ключей в список
    void mergeNodes(Node* node);    // объединить узлы

public:
    BST() : root(nullptr), size(0) {}   // конструктор по умолчанию
    BST(const BST& other);  // конструктор копирования
    ~BST(); // деструктор
    BST& operator=(const BST& other);   // оператор присваивания

    size_t getSize() const { return size; } // получить размер списка
    bool isEmpty() const { return size == 0; }  // проверка на пустоту
    void clear();   // очистка всего дерева
    Data& operator[](const Key& key);   // получение/изменение данных по ключу
    const Data& operator[](const Key& key) const;   // получение по ключу из константного дерева
    bool insert(const Key& key, const Data& data);  // вставка по ключу
    bool remove(const Key& key);    // удалению по ключу
    std::vector<Key> getKeysPostOrder() const;  // получение списка ключей
    void merge(const BST& other);   // объединение деревьев
    void print() const { printTree(root, 0); } // печать всего дерева на экран

    // Итераторы
    class Iterator;
    class ReverseIterator;

    Iterator begin() const { return Iterator(findMin(root), root); }    // получние прямого итератора на минимальный ключ
    Iterator end() const { return Iterator(nullptr, root); }    // получение неустановленного прямого итератора
    ReverseIterator rbegin() const { return ReverseIterator(findMax(root), root); } // получение обратного итреатора на макс ключ
    ReverseIterator rend() const { return ReverseIterator(nullptr, root); } // получение обратного неустановленного итератора

    class Iterator {
    private:
        Node* current;  // текущей узел
        Node* rootIt;   // указатель на корень

        Node* findMaxIt(Node* node) const { // вспомогательная функция поиска максимального узла
            if (!node) return nullptr;
            while (node->right) node = node->right;
            return node;
        }
    
    public:
        Iterator() : current(nullptr), rootIt(nullptr) {}   // конкструктор по умолчанию
        Iterator(Node* node, Node* root_node) : current(node), rootIt(root_node) {} // конструктор
    
        Data& operator*() const { // получение значения 
            if (current == nullptr) throw std::out_of_range("Exception: out of range");
            return current->data; 
        }

        Key getKey() const {    // получение ключа
            if (current == nullptr) throw std::out_of_range("Exception: out of range"); 
            return current->key; 
        }
    
        Iterator& operator++() {    // префиксный инкремент
            if (current == nullptr) throw std::out_of_range("Exception: out of range");

            if (!current) return *this;
                
            if (current->right) {
                // Если есть правое поддерево, идем к его минимальному элементу
                current = current->right;
                while (current->left) {
                    current = current->left;
                }
            } else {
                // Идем вверх до первого узла, который является левым потомком
                Node* parent = current->parent;
                while (parent && current == parent->right) {
                    current = parent;
                    parent = parent->parent;
                }
                current = parent;
            }
            return *this;
        }
    
        Iterator operator++(int) {  // постфиксный инкремент
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
    
        Iterator& operator--() {    // префиксный декремент
            if (!current) {
                // Для end() итератора переходим к максимальному элементу
                current = findMaxIt(rootIt);
                return *this;
            }
            
            if (current->left) {
                current = findMaxIt(current->left);
            } else {
                Node* parent = current->parent;
                while (parent && current == parent->left) {
                    current = parent;
                    parent = parent->parent;
                }
                current = parent;
            }
            return *this;
        }

        Iterator operator--(int) {  // постфикрсый декремент
            Iterator temp = *this;
            --(*this);
            return temp;
        }
    
        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };
    
    class ReverseIterator {
    private:
        Node* current;  // текущей узел
        Node* rootIt;   // указатель на корень

        Node* findMinIt(Node* node) const { // вспомогательная функция поиска минимального узла
            if (!node) return nullptr;
            while (node->left) node = node->left;
            return node;
        }

    public:
        ReverseIterator() : current(nullptr), rootIt(nullptr) {}    // конструктор по умолчанию
        ReverseIterator(Node* node, Node* root_node) : current(node), rootIt(root_node) {}  // конструктор

        Data& operator*() const {   // получение значения
            if (current == nullptr) throw std::out_of_range("Exception: out of range");
            return current->data; 
        }

        Key getKey() const {    // получение ключа
            if (current == nullptr) throw std::out_of_range("Exception: out of range");
            return current->key; 
        }

        ReverseIterator& operator++() { // префиксный инкремент
            if (current == nullptr) throw std::out_of_range("Exception: out of range");

            if (!current) return *this;
            
            if (current->left) {
                // Если есть левое поддерево, идем к его максимальному элементу
                current = current->left;
                while (current->right) {
                    current = current->right;
                }
            } else {
                // Идем вверх до первого узла, который является правым потомком
                Node* parent = current->parent;
                while (parent && current == parent->left) {
                    current = parent;
                    parent = parent->parent;
                }
                current = parent;
            }
            return *this;
        }

        ReverseIterator operator++(int) {   // постфиксный инкремент
            ReverseIterator temp = *this;
            ++(*this);
            return temp;
        }

        ReverseIterator& operator--() { // префиксный инкремент
            if (!current) {
                // Для rend() итератора переходим к минимальному элементу
                current = findMinIt(rootIt);
                return *this;
            }
            
            if (current->right) {
                current = findMinIt(current->right);
            } else {
                Node* parent = current->parent;
                while (parent && current == parent->right) {
                    current = parent;
                    parent = parent->parent;
                }
                current = parent;
            }
            return *this;
        }

        ReverseIterator operator--(int) {   // постфиксный инкремент
            ReverseIterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const ReverseIterator& other) const { return current == other.current; }
        bool operator!=(const ReverseIterator& other) const { return current != other.current; }
    };
};

// Реализация методов BST

template <typename Key, typename Data>
BST<Key, Data>::BST(const BST& other) : root(nullptr), size(0) {
    root = copyTree(other.root, nullptr);
    size = other.size;
}

template <typename Key, typename Data>
BST<Key, Data>::~BST() {
    clear();
}

template <typename Key, typename Data>
BST<Key, Data>& BST<Key, Data>::operator=(const BST& other) {
    if (this != &other) {
        clear();
        root = copyTree(other.root, nullptr);
        size = other.size;
    }
    return *this;
}

template <typename Key, typename Data>
void BST<Key, Data>::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename Key, typename Data>
void BST<Key, Data>::clear() {
    clear(root);
    root = nullptr;
    size = 0;
}

template <typename Key, typename Data>
typename BST<Key, Data>::Node* BST<Key, Data>::copyTree(Node* node, Node* parent) {
    if (!node) return nullptr;
    
    Node* newNode = new Node(node->key, node->data);
    newNode->parent = parent;
    newNode->left = copyTree(node->left, newNode);
    newNode->right = copyTree(node->right, newNode);
    
    return newNode;
}

template <typename Key, typename Data>
typename BST<Key, Data>::Node* BST<Key, Data>::findMin(Node* node) const {
    if (!node) return nullptr;
    while (node->left) node = node->left;
    return node;
}

template <typename Key, typename Data>
typename BST<Key, Data>::Node* BST<Key, Data>::findMax(Node* node) const {
    if (!node) return nullptr;
    while (node->right) node = node->right;
    return node;
}

template <typename Key, typename Data>
void BST<Key, Data>::printTree(Node* node, int space) const {
    if (!node) return;
    
    space += 5;
    
    printTree(node->right, space);
    
    std::cout << std::endl;
    for (int i = 5; i < space; i++) std::cout << " ";
    std::cout << node->key << "\n";
    
    printTree(node->left, space);
}

template <typename Key, typename Data>
Data& BST<Key, Data>::operator[](const Key& key) {
    Node* current = root;
    Node* parent = nullptr;
    
    while (current) {
        if (key == current->key) {
            return current->data;
        }
        
        parent = current;
        current = (key < current->key) ? current->left : current->right;
    }
    
    throw std::out_of_range("Key not found");
}

template <typename Key, typename Data>
const Data& BST<Key, Data>::operator[](const Key& key) const {
    return const_cast<const Data&>(operator[](key));
}

template <typename Key, typename Data>
bool BST<Key, Data>::insert(const Key& key, const Data& data) {
    Node* current = root;
    Node* parent = nullptr;
    
    while (current) {
        if (key == current->key) {
            return false; // Ключ уже существует
        }
        
        parent = current;
        current = (key < current->key) ? current->left : current->right;
    }
    
    Node* newNode = new Node(key, data);
    newNode->parent = parent;
    
    if (!parent) {
        root = newNode;
    } else if (key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    
    size++;
    return true;
}

template <typename Key, typename Data>
bool BST<Key, Data>::remove(const Key& key) {
    Node* current = root;
    
    while (current) {
        if (key == current->key) break;
        current = (key < current->key) ? current->left : current->right;
    }
    
    if (!current) return false; // Ключ не найден
    
    if (!current->left && !current->right) {
        // Нет потомков
        if (current->parent) {
            if (current->parent->left == current) {
                current->parent->left = nullptr;
            } else {
                current->parent->right = nullptr;
            }
        } else {
            root = nullptr;
        }
        delete current;
    } else if (!current->left || !current->right) {
        // Один потомок
        Node* child = current->left ? current->left : current->right;
        child->parent = current->parent;
        
        if (current->parent) {
            if (current->parent->left == current) {
                current->parent->left = child;
            } else {
                current->parent->right = child;
            }
        } else {
            root = child;
        }
        delete current;
    } else {
        // Два потомка
        Node* successor = findMin(current->right);
        current->key = successor->key;
        current->data = successor->data;
        
        if (successor->parent->left == successor) {
            successor->parent->left = successor->right;
        } else {
            successor->parent->right = successor->right;
        }
        
        if (successor->right) {
            successor->right->parent = successor->parent;
        }
        
        delete successor;
    }
    
    size--;
    return true;
}

template <typename Key, typename Data>
void BST<Key, Data>::postOrderTraversal(Node* node, std::vector<Key>& keys) const {
    if (!node) return;
    
    postOrderTraversal(node->left, keys);
    postOrderTraversal(node->right, keys);
    keys.push_back(node->key);
}

template <typename Key, typename Data>
std::vector<Key> BST<Key, Data>::getKeysPostOrder() const {
    std::vector<Key> keys;
    postOrderTraversal(root, keys);
    return keys;
}

template <typename Key, typename Data>
void BST<Key, Data>::mergeNodes(Node* node) {
    if (!node) return;
    insert(node->key, node->data);
    mergeNodes(node->left);
    mergeNodes(node->right);
}

template <typename Key, typename Data>
void BST<Key, Data>::merge(const BST& other) {
    mergeNodes(other.root);
}
