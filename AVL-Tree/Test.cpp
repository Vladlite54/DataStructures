#include "Test.h"

//функция установки первого случайного числа от часов компьютера
void sRand() { 
    srand(time(0)); 
    RRand = (INT_64)rand();
}
//функция генерации случайного числа
//линейный конгруэнтный генератор Xi+1=(a*Xi+c)%m
//habr.com/ru/post/208178
INT_64 LineRand() {
    INT_64 y1,y2;
    y1= (aRand*RRand+cRand) % mRand;
    y2= (aRand*y1+cRand) % mRand;
    RRand = y1 & 0xFFFFFFFF00000000LL ^ (y2 & 0xFFFFFFFF00000000LL) >> 32;
    return RRand;
}

void test_rand(int n)
{
    int found;
    //создание дерева для 64 – разрядных ключей типа INT_64
    BST<INT_64, int> tree;
    //массив для ключей, которые присутствуют в дереве
    INT_64* m = new INT_64[n];
    //установка первого случайного числа
    sRand();
    //заполнение дерева и массива элементами со случайными ключами
    for(int i=0; i<n; i++) {
        m[i] = LineRand();
        tree.insert(m[i],1);
    }
    //вывод размера дерева до теста
    cout <<"items count: "<< tree.getSize() << endl;
    //обнуление счётчиков трудоёмкости вставки, удаления и поиска
    double I = 0;
    double D = 0;
    double S = 0;
    //генерация потока операций, 10% - промахи операций
    for(int i=0;i<n/2;i++) {
        if(i%10==0) { //10% промахов 
            BST<INT_64, int>::resetCOUNTER();
            tree.remove(LineRand());
            D += BST<INT_64, int>::getCOUNTER();

            BST<INT_64, int>::resetCOUNTER();
            tree.insert(m[rand()%n], 1);
            I += BST<INT_64, int>::getCOUNTER();

            try {
                BST<INT_64, int>::resetCOUNTER();
                found = tree[LineRand ()];
                S += BST<INT_64, int>::getCOUNTER();
            }
            //обработка исключения при ошибке операции поиска
            catch(std::exception &e)  {
                S += BST<INT_64, int>::getCOUNTER();
            }
        }
        else { //90% успешных операций
            int ind = rand() % n;
            BST<INT_64, int>::resetCOUNTER();
            tree.remove(m[ind]);
            D += BST<INT_64, int>::getCOUNTER();
            
            INT_64 key= LineRand();
            BST<INT_64, int>::resetCOUNTER();
            tree.insert(key, 1);
            I += BST<INT_64, int>::getCOUNTER();

            m[ind] = key;
            try {
                BST<INT_64, int>::resetCOUNTER();
                found = tree[m[rand() % n]];
                S += BST<INT_64, int>::getCOUNTER();
            }
            //обработка исключения при ошибке операции поиска
            catch(std::exception &e) {
                S += BST<INT_64, int>::getCOUNTER();
            }
        } //конец теста
    }
    //вывод результатов:
    //вывод размера дерева после теста
    cout << "items count: "<< tree.getSize() << endl;
    //теоретической оценки трудоёмкости операций BST
    cout << "1.39*log2(n)= "<< 1.39 * (log((double)n) / log(2.0)) << endl;
    //экспериментальной оценки трудоёмкости вставки
    cout << "Count insert: " << I / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости удаления
    cout << "Count delete: " << D / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости поиска
    cout << "Count search: " << S / (n / 2) << endl;
    //освобождение памяти массива m[]
    delete[] m;
}

