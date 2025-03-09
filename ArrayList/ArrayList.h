#pragma once

#include <iostream>

template<typename T>
class ArrayList {
public:
    ArrayList(int capacity = 16);    // конструктор списка
    ArrayList(const ArrayList<T> &other);  // конструктор копирования
    ~ArrayList();   // деструктор
    int getSize(); // опрос размера списка
    void clear();   // очистка списка
    bool empty();   // проверка списка на пустоту

    class iterator {

    };


private:
    struct Node {    // узел списка
        T value;    // значение в узле
        int next;   // индекс следующего узла
        int prev;   // индекс предыдущего узла
        Node() : Node(T(), -1, -1) {};  // конструктор по умолчанию узла
        Node(T value, int next, int prev) : next{-1}, prev{-1} { // конструктор узла
            this->value = value;
            this->next = next;
            this->prev = prev;
        }
    };

    Node* array;    // массив, хранящий узлы
    int head;   // индекс первого элемента списка
    int tail;   // индекс последнего элемента списка
    int firstFree;  // индекс первого свободного элемента в списке
    int capacity;   // емкость списка  
    int size;   // размер списка

    void resize();  // увеличить емкость списка

};

///////////// ПУБЛИЧНЫЕ МЕТОДЫ /////////////

// Конструктор списка
template <typename T>
ArrayList<T>::ArrayList(int capacity) {
    this->capacity = capacity;
    size = 0;
    head = tail = -1;
    firstFree = 0;
    this->array = new Node[this->capacity];
}

// Конструктор копирования
template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T> &other) : head{other.head}, tail{other.tail},
 firstFree{other.firstFree}, capacity{other.capacity}, size{other.size}  {
    this->array = new Node[capacity];
    for (int i = 0; i < capacity; i++) {
        this->array[i] = other.array[i];
    }
}

// Деструктор списка
template <typename T>
ArrayList<T>::~ArrayList()  {
    delete[] array;
}

// Опрос размера списка
template <typename T>
int ArrayList<T>::getSize() {    
    return size;
}

// Проверка списка на пустоту
template <typename T>
bool ArrayList<T>::empty() {
    return size == 0;
}

///////////// ПРИВАТНЫЕ МЕТОДЫ /////////////

template <typename T>
void ArrayList<T>::resize() {
    Node* newArr = new Node[capacity * 2];
    for (int i = 0; i < capacity; i++) {
        newArr[i] = array[i];
    }
    delete[] array;
    array = newArr;
    capacity = capacity * 2;
}

