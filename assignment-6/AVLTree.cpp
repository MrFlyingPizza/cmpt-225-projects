#include <iostream>
#include "AVLTree.h"
#include "Node.h"

AVLTree::Node AVLTree::END = Node(true);

AVLTree::AVLTree()
: size_(0)
{
    root_node_ = new Node();
}

AVLTree::~AVLTree()
{
    destructor(root_node_);
}

void AVLTree::destructor(Node *node)
{
    if (node == nullptr) return;
    destructor(node->lchild_);
    destructor(node->rchild_);
    delete node;
}

int AVLTree::height(Node const* node) const
{
    return (node == nullptr) ? -1 : node->height_;
}

void AVLTree::setHeight(Node *node)
{
    if (node == nullptr) return;
    const int lheight = height(node->lchild_);
    const int rheight = height(node->rchild_);
    node->height_ = (lheight < rheight) ? rheight+1 : lheight+1;
}

AVLTree::Node* AVLTree::rotateLeft(Node *&node)
{
    Node *new_root = node->rchild_;
    node->rchild_ = new_root->lchild_;
    if (node->rchild_ != nullptr) node->rchild_->parent_ = node;
    new_root->lchild_ = node;
    new_root->parent_ = node->parent_;
    node->parent_ = new_root;
    setHeight(node);
    setHeight(new_root);
    node = new_root;
    if (node->parent_ != nullptr)
        setHeight(node->parent_);
    return new_root;
}

AVLTree::Node* AVLTree::rotateRight(Node *&node)
{
    Node *new_root = node->lchild_;
    node->lchild_ = new_root->rchild_;
    if (node->lchild_ != nullptr) node->lchild_->parent_ = node;
    new_root->rchild_ = node;
    new_root->parent_ = node->parent_;
    node->parent_ = new_root;
    setHeight(node);
    setHeight(new_root);
    node = new_root;
    if (node->parent_ != nullptr)
        setHeight(new_root->parent_);
    return node;
}

AVLTree::Node* AVLTree::restructure(Node *&node)
{
    if (node == nullptr) return node;
    setHeight(node);
    if (height(node) < 2) return node;
    if (isBalanced(node) == true) return node;
    Node *new_root = node;
    const int diff = height(node->lchild_) - height(node->rchild_);
    if (diff < -1)
    {
        const int indiff = height(node->rchild_->lchild_) - height(node->rchild_->rchild_);
        if (indiff > 0)
        {
            node->rchild_ = rotateRight(node->rchild_);
        }
        new_root = rotateLeft(node);
    }
    else
    {
        const int indiff = height(node->lchild_->lchild_) - height(node->lchild_->rchild_);
        if (indiff < 0)
        {
            node->lchild_ = rotateLeft(node->lchild_);
        }
        new_root = rotateRight(node);
    }
    node = new_root;
    return new_root;
}

bool AVLTree::isBalanced(Node const* node) const
{
    const int diff = height(node->lchild_) - height(node->rchild_);
    return diff <= 1 && diff >= -1;
}

void AVLTree::rebalance(Node *node)
{
    while (node != nullptr)
    {
        if (node == root_node_)
        {
            restructure(root_node_);
        }
        else
        {
            Node *&child_ref = (node == node->parent_->lchild_)
                ? node->parent_->lchild_ : node->parent_->rchild_;
            restructure(child_ref);
        }
        if (node != nullptr)
            node = node->parent_;
    }
}

void AVLTree::createLeaf(Node *node)
{
    if (node->lchild_ == nullptr)
    {
        node->lchild_ = new Node();
        node->lchild_->parent_ = node;
    }
    if (node->rchild_ == nullptr)
    {
        node->rchild_ = new Node();
        node->rchild_->parent_ = node;
    }
    setHeight(node);
}

AVLTree::Node const* AVLTree::finder(Node const *node, const int k) const
{
    if (height(node) == 0) return (Node*) &AVLTree::END;
    if (node->key_ == k) return node;

    if (node->key_ > k)
        return finder(node->lchild_, k);
    else
        return finder(node->rchild_, k);
}

AVLTree::Node const& AVLTree::find(const int k) const
{
    return *finder(root_node_, k);
}

