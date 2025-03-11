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
    bool contains(T target);  // опрос наличия заданного значения
    T& getAt(int index); // чтение значения с заданным номером в списке 
    void setAt(int index, T value); // изменение значения с заданным номером в списке
    int find(T target); // получение позиции в списке для заданного значения
    void add(T value);  // включение нового значения
    void insert(int index, T value); // включение нового значения с заданным номером
    void erase(T value); // удаление заданного значения в списке
    void eraseAt(int index); // удаление значения с позиции с заданным номером
    void print();
    void printFull();

    class iterator {

    };


private:
    struct Node {    // узел списка
        T value;    // значение в узле
        int next;   // индекс следующего узла
        int prev;   // индекс предыдущего узла
        Node() : value{}, next{-1}, prev{-1} {};  // конструктор по умолчанию узла
        Node(T value) { // конструктор узла
            this->value = value;
            this->next = -1;
            this->prev = -1;
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
    for (int i = 0; i < capacity - 1; ++i) {
        array[i].next = i + 1;
    }
    array[capacity - 1].next = -1;
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

// Очистка списка
template <typename T>
void ArrayList<T>::clear()  {
    head = tail = -1;
    firstFree = size = 0;
    for (int i = 0; i < capacity - 1; ++i) {
        array[i].next = i + 1; 
        array[i].prev = -1;
        array[i] = T{};
    }
    array[capacity - 1].next = array[capacity - 1].prev = -1;
    
}

// Проверка списка на пустоту
template <typename T>
bool ArrayList<T>::empty() {
    return size == 0;
}

// Опрос наличия заданного значения
template <typename T>
bool ArrayList<T>::contains(T target) {
    return find(target) != -1;
}

// Чтение значения с заданным номеров в списке
template <typename T>
T &ArrayList<T>::getAt(int index) {
    if (index < 0 || index > size) throw std::out_of_range("Out of range");
    int current = head;
    int j = 0;
    while(j <= index) {
        if(j == index) break;
        ++j;
        current = array[current].next;
    }
    return array[current].value;
}

// Именение значения с заданным номером в списке
template <typename T>
void ArrayList<T>::setAt(int index, T value) {
    getAt(index) = value;

}

// Получение позиции в списке для заданного значения
template <typename T>
int ArrayList<T>::find(T target) {
    int i = 0;
    int current = head;
    while(i < size) {
        if (array[current].value == target) return current;
        current = array[current].next;
        ++i;
    }
    return -1;
}

// Включение нового значения
template <typename T>
void ArrayList<T>::add(T value) {
    if (size == capacity) resize();
    int insertionIndex = firstFree;
    firstFree = array[firstFree].next;
    array[insertionIndex].value = value;
    array[insertionIndex].prev = tail;
    if (tail != -1) array[tail].next = insertionIndex;
    if (head == -1) head = insertionIndex;
    tail = insertionIndex;
    ++size;
}

// Включение нового значения с заданным номером
template <typename T>
void ArrayList<T>::insert(int index, T value) {
    if(index < 0 || index > size) throw std::out_of_range("Out of range");
    if (size == capacity) resize();
    if (index == size) {
        add(value);
        return;
    };
    int insertIndex = firstFree;
    firstFree = array[firstFree].next;
    if (index == 0) {
        array[insertIndex].value = value;
        array[insertIndex].next = head;
        if (head != -1) array[head].prev = insertIndex;
        if(tail == -1) tail = insertIndex;
        head = insertIndex;
    }
    else {
        array[insertIndex] = value;
        int previous = head;
        for (int i = 0; i < index - 1; ++i) {
            previous = array[previous].next;
        }
        array[insertIndex].prev = previous;
        array[insertIndex].next = array[previous].next;
        array[array[previous].next].prev = insertIndex;
        array[previous].next = insertIndex;
    }
    ++size;
}

template <typename T>
inline void ArrayList<T>::print() {
    for(int i = head, j = 0; j < size; i = array[i].next, ++j) {
        std::cout << array[i].value << " ";
    }
    std::cout << std::endl;
}

template <typename T>
inline void ArrayList<T>::printFull() {
    for(int i = 0; i < capacity; ++i) {
        std::cout << array[i].value << " ";
    }
    std::cout << std::endl;
}

///////////// ПРИВАТНЫЕ МЕТОДЫ /////////////

// Увеличить емкость списка
template <typename T>
void ArrayList<T>::resize() {
    capacity = capacity * 2;
    Node* newArr = new Node[capacity];
    for (int i = 0; i < size; ++i) {
        newArr[i] = array[i];
    }
    for (int i = size; i < capacity - 1; ++i) {
        newArr[i].next = i + 1;
    }
    firstFree = size;
    delete[] array;
    array = newArr;
}

