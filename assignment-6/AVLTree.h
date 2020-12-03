#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <ostream>

class AVLTree {
private:
    class Node;
    
    friend std::ostream& operator<<(std::ostream& os, AVLTree const& tree);
    friend std::ostream& operator<<(std::ostream& os, AVLTree::Node const& node);

    Node* root_node_;
    int size_;

    Node const* finder(Node const* node, int k) const;
    void createLeaf(Node *node);
    Node* inserter(Node *node, int k);
    void recursOStream(std::ostream& os, Node const* node, int indent_num) const;
    int height(Node const* node) const;
    void setHeight(Node *node);
    AVLTree::Node* restructure(Node *&node);
    AVLTree::Node* rotateLeft(Node *&node);
    AVLTree::Node* rotateRight(Node *&node);
    void destructor(Node *node);
    bool isBalanced(Node const* node) const;
    void rebalance(Node *node);
    void printRecur(Node *node, int space, short dir);

public:
    AVLTree();
    ~AVLTree();

    static Node END;

    Node const& find(int k) const;

    Node const& put(int k);
    void erase(int k);

    int size() const;
    bool empty() const;
    Node const& getEnd() const;
    void print();
};

#endif