AVLTree::Node* AVLTree::inserter(Node *node, const int k)
{
    Node *res;
    if (height(node) == 0)
    {
        node->key_ = k;
        createLeaf(node);
        res = node;
    }
    else
    {
        Node *&child = (k < node->key_) ? node->lchild_ : node->rchild_;
        res = inserter(child, k);
    }
    setHeight(node);
    return res;
}

AVLTree::Node const& AVLTree::put(const int k)
{
    Node* res = inserter(root_node_, k);
    rebalance(res->parent_);
    ++size_;
    return *res;
}

void AVLTree::erase(const int k)
{
    if (empty()) return;

    Node **iter = &root_node_;
    while (height(*iter) != 0 && (*iter)->key_ != k)
        iter = (k <= (*iter)->key_) ? &(*iter)->lchild_ : &(*iter)->rchild_;
    Node *&node = *iter;
    
    if (height(node) == 0) return;

    --size_;

    Node *to_del = node, *h_setter = nullptr;
    const int lh = height(node->lchild_), rh = height(node->rchild_);
    if (lh > 0 && rh > 0)
    {
        Node *filler = node->rchild_;
        while (height(filler->lchild_) != 0)
            filler = filler->lchild_;

        Node *&upper_ptr = (filler == node->rchild_) ? node->rchild_ : filler->parent_->lchild_;
        delete filler->lchild_;

        h_setter = filler->rchild_;

        filler->rchild_->parent_ = filler->parent_;
        upper_ptr = filler->rchild_;
        
        filler->lchild_ = node->lchild_;
        filler->rchild_ = node->rchild_;
        node->lchild_->parent_ = filler;
        node->rchild_->parent_ = filler;
        filler->parent_ = node->parent_;
        node = filler;
    }
    else if (lh > 0)
    {
        node->lchild_->parent_ = node->parent_;
        delete node->rchild_;
        node = node->lchild_;
        h_setter = node->parent_;
    }
    else
    {
        node->rchild_->parent_ = node->parent_;
        delete node->lchild_;
        node = node->rchild_;
        h_setter = node->parent_;
    }
    delete to_del;

    Node *rebalancer = h_setter;
    while (h_setter != nullptr)
    {
        setHeight(h_setter);
        h_setter = h_setter->parent_;
    }
    rebalance(rebalancer);
}

int AVLTree::size() const
{
    return size_;
}

bool AVLTree::empty() const
{
    return size_ == 0;
}

AVLTree::Node const& AVLTree::getEnd() const
{
    return END;
}

void AVLTree::recursOStream(std::ostream& os, Node const* node, const int indent_num) const
{
    if (node == nullptr) return;

    for (int i=0; i<indent_num; ++i)
        os << '\t';
    os << *node;
    std::cout << std::endl;
    recursOStream(os, node->lchild_, indent_num+1);
    recursOStream(os, node->rchild_, indent_num+1); 
}

std::ostream& operator<<(std::ostream& os, AVLTree const& tree)
{
    tree.recursOStream(os, tree.root_node_, 0);
    return os;
}

void AVLTree::printRecur(Node *node, int space, short dir)
{
    if (node == nullptr) return;
    printRecur(node->lchild_, space+1, -1);
    for (int i = space; i >= 0; --i)
        std::cout << '\t';

    if (dir == -1) std::cout << '/';
    if (dir == 1) std::cout << '\\';
    if (height(node) == 0)
        std::cout << 'L';
    else
        std::cout << node->key_;
    
    std::cout << " (" << node->height_ << ")";
    //std::cout << "s " << node << " p " << node->parent_ << " l " << node->lchild_ << " r " << node->rchild_;
    std::cout << std::endl;
    printRecur(node->rchild_, space+1, 1);
}

void AVLTree::print()
{
    printRecur(root_node_, 0, 0);
}

std::ostream& operator<<(std::ostream& os, AVLTree::Node const& node)
{
    if (node.height_ == 0)
        os << 'L' << ' ' << '(' << node.height_ << ')';
    else if (node.height_ == -2)
        os << "END";
    else
        os << node.key_ << ' ' << '(' << node.height_ << ')';
    return os;
}