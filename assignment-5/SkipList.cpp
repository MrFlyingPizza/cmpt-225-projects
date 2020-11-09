#include <string>
#include <iostream>

#include "Entry.h"
#include "SkipList.h"

SkipList::QuadNode::QuadNode(Entry const& entry)
: entry_(entry), prev_(nullptr), next_(nullptr), below_(nullptr), above_(nullptr)
{}

SkipList::QuadNode::QuadNode(const int inf_key)
: entry_(inf_key), prev_(nullptr), next_(nullptr), below_(nullptr), above_(nullptr)
{}


SkipList::SkipList()
: size_(0), max_level_(0)
{
    lnode_ = new QuadNode(Entry::MINUS_INF);
    lnode_->next_ = new QuadNode(Entry::PLUS_INF);
    rnode_ = lnode_->next_;
    base_node_ = lnode_;
}

SkipList::~SkipList()
{
    QuadNode *vnode = lnode_, *hnode = lnode_, *temp;
    while (vnode != nullptr)
    {
        hnode = vnode;
        vnode = vnode->below_;
        while (hnode != nullptr)
        {
            temp = hnode;
            hnode = hnode->next_;
            delete temp;
        }
    }
}

Entry const& SkipList::find(const int k) const
{
    if (k < 0) throw NegativeKeyException();

    QuadNode* current = lnode_;
    QuadNode* next = current->next_;
    while (current->entry_.getKey() != k)
    {
        current = (next->entry_.getKey() == Entry::PLUS_INF.getKey()) 
            ? current->below_ : current->next_;

        if (current == nullptr)
            return Entry::END;

        next = current->next_;
    }
    return current->entry_;
}

Entry const& SkipList::lesserEntry(const int k) const
{
    if (k < 0) throw NegativeKeyException();
    if (empty()) return Entry::MINUS_INF;

    QuadNode* current = lnode_;
    QuadNode* ahead = current->next_;
    while (ahead->entry_.getKey() < k || current->below_ != nullptr)
    {
        current = (ahead->entry_.getKey() >= k 
            || ahead->entry_.getKey() == Entry::PLUS_INF.getKey()) 
                ? current->below_ : current->next_;

        ahead = current->next_;
    }
    return current->entry_;
}

Entry const& SkipList::greaterEntry(const int k) const
{
    if (k < 0) throw NegativeKeyException();
    if (empty()) return Entry::PLUS_INF;

    QuadNode* current = rnode_;
    QuadNode* ahead = current->prev_;
    while (ahead->entry_.getKey() > k || current->below_ != nullptr)
    {
        current = (ahead->entry_.getKey() <= k 
            || ahead->entry_.getKey() == Entry::MINUS_INF.getKey()) 
                ? current->below_ : current->prev_;

        ahead = current->prev_;
    }
    return current->entry_;
}

SkipList::QuadNode* SkipList::listInsert(QuadNode* node, Entry k) const
{
    while (node->next_->entry_.getKey() < k.getKey() 
        && node->next_->entry_.getKey() != Entry::PLUS_INF.getKey())
    {
        node = node->next_;
    }

    QuadNode* insertion_node = new QuadNode(k);
    QuadNode* old_next = node->next_;
    node->next_ = insertion_node;
    insertion_node->next_ = old_next;

    return insertion_node;
}

void SkipList::put(const int k, const std::string v)
{
    int count = 1;
    while (rand()%2 != 0) ++count;

    if (count >= max_level_)
    {
        for (int i = 0; i <= count-max_level_; ++i)
        {
            lnode_->above_ = new QuadNode(Entry::MINUS_INF);
            rnode_->above_ = new QuadNode(Entry::PLUS_INF);
            lnode_ = lnode_->above_;
            rnode_ = rnode_->above_;
            lnode_->next_ = rnode_;
            ++max_level_;
        }
    }
    
    QuadNode* descend_node = lnode_->below_;
    QuadNode* inserted_node;
    QuadNode* old_inserted_node = nullptr;
    while (descend_node != nullptr)
    {
        inserted_node = listInsert(descend_node, Entry(k, v));
        inserted_node->above_ = old_inserted_node;
        descend_node = descend_node->below_;
    }

}

void SkipList::erase(const int k)
{

}

int SkipList::size() const
{
    return size_;
}

bool SkipList::empty() const
{
    return size_ <= 0;
}

void SkipList::print() const
{
    QuadNode* descend_node = lnode_;
    QuadNode* iter_node;
    QuadNode* searcher_node;
    int hpos;
    std::cout << "print\n";
    while (descend_node != nullptr)
    {
        std::cout << "entered loop\n";
        std::cout << "-INF --";
        iter_node = descend_node;
        searcher_node = base_node_;
        while (iter_node != nullptr)
        {
            std::cout << "entered second loop\n";
            hpos = 0;
            while (searcher_node->entry_.getKey() != iter_node->entry_.getKey())
            {
                ++hpos;
                searcher_node = searcher_node->next_;
            }
            
            for (int i = 0; i < hpos; ++i)
                std::cout << "--";

            std::cout << iter_node->entry_.getKey() << "--";
            std::cout << searcher_node->entry_.toString() << " ?= " << iter_node->entry_.toString() << std::endl;
            iter_node = iter_node->next_;

        }
        std::cout << " +INF" << std::endl;
        descend_node = descend_node->below_;
    }
}
