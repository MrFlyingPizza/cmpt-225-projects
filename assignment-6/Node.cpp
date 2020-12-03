#include "Node.h"

AVLTree::Node::Node(const bool is_end)
: key_(0), height_(-2), parent_(nullptr), lchild_(nullptr), rchild_(nullptr), is_end_(is_end)
{}

AVLTree::Node::Node(const int key)
: key_(key), height_(0), parent_(nullptr), lchild_(nullptr), rchild_(nullptr), is_end_(false)
{}

int AVLTree::Node::key() const
{
    return key_;
}

bool AVLTree::Node::operator==(Node const& node)
{
    return (is_end_ == node.is_end_ && key_ == node.key_);
}