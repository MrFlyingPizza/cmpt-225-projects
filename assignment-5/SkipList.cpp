#include <string>
#include <iostream>

#include "Entry.h"
#include "QuadNode.h"
#include "SkipList.h"


SkipList::SkipList()
: size_(0), max_level_(0)
{
    lnode_ = new QuadNode(QuadNode::M_INF);
    lnode_->next_= new QuadNode(QuadNode::P_INF);
    rnode_ = lnode_->next_;
    base_node_ = lnode_;
}

SkipList::~SkipList()
{
    QuadNode *vnode = lnode_,
        *hnode, *temp;

    while (vnode != nullptr)
    {
        hnode = vnode;
        while (hnode != nullptr)
        {
            temp = hnode;
            hnode = hnode->next_;

            if (!temp->entry_->isKeyEqual(Entry::M_INF)
                && !temp->entry_->isKeyEqual(Entry::P_INF))
                delete temp->entry_;
            
            if (temp != nullptr)
                delete temp;
        }
        vnode = vnode->below_;
    }
    
}

Entry const& SkipList::find(const int k) const
{
    QuadNode *current = lnode_;
    QuadNode *next = current;
    while (current->entry_->getKey() != k && current != nullptr)
    {
        next = current->next_;
        current = (*next == QuadNode::P_INF) ? current->below_ : current->next_;
    }
    return (current == nullptr) ? Entry::END_ENTRY : *current->entry_;
}

Entry const& SkipList::lesserEntry(const int k) const
{
    if (empty()) return Entry::M_INF;

    QuadNode* current = lnode_;
    QuadNode* ahead = current->next_;
    while (ahead->entry_->getKey() < k || current->below_ != nullptr)
    {
        current = (ahead->entry_->getKey() >= k 
            || *ahead == QuadNode::P_INF) 
                ? current->below_ : current->next_;

        ahead = current->next_;
    }
    return *current->entry_;
}

Entry const& SkipList::greaterEntry(const int k) const
{
    if (empty()) return Entry::P_INF;

    QuadNode* current = rnode_;
    QuadNode* ahead = current->prev_;
    while (ahead->entry_->getKey() > k || current->below_ != nullptr)
    {
        current = (ahead->entry_->getKey() <= k 
            || *ahead == QuadNode::M_INF) 
                ? current->below_ : current->prev_;

        ahead = current->prev_;
    }
    return *current->entry_;
}

SkipList::QuadNode* SkipList::listInsert(
    QuadNode* node, const int k, const std::string v) const
{
    QuadNode* insertion_node = new QuadNode(new Entry(k, v));
    
    while (*node->next_->entry_ < *insertion_node->entry_
        && *node->next_ != QuadNode::P_INF)
    {
        node = node->next_;
    }

    QuadNode* old_next = node->next_;
    node->next_ = insertion_node;
    insertion_node->next_ = old_next;

    return insertion_node;
}

void SkipList::put(const int k, const std::string v)
{
    int count = 1;
    while (rand()%2 != 0) ++count;

    QuadNode *temp_lnode, *temp_rnode;
    if (count >= max_level_)
    {
        for (int i = 0; i <= count-max_level_; ++i)
        {
            lnode_->above_ = new QuadNode(QuadNode::M_INF);
            rnode_->above_ = new QuadNode(QuadNode::P_INF);

            temp_lnode = lnode_;
            temp_rnode = rnode_;

            lnode_ = lnode_->above_;
            rnode_ = rnode_->above_;

            lnode_->below_ = temp_lnode;
            rnode_->below_ = temp_rnode;

            lnode_->next_ = rnode_;
            rnode_->prev_ = lnode_;
            ++max_level_;
        }
    }
    
    QuadNode* descend_node = lnode_->below_;
    QuadNode* inserted_node;
    QuadNode* old_inserted_node = nullptr;
    QuadNode* dupe_node = nullptr;
    while (descend_node != nullptr)
    {
        inserted_node = listInsert(descend_node, k, v);

        if (*inserted_node == *inserted_node->next_)
        {
            dupe_node = inserted_node->next_;
            inserted_node->next_ = inserted_node->next_->next_;
            delete dupe_node;
        }

        if (old_inserted_node != nullptr)
            old_inserted_node->below_ = inserted_node;
        
        inserted_node->above_ = old_inserted_node;
        old_inserted_node = inserted_node;
        descend_node = descend_node->below_;
    }

    if (dupe_node != nullptr)
        ++size_;
}

void SkipList::erase(const int k)
{
    QuadNode *current = lnode_;
    QuadNode *next;
    while (current->entry_->getKey() != k && current != nullptr)
    {
        next = current->next_;
        current = (*next == QuadNode::P_INF) ? current->below_ : current->next_;
    }

    if (current == nullptr)
        throw NotFoundException();
    
    QuadNode *descend_node;
    while (descend_node != nullptr)
    {
        descend_node->prev_->next_ = descend_node->next_;
        descend_node->next_->prev_ = descend_node->prev_;
        delete descend_node;
        descend_node = descend_node->below_;
    }
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
    while (descend_node != nullptr)
    {
        iter_node = descend_node;
        searcher_node = base_node_;
        while (iter_node != nullptr)
        {
            hpos = 0;
            while (*searcher_node != *iter_node)
            {
                hpos += 2;
                if (*searcher_node->next_ != *iter_node)
                    hpos += std::to_string(searcher_node->entry_->getKey()).length();
                searcher_node = searcher_node->next_;
            }
            
            for (int i = 0; i < hpos; ++i)
                std::cout << "-";

            if (*iter_node == QuadNode::M_INF)
                std::cout << "-INF";
            else if (*iter_node == QuadNode::P_INF)
                std::cout << "INF+";
            else
                std::cout << iter_node->entry_->getKey();

            iter_node = iter_node->next_;
        }
        std::cout << std::endl;
        descend_node = descend_node->below_;
    }

}
