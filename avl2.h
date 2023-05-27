#ifndef AVLTree_H
#define AVLTree_H
#include "nodeavl.h"
#include "stack"
#include "queue"

using namespace std;

template <typename TK, typename TV>
class AVLTree{
private:
    NodeT<TK,TV>* root;
    void insert(NodeT<TK,TV>* &node, TK key, TV value);

public:
    AVLTree() : root(nullptr) {}

    void insert(TK key, TV value){
        insert(this->root, key, value);
    }

};

template <typename TK, typename TV>
void AVLTree<TK,TV>::insert(NodeT<TK, TV> *&node, TK key, TV value) {
    if (node == nullptr)
        node = new NodeT<TK,TV>(key,value);
    else if (value < node->data->value)
        insert(node->left, key, value);
    else
        insert(node->right, value);
}