void test_ord(int n) {
    int found;
    //создание дерева для 64 – разрядных ключей типа INT_64
    BST<INT_64, int> tree;
    //массив для ключей, которые присутствуют в дереве
    INT_64* m = new INT_64[n];
    //заполнение дерева и массива элементами с возрастающими чётными
    //ключами на интервале [0, 10000, 20000, ... ,10000*n]
    for(int i = 0; i < n; i++) {
        m[i]= i*10000;
        tree.insert(m[i],1);
    }
    //вывод размера дерева до теста
    cout << "items count:" << tree.getSize() << endl;
    //обнуление счётчиков трудоёмкости вставки, удаления и поиска
    double I = 0;
    double D = 0;
    double S = 0;
    //установка первого случайного числа
    sRand ();
    //генерация потока операций, 10% - промахи операций
    for(int i = 0; i < n / 2; i++) {
        if(i%10==0) { //10% промахов
            int k = LineRand() % (10000*n);
            k = k + !(k % 2); //случайный нечётный ключ
            BST<INT_64, int>::resetCOUNTER();
            tree.remove(k);
            D += BST<INT_64, int>::getCOUNTER();

            BST<INT_64, int>::resetCOUNTER();
            tree.insert(m[rand() % n], 1);
            I += BST<INT_64, int>::getCOUNTER();

            k = LineRand() % (10000 * n);
            k = k + !(k%2); // случайный нечётный ключ
            try {
                BST<INT_64, int>::resetCOUNTER();
                found = tree[k];
                S += BST<INT_64, int>::getCOUNTER();
            }
            //обработка исключения при ошибке операции поиска
            catch(std::exception &e) {
                S += BST<INT_64, int>::getCOUNTER();
            }
        }
        else { //90% успешных операций
            int ind = rand() % n;
            BST<INT_64, int>::resetCOUNTER();
            tree.remove(m[ind]);
            D += BST<INT_64, int>::getCOUNTER();

            int k = LineRand() % (10000 * n);
            k = k + k % 2; // случайный чётный ключ
            BST<INT_64, int>::resetCOUNTER();
            tree.insert(k, 1);
            I += BST<INT_64, int>::getCOUNTER();

            m[ind] = k;
            try {
                BST<INT_64, int>::resetCOUNTER();
                found = tree[m[rand() % n]];
                S += BST<INT_64, int>::getCOUNTER();
            }
            //обработка исключения при ошибке операции поиска
            catch(std::exception &e) {
                S += BST<INT_64, int>::getCOUNTER();
            }
        }
    }

    //вывод результатов:
    // вывод размера дерева после теста
    cout << "items count: " << tree.getSize() << endl;
    //теоретической оценки трудоёмкости операций BST
    cout << "n/2 = " << n / 2 << endl;
    //экспериментальной оценки трудоёмкости вставки
    cout << "Count insert: " << I / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости удаления
    cout << "Count delete: " << D / (n / 2) <<endl;
    //экспериментальной оценки трудоёмкости поиска
    cout << "Count search: " << S / (n / 2) <<endl;
    //освобождение памяти массива m[]

    delete[] m;
} //конец теста

void test_rand_avl(int n)
{
    int found;
    //создание дерева для 64 – разрядных ключей типа INT_64
    AVLTree<INT_64, int> tree;
    //массив для ключей, которые присутствуют в дереве
    INT_64* m = new INT_64[n];
    //установка первого случайного числа
    sRand();
    //заполнение дерева и массива элементами со случайными ключами
    for(int i=0; i<n; i++) {
        m[i] = LineRand();
        tree.insert(m[i],1);
    }
    //вывод размера дерева до теста
    cout <<"items count: "<< tree.getSize() << endl;
    //обнуление счётчиков трудоёмкости вставки, удаления и поиска
    double I = 0;
    double D = 0;
    double S = 0;
    //генерация потока операций, 10% - промахи операций
    for(int i=0;i<n/2;i++) {
        if(i%10==0) { //10% промахов 
            BST<INT_64, int>::resetCOUNTER();
            tree.remove(LineRand());
            D += BST<INT_64, int>::getCOUNTER();

            BST<INT_64, int>::resetCOUNTER();
            tree.insert(m[rand()%n], 1);
            I += BST<INT_64, int>::getCOUNTER();

            try {
                BST<INT_64, int>::resetCOUNTER();
                found = tree[LineRand ()];
                S += BST<INT_64, int>::getCOUNTER();
            }
            //обработка исключения при ошибке операции поиска
            catch(std::exception &e)  {
                S += BST<INT_64, int>::getCOUNTER();
            }
        }
        else { //90% успешных операций
            int ind = rand() % n;
            BST<INT_64, int>::resetCOUNTER();
            tree.remove(m[ind]);
            D += BST<INT_64, int>::getCOUNTER();
            
            INT_64 key= LineRand();
            BST<INT_64, int>::resetCOUNTER();
            tree.insert(key, 1);
            I += BST<INT_64, int>::getCOUNTER();

            m[ind] = key;
            try {
                BST<INT_64, int>::resetCOUNTER();
                found = tree[m[rand() % n]];
                S += BST<INT_64, int>::getCOUNTER();
            }
            //обработка исключения при ошибке операции поиска
            catch(std::exception &e) {
                S += BST<INT_64, int>::getCOUNTER();
            }
        } //конец теста
    }
    //вывод результатов:
    //вывод размера дерева после теста
    cout << "items count: "<< tree.getSize() << endl;
    //теоретической оценки трудоёмкости операций BST
    cout << "1.39*log2(n)= "<< 1.39 * (log((double)n) / log(2.0)) << endl;
    //экспериментальной оценки трудоёмкости вставки
    cout << "Count insert: " << I / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости удаления
    cout << "Count delete: " << D / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости поиска
    cout << "Count search: " << S / (n / 2) << endl;
    //освобождение памяти массива m[]
    delete[] m;
}

