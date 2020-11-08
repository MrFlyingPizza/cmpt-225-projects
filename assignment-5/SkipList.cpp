#include <string>

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