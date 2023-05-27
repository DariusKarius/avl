//
// Created by Dario on 25/05/2023.
//

#ifndef PROYECTO_PRUEBA_H
#define PROYECTO_PRUEBA_H

#endif //PROYECTO_PRUEBA_H
using namespace std;

template <typename TK, typename TV>
struct Entry {
    TK key;
    TV value;

    Entry() {
        key = TK();
        value = TV();
    }

    Entry(TK k, TV v) {
        this->key = k;
        this->value = v;
    }

    bool same_key(Entry a) {
        return a.key == this->key;
    }

    friend ostream& operator<<(ostream& salida, Entry<TK, TV> e) {
        salida << e.key << " " << e.value;
        return salida;
    }
};

template <typename TK, typename TV>
struct NodeT {
    Entry<TK, TV> data;
    NodeT* left;
    NodeT* right;
    int height;
    NodeT() : left(nullptr), right(nullptr), height(0) {}
    NodeT(Entry<TK, TV> value) : data(value), left(nullptr), right(nullptr), height(0) {}

    void killSelf() {
        if (left != nullptr) left->killSelf();
        if (right != nullptr) right->killSelf();
        delete this;
    }
};

template <typename TK, typename TV>
class AVLTree2 {
private:
    NodeT<TK, TV>* root;

public:
    AVLTree2() : root(nullptr) {}
    void insert(TK key, TV value) {
        Entry<TK, TV> entry(key, value);
        insert(this->root, entry);
    }
    bool find(TK key) {
        return find(this->root, key);
    }

    string getInOrder() {
        return getInOrder(this->root);
    }

    int height() {
        return height(this->root);
    }

    Entry<TK, TV> minValue() {
        return minValue(this->root);
    }

    Entry<TK, TV> maxValue() {
        return maxValue(this->root);
    }

    bool isBalanced() {
        return isBalanced(this->root);
    }

    int size() {
        return size(this->root);
    }

    void remove(TK key) {
        remove(this->root, key);
    }

    void displayPretty() {
        displayPretty(this->root, 1);
    }

    Entry<TK, TV> minValue_wp(NodeT<TK, TV>* node) {
        while (node->left != nullptr)
            node = node->left;
        return node->data;
    }

    TK successor(TK key) {
        Entry<TK, TV> entry(key, TV());
        return successor(root, entry).key;
    }

    TK if_not_found_succesor(TK key) {
        Entry<TK, TV> entry(key, TV());
        return if_not_found_succesor(root, entry).key;
    }

    TK if_not_found_predecesor(TK key) {
        Entry<TK, TV> entry(key, TV());
        return if_not_found_predecesor(root, entry).key;
    }

    string search_by_range(TK begin, TK end) {
        if (!find(begin))
            begin = if_not_found_succesor(begin);
        if (!find(end))
            end = if_not_found_predecesor(end);
        return search_by_range(root, begin, end);
    }

    ~AVLTree2() {
        if (this->root != nullptr) {
            this->root->killSelf();
        }
    }

private:
    string getInOrder(NodeT<TK, TV>* node);
    void insert(NodeT<TK, TV>*& node, Entry<TK, TV> entry);
    bool find(NodeT<TK, TV>* node, TK key);
    int height(NodeT<TK, TV>* node);
    bool isBalanced(NodeT<TK, TV>* node);
    Entry<TK, TV> minValue(NodeT<TK, TV>* node);
    Entry<TK, TV> maxValue(NodeT<TK, TV>* node);
    int size(NodeT<TK, TV>* node);
    void remove(NodeT<TK, TV>*& node, TK key);
    void displayPretty(NodeT<TK, TV>* node, int level);
    Entry<TK, TV> successor(NodeT<TK, TV>* node, Entry<TK, TV> entry);

    /*add for avl*/
    int balancingFactor(NodeT<TK, TV>* node);
    void updateHeight(NodeT<TK, TV>* node);
    void balance(NodeT<TK, TV>*& node);
    void left_rota(NodeT<TK, TV>*& node);
    void right_rota(NodeT<TK, TV>*& node);
    string search_by_range(NodeT<TK, TV>* node, TK begin, TK end);
    Entry<TK, TV> if_not_found_succesor(NodeT<TK, TV>* node, Entry<TK, TV> entry);
    Entry<TK, TV> if_not_found_predecesor(NodeT<TK, TV>* node, Entry<TK, TV> entry);
};

template <typename TK, typename TV>
bool AVLTree2<TK, TV>::find(NodeT<TK, TV>* node, TK key) {
    if (node == nullptr)
        return false;
    else if (key < node->data.key)
        return find(node->left, key);
    else if (key > node->data.key)
        return find(node->right, key);
    else
        return true;
}

template <typename TK, typename TV>
bool AVLTree2<TK, TV>::isBalanced(NodeT<TK, TV>* node) //O(n^2)
{
    if (node == nullptr)
        return true;
    else
        return abs(height(node->left) - height(node->right)) <= 1 && isBalanced(node->left) && isBalanced(node->right);
}

template <typename TK, typename TV>
Entry<TK, TV> AVLTree2<TK, TV>::minValue(NodeT<TK, TV>* node) {
    if (node == nullptr)
        throw("The tree is empty");
    else if (node->left == nullptr)
        return node->data;
    else
        return minValue(node->left);
}

template <typename TK, typename TV>
Entry<TK, TV> AVLTree2<TK, TV>::maxValue(NodeT<TK, TV>* node) {
    if (node == nullptr)
        throw("The tree is empty");
    else if (node->right == nullptr)
        return node->data;
    else
        return maxValue(node->right);
}

