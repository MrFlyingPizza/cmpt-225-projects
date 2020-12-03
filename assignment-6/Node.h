#ifndef NODE_H
#define NODE_H

#include "AVLTree.h"

class AVLTree::Node {
    friend class AVLTree;
    friend std::ostream& operator<<(std::ostream& os, AVLTree::Node const& node);
private:
    int key_;
    int height_;
    Node *parent_;
    Node *lchild_, *rchild_;

    bool is_end_;

    explicit Node(bool is_end);
    explicit Node(int key = 0);
public:
    int key() const;

    bool operator==(Node const& node);
};

#endif