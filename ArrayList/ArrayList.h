#pragma once

#include <iostream>

template<typename T>
class ArrayList {
public:
    ArrayList(int capacity);    // конструктор списка
    ArrayList(const ArrayList<T> &other);  // конструктор копирования
    ~ArrayList();   // деструктор
    int size(); // опрос размера списка
    void clear();   // очистка списка
    bool empty();   // проверка списка на пустоту


private:
    class Node {    // узел списка
    public:
        T value;    // значение в узле
        int next;   // индекс следующего узла
        int prev;   // индекс предыдущего узла
        Node(T value);  // конструктор узла
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
    array = new Node[this->capacity];
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


// Конструктор узла списка
template <typename T>
ArrayList<T>::Node::Node(T value) {
    this->value = value;
    this->next = -1;
    this->prev = -1;
}


