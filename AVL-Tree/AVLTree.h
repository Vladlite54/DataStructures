#pragma once

#include <iostream>
#include <algorithm>

template <typename Key, typename Data>
class AVLTree : public BST<Key, Data> {
private:
    using typename BST<Key, Data>::Node;
    
    struct AVLNode : public Node {  // узел AVL-дерева
        int height; // высота
        
        AVLNode(const Key& k, const Data& d) 
            : Node(k, d), height(1) {}
    };

    // Обновить высоту
    void updateHeight(AVLNode* node) {  // обновить высоту
        int leftHeight = node->left ? static_cast<AVLNode*>(node->left)->height : 0;
        int rightHeight = node->right ? static_cast<AVLNode*>(node->right)->height : 0;
        node->height = 1 + std::max(leftHeight, rightHeight);
    }

    // Получить фактор балансировки
    int getBalance(AVLNode* node) { 
        if (!node) return 0;
        int leftHeight = node->left ? static_cast<AVLNode*>(node->left)->height : 0;
        int rightHeight = node->right ? static_cast<AVLNode*>(node->right)->height : 0;
        return leftHeight - rightHeight; // разность высоты левого и правого поддерева
    }

    // Получить фактор балансировки (метод с модификатором const)
    int getBalance(AVLNode* node) const { 
        if (!node) return 0;
        int leftHeight = node->left ? static_cast<AVLNode*>(node->left)->height : 0;
        int rightHeight = node->right ? static_cast<AVLNode*>(node->right)->height : 0;
        return leftHeight - rightHeight;
    }
    
    // Правый поворот
    Node* rotateRight(Node* y) { 
        BST<Key, Data>::incrementCOUNTER();
        Node* x = y->left;
        y->left = x->right;
        if (x->right) x->right->parent = y;
        x->parent = y->parent;
        
        if (!y->parent) {
            this->root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
        
        x->right = y;
        y->parent = x;
        
        updateHeight(static_cast<AVLNode*>(y));
        updateHeight(static_cast<AVLNode*>(x));
        
        return x;
    }

    // Левый поворот
    Node* rotateLeft(Node* x) {
        BST<Key, Data>::incrementCOUNTER();
        Node* y = x->right;
        x->right = y->left;
        if (y->left) y->left->parent = x;
        y->parent = x->parent;
        
        if (!x->parent) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        
        y->left = x;
        x->parent = y;
        
        updateHeight(static_cast<AVLNode*>(x));
        updateHeight(static_cast<AVLNode*>(y));
        
        return y;
    }

    // Балансировка дерева
    void rebalance(Node* node) {
        if (!node) return;
        
        AVLNode* avlNode = static_cast<AVLNode*>(node);
        updateHeight(avlNode);
        int balance = getBalance(avlNode);

        // условие для LL-поворота
        if (balance > 1 && getBalance(static_cast<AVLNode*>(avlNode->left)) >= 0) {
            if (node == this->root) {
                this->root = rotateRight(node);
            } else {
                rotateRight(node);
            }
            return;
        }

        // условие для RR-поворота
        if (balance < -1 && getBalance(static_cast<AVLNode*>(avlNode->right)) <= 0) {
            if (node == this->root) {
                this->root = rotateLeft(node);
            } else {
                rotateLeft(node);
            }
            return;
        }

        // условие для LR-поворота
        if (balance > 1 && getBalance(static_cast<AVLNode*>(avlNode->left)) < 0) {
            avlNode->left = rotateLeft(avlNode->left);
            if (node == this->root) {
                this->root = rotateRight(node);
            } else {
                rotateRight(node);
            }
            return;
        }

        // условие для RL-поворота
        if (balance < -1 && getBalance(static_cast<AVLNode*>(avlNode->right)) > 0) {
            avlNode->right = rotateRight(avlNode->right);
            if (node == this->root) {
                this->root = rotateLeft(node);
            } else {
                rotateLeft(node);
            }
            return;
        }
    }

public:
    AVLTree() : BST<Key, Data>() {}

    // Вставка
    bool insert(const Key& key, const Data& data) override {
        std::vector<Node*> path;
        Node* current = this->root;
        Node* parent = nullptr;

        // поиск места для вставки
        while (current) {
            BST<Key, Data>::incrementCOUNTER();
            path.push_back(current);
            if (key == current->key) {
                return false;
            }
            parent = current;
            current = (key < current->key) ? current->left : current->right;
        }

        // создание нового узла
        Node* newNode = new AVLNode(key, data);
        newNode->parent = parent;
        
        if (!parent) {
            this->root = newNode;
        } else if (key < parent->key) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        this->size++;
        path.push_back(newNode);

        // балансировка
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            rebalance(*it);
        }

        return true;
    }

    // удаление
    bool remove(const Key& key) override {
        std::vector<Node*> path;
        Node* current = this->root;
        Node* parent = nullptr;

        // поиск узла для удаления
        while (current && current->key != key) {
            BST<Key, Data>::incrementCOUNTER();
            path.push_back(current);
            parent = current;
            current = (key < current->key) ? current->left : current->right;
        }

        if (!current) return false;

        path.push_back(current); // добавляем узел для удаления в путь

        // удаление узла
        if (!current->left || !current->right) {
            Node* child = current->left ? current->left : current->right;
            
            if (!parent) {
                this->root = child;
            } else if (current == parent->left) {
                parent->left = child;
            } else {
                parent->right = child;
            }
            
            if (child) child->parent = parent;
            delete current;
        } else {
            // у узла два потомка
            Node* successor = current->right;
            parent = current;
            path.push_back(successor);
            
            while (successor->left) {
                BST<Key, Data>::incrementCOUNTER();
                parent = successor;
                successor = successor->left;
                path.push_back(successor);
            }

            current->key = successor->key;
            current->data = successor->data;

            if (parent->left == successor) {
                parent->left = successor->right;
            } else {
                parent->right = successor->right;
            }
            
            if (successor->right) {
                successor->right->parent = parent;
            }
            
            delete successor;
        }

        this->size--;

        // балансировка
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            rebalance(*it);
        }

        return true;
    }

    void print() const {
        printTree(static_cast<AVLNode*>(this->root), 0);
    }

private:
    // Вывод дерева на экран
    void printTree(AVLNode* node, int space) const {
        if (!node) return;
        space += 4;
        
        // правое поддерево
        printTree(static_cast<AVLNode*>(node->right), space);
        
        // вывод текущего узла с фактором баланса
        std::cout << std::endl;
        for (int i = 4; i < space; i++) std::cout << " ";
        
        int balance = getBalance(node);
        std::cout << node->key << "[" << balance << "]" << "\n";
        
        // левое поддерево
        printTree(static_cast<AVLNode*>(node->left), space);
    }
};