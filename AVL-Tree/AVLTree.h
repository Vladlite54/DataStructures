#include <iostream>
#include <algorithm>

template <typename Key, typename Data>
class AVLTree : public BST<Key, Data> {
private:
    using Node = typename BST<Key, Data>::Node;

    // Вспомогательные методы для балансировки
    int getHeight(Node* node) const {
        if (!node) return 0;
        return std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    int getBalanceFactor(Node* node) const {
        if (!node) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Выполняем поворот
        x->right = y;
        y->left = T2;

        // Обновляем родительские указатели
        x->parent = y->parent;
        y->parent = x;
        if (T2) T2->parent = y;

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Выполняем поворот
        y->left = x;
        x->right = T2;

        // Обновляем родительские указатели
        y->parent = x->parent;
        x->parent = y;
        if (T2) T2->parent = x;

        return y;
    }

    Node* balance(Node* node) {
        if (!node) return nullptr;

        int balanceFactor = getBalanceFactor(node);

        // Left Left Case
        if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0)
            return rotateRight(node);

        // Right Right Case
        if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0)
            return rotateLeft(node);

        // Left Right Case
        if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Итеративная вставка с балансировкой
    bool insertIterative(const Key& key, const Data& data) {
        if (!this->root) {
            this->root = new Node(key, data);
            this->size++;
            return true;
        }

        Node* current = this->root;
        Node* parent = nullptr;
        std::vector<Node*> path; // Для хранения пути вставки

        while (current) {
            BST<Key, Data>::incrementOperationCount();
            parent = current;
            path.push_back(parent);

            if (key == current->key) {
                return false; // Ключ уже существует
            }

            current = (key < current->key) ? current->left : current->right;
        }

        Node* newNode = new Node(key, data);
        newNode->parent = parent;

        if (key < parent->key) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        this->size++;

        // Балансировка вдоль пути вставки
        for (int i = path.size() - 1; i >= 0; --i) {
            Node* node = path[i];
            Node* balanced = balance(node);

            if (balanced != node) {
                if (i == 0) {
                    this->root = balanced;
                } else {
                    Node* parent = path[i-1];
                    if (parent->left == node) {
                        parent->left = balanced;
                    } else {
                        parent->right = balanced;
                    }
                }
            }
        }

        return true;
    }

    // Итеративное удаление с балансировкой
    bool removeIterative(const Key& key) {
        Node* current = this->root;
        Node* parent = nullptr;
        std::vector<Node*> path; // Для хранения пути удаления

        // Поиск узла для удаления
        while (current) {
            BST<Key, Data>::incrementOperationCount();
            if (key == current->key) break;

            parent = current;
            path.push_back(parent);
            current = (key < current->key) ? current->left : current->right;
        }

        if (!current) return false; // Ключ не найден

        path.push_back(current);

        if (!current->left && !current->right) {
            // Нет потомков
            if (parent) {
                if (parent->left == current) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
            } else {
                this->root = nullptr;
            }
            delete current;
        } else if (!current->left || !current->right) {
            // Один потомок
            Node* child = current->left ? current->left : current->right;
            if (parent) {
                if (parent->left == current) {
                    parent->left = child;
                } else {
                    parent->right = child;
                }
                child->parent = parent;
            } else {
                this->root = child;
                child->parent = nullptr;
            }
            delete current;
        } else {
            // Два потомка
            Node* successor = current->right;
            Node* successorParent = current;
            path.push_back(successor);

            while (successor->left) {
                BST<Key, Data>::incrementOperationCount();
                successorParent = successor;
                successor = successor->left;
                path.push_back(successor);
            }

            current->key = successor->key;
            current->data = successor->data;

            if (successorParent->left == successor) {
                successorParent->left = successor->right;
            } else {
                successorParent->right = successor->right;
            }

            if (successor->right) {
                successor->right->parent = successorParent;
            }

            delete successor;
        }

        this->size--;

        // Балансировка вдоль пути удаления
        for (int i = path.size() - 1; i >= 0; --i) {
            Node* node = path[i];
            Node* balanced = balance(node);

            if (balanced != node) {
                if (i == 0) {
                    this->root = balanced;
                } else {
                    Node* parent = path[i-1];
                    if (parent->left == node) {
                        parent->left = balanced;
                    } else {
                        parent->right = balanced;
                    }
                }
            }
        }

        return true;
    }

public:
    AVLTree() : BST<Key, Data>() {}
    
    // Переопределяем методы вставки и удаления
    bool insert(const Key& key, const Data& data) override {
        return insertIterative(key, data);
    }

    bool remove(const Key& key) override {
        return removeIterative(key);
    }

    // Используем реализацию operator[] из BST, так как он использует insert
};