void test_ord_avl(int n) {
    int found;
    //создание дерева для 64 – разрядных ключей типа INT_64
    AVLTree<INT_64, int> tree;
    //массив для ключей, которые присутствуют в дереве
    INT_64* m = new INT_64[n];
    //заполнение дерева и массива элементами с возрастающими чётными
    //ключами на интервале [0, 10000, 20000, ... ,10000*n]
    for(int i = 0; i < n; i++) {
        m[i]= i*10000;
        tree.insert(m[i],1);
    }
    //вывод размера дерева до теста
    cout << "items count:" << tree.getSize() << endl;
    //обнуление счётчиков трудоёмкости вставки, удаления и поиска
    double I = 0;
    double D = 0;
    double S = 0;
    //установка первого случайного числа
    sRand ();
    //генерация потока операций, 10% - промахи операций
    for(int i = 0; i < n / 2; i++) {
        if(i%10==0) { //10% промахов
            int k = LineRand() % (10000*n);
            k = k + !(k % 2); //случайный нечётный ключ
            BST<INT_64, int>::resetCOUNTER();
            tree.remove(k);
            D += BST<INT_64, int>::getCOUNTER();

            BST<INT_64, int>::resetCOUNTER();
            tree.insert(m[rand() % n], 1);
            I += BST<INT_64, int>::getCOUNTER();

            k = LineRand() % (10000 * n);
            k = k + !(k%2); // случайный нечётный ключ
            try {
                BST<INT_64, int>::resetCOUNTER();
                found = tree[k];
                S += BST<INT_64, int>::getCOUNTER();
            }
            //обработка исключения при ошибке операции поиска
            catch(std::exception &e) {
                S += BST<INT_64, int>::getCOUNTER();
            }
        }
        else { //90% успешных операций
            int ind = rand() % n;
            BST<INT_64, int>::resetCOUNTER();
            tree.remove(m[ind]);
            D += BST<INT_64, int>::getCOUNTER();

            int k = LineRand() % (10000 * n);
            k = k + k % 2; // случайный чётный ключ
            BST<INT_64, int>::resetCOUNTER();
            tree.insert(k, 1);
            I += BST<INT_64, int>::getCOUNTER();

            m[ind] = k;
            try {
                BST<INT_64, int>::resetCOUNTER();
                found = tree[m[rand() % n]];
                S += BST<INT_64, int>::getCOUNTER();
            }
            //обработка исключения при ошибке операции поиска
            catch(std::exception &e) {
                S += BST<INT_64, int>::getCOUNTER();
            }
        }
    }

    //вывод результатов:
    // вывод размера дерева после теста
    cout << "items count: " << tree.getSize() << endl;
    //теоретической оценки трудоёмкости операций BST
    cout << "1.39*log2(n)= "<< 1.39 * (log((double)n) / log(2.0)) << endl;
    //экспериментальной оценки трудоёмкости вставки
    cout << "Count insert: " << I / (n / 2) << endl;
    //экспериментальной оценки трудоёмкости удаления
    cout << "Count delete: " << D / (n / 2) <<endl;
    //экспериментальной оценки трудоёмкости поиска
    cout << "Count search: " << S / (n / 2) <<endl;
    //освобождение памяти массива m[]

    delete[] m;
} //конец теста