template <typename TK, typename TV>
int AVLTree2<TK, TV>::size(NodeT<TK, TV>* node) {
    if (node == nullptr)
        return 0;
    else
        return 1 + size(node->left) + size(node->right);
}

template <typename TK, typename TV>
string AVLTree2<TK, TV>::getInOrder(NodeT<TK, TV>* node) {
    string result = "";
    if (node != nullptr) {
        result += getInOrder(node->left);
        result += node->data.key + " - " + node->data.value + "\n";
        result += getInOrder(node->right);
    }
    return result;
}

template <typename TK, typename TV>
void AVLTree2<TK, TV>::insert(NodeT<TK, TV>*& node, Entry<TK, TV> entry) {
    if (node == nullptr)
        node = new NodeT<TK, TV>(entry);
    else if (entry.key < node->data.key)
        insert(node->left, entry);
    else
        insert(node->right, entry);

    //regreso de la recursividad
    updateHeight(node);
    balance(node);
}

template <typename TK, typename TV>
int AVLTree2<TK, TV>::height(NodeT<TK, TV>* node) {
    if (node == nullptr) return -1;
    else return node->height;
}

template <typename TK, typename TV>
int AVLTree2<TK, TV>::balancingFactor(NodeT<TK, TV>* node) {
    return height(node->left) - height(node->right);
}

template <typename TK, typename TV>
void AVLTree2<TK, TV>::updateHeight(NodeT<TK, TV>* node) {
    node->height = max(height(node->left), height(node->right)) + 1;
}

template <typename TK, typename TV>
void AVLTree2<TK, TV>::balance(NodeT<TK, TV>*& node) {
    int bf = balancingFactor(node);
    if (bf >= 2) { //esta cargado a la izquierda
        if (balancingFactor(node->left) < 0) //verifica rotacion doble
            left_rota(node->left);
        right_rota(node);
    }
    else if (bf <= -2) { //esta cargado a la derecha
        if (balancingFactor(node->right) > 0) //verifica rotacion doble
            right_rota(node->right);
        left_rota(node);
    }
}

template <typename TK, typename TV>
void AVLTree2<TK, TV>::left_rota(NodeT<TK, TV>*& parent) {
    NodeT<TK, TV>* child = parent->right;
    parent->right = child->left;
    child->left = parent;
    //update height
    updateHeight(parent);
    updateHeight(child);
    parent = child;
}

template <typename TK, typename TV>
void AVLTree2<TK, TV>::right_rota(NodeT<TK, TV>*& parent) {
    NodeT<TK, TV>* child = parent->left;
    parent->left = child->right;
    child->right = parent;
    //update height
    updateHeight(parent);
    updateHeight(child);
    parent = child;
}

template <typename TK, typename TV>
void AVLTree2<TK, TV>::remove(NodeT<TK, TV>*& node, TK key) {
    if (node == nullptr)
        return;
    else if (key < node->data.key)
        remove(node->left, key);
    else if (key > node->data.key)
        remove(node->right, key);
    else {
        if (node->left == nullptr && node->right == nullptr) { //no children
            delete node;
            node = nullptr;
        }
        else if (node->left != nullptr && node->right == nullptr) { //only left child
            NodeT<TK, TV>* temp = node;
            node = node->left;
            delete temp;
        }
        else if (node->left == nullptr && node->right != nullptr) { //only right child
            NodeT<TK, TV>* temp = node;
            node = node->right;
            delete temp;
        }
        else { //two children
            Entry<TK, TV> succesor = minValue(node->right);
            node->data = succesor;
            remove(node->right, succesor.key);
        }

        updateHeight(node);
        balance(node);
    }
}

template <typename TK, typename TV>
void AVLTree2<TK, TV>::displayPretty(NodeT<TK, TV>* node, int level) {
    if (node != nullptr) {
        displayPretty(node->right, level + 1);
        cout << endl;
        if (node == root)
            cout << "Root -> ";
        for (int i = 0; i < level && node != root; i++)
            cout << "        ";
        cout << node->data.key;
        displayPretty(node->left, level + 1);
    }
}

template <typename TK, typename TV>
Entry<TK, TV> AVLTree2<TK, TV>::successor(NodeT<TK, TV>* node, Entry<TK, TV> entry) {
    if (node == nullptr)
        return entry;
    if (entry.key < node->data.key) {
        entry = node->data;
        return successor(node->left, entry);
    }
    else
        return successor(node->right, entry);
}

template <typename TK, typename TV>
Entry<TK, TV> AVLTree2<TK, TV>::if_not_found_succesor(NodeT<TK, TV>* node, Entry<TK, TV> entry) {
    if (node == nullptr)
        return entry;
    if (entry.key < node->data.key) {
        entry = node->data;
        return if_not_found_succesor(node->left, entry);
    }
    else
        return if_not_found_succesor(node->right, entry);
}

template <typename TK, typename TV>
Entry<TK, TV> AVLTree2<TK, TV>::if_not_found_predecesor(NodeT<TK, TV>* node, Entry<TK, TV> entry) {
    if (node == nullptr)
        return entry;
    if (entry.key > node->data.key) {
        entry = node->data;
        return if_not_found_predecesor(node->right, entry);
    }
    else
        return if_not_found_predecesor(node->left, entry);
}

template <typename TK, typename TV>
string AVLTree2<TK, TV>::search_by_range(NodeT<TK, TV>* node, TK begin, TK end) {
    string result = "";
    if (node != nullptr) {
        if (node->data.key > begin)
            result += search_by_range(node->left, begin, end);
        if (node->data.key >= begin && node->data.key <= end)
            result += node->data.key + " - " + node->data.value + "\n";
        if (node->data.key < end)
            result += search_by_range(node->right, begin, end);
    }
    return result;
}