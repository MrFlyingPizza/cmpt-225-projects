#include <string>
#include <iostream>

#include "Entry.h"
#include "QuadNode.h"
#include "SkipList.h"


SkipList::SkipList()
: size_(0), max_level_(0)
{
    lnode_ = new QuadNode(new Entry(Entry::MINUS));
    lnode_->next_= new QuadNode(new Entry(Entry::PLUS));
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
        }
        vnode = vnode->below_;
    }
    
}

Entry const& SkipList::find(const int k) const
{
    if (empty()) return Entry::END_ENTRY;

    QuadNode *current = lnode_->below_;
    while (current != nullptr)
    {
        if (current->entry_->isKeyEqual(k)) return *current->entry_;
        current = (!current->next_->entry_->isKeyGreaterThan(k))
            ? current->next_ : current->below_;
    }
    return Entry::END_ENTRY;
}

Entry const& SkipList::lesserEntry(const int k) const
{
    if (empty()) return Entry::M_INF;

    QuadNode* current = lnode_;
    QuadNode* ahead = current->next_;
    while (ahead->entry_->isKeyLessThan(k) || current->below_ != nullptr)
    {
        current = (!ahead->entry_->isKeyLessThan(k) || *ahead->entry_ == *rnode_->entry_)
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
    while (ahead->entry_->isKeyGreaterThan(k) || current->below_ != nullptr)
    {
        current = (!ahead->entry_->isKeyGreaterThan(k) || *ahead->entry_ == *lnode_->entry_)
            ? current->below_ : current->prev_;

        ahead = current->prev_;
    }
    return *current->entry_;
}

void SkipList::put(const int k, const std::string v)
{
    Entry *new_entry = new Entry(k,v);
    int count = 0;
    while (rand()%2 == 0) ++count;
    for (int i = max_level_; i <= count; i++)
    {
        lnode_->above_ = new QuadNode(lnode_->entry_);
        rnode_->above_ = new QuadNode(rnode_->entry_);

        lnode_->above_->below_ = lnode_;
        rnode_->above_->below_ = rnode_;

        lnode_ = lnode_->above_;
        rnode_ = rnode_->above_;

        lnode_->next_ = rnode_;
        rnode_->prev_ = lnode_;
        ++max_level_;
    }
    QuadNode *search_node = lnode_;
    QuadNode *insert_node, *old_node = nullptr;
    Entry *old_entry = nullptr;
    int to_drop = max_level_ - count;
    while (search_node != nullptr)
    {
        if (*search_node->next_->entry_ <= *new_entry)
        {
            search_node = search_node->next_;
        }
        else
        {
            insert_node = nullptr;
            if (*search_node->entry_ == *new_entry)
            {
                if (search_node->below_ == nullptr)
                    old_entry = search_node->entry_;
                
                insert_node = search_node;
                insert_node->entry_ = new_entry;
            }
            else if (to_drop == 0)
            {
                insert_node = new QuadNode(new_entry);
                insert_node->prev_ = search_node;
                insert_node->next_ = search_node->next_;
                insert_node->next_->prev_ = insert_node;
                search_node->next_ = insert_node;
            }

            if (insert_node != nullptr)
            {
                insert_node->above_ = old_node;
                if (old_node != nullptr)
                    old_node->below_ = insert_node;
                
                old_node = insert_node;
            }

            search_node = search_node->below_;
            if (to_drop != 0)
                --to_drop;
        }
    }

    if (old_entry == nullptr)
        ++size_;
    else
        delete old_entry;
}

void SkipList::erase(const int k)
{
    if (empty()) throw NotFoundException();

    QuadNode *current = lnode_->below_;
    QuadNode *next = current;
    while (!current->entry_->isKeyEqual(k) && current != nullptr)
    {
        next = current->next_;
        current = (!next->entry_->isKeyGreaterThan(k) && *current->next_->entry_ != *rnode_->entry_)
                ? current->next_ : current->below_;
    }

    if (current == nullptr)
        throw NotFoundException();

    QuadNode *descend_lnode = lnode_->below_, *descend_rnode = rnode_->below_;
    QuadNode *delete_node;
    bool is_relink_top;
    while (current != nullptr)
    {
        if (*current->prev_->entry_ == *lnode_->entry_ && *current->next_->entry_ == *rnode_->entry_)
        {
            descend_lnode = descend_lnode->below_;
            descend_rnode = descend_rnode->below_;

            delete current->prev_;
            delete current->next_;

            is_relink_top = true;
            --max_level_;
        }

        current->prev_->next_ = current->next_;
        current->next_->prev_ = current->prev_;
        
        delete_node = current;
        current = current->below_;
        delete delete_node;
    }

    if (is_relink_top)
    {
        descend_lnode->above_ = lnode_;
        descend_rnode->above_ = rnode_;
        lnode_->below_ = descend_lnode;
        rnode_->below_ = descend_rnode;
        is_relink_top = false;
    }

    --size_;
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
    QuadNode *vnode = lnode_;
    while (vnode != nullptr)
    {
        QuadNode *hnode = vnode;
        QuadNode *search_node = base_node_;
        while (hnode != nullptr)
        {
            int dash_count = 0;
            while (*search_node->entry_ != *hnode->entry_)
            {
                dash_count += 2;
                if (*search_node->next_->entry_ != *hnode->entry_)
                    dash_count += std::to_string(search_node->next_->entry_->getKey()).length();

                search_node = search_node->next_;
            }

            for (int i = 0; i < dash_count; ++i)
                std::cout << '-';

            
            if (*hnode->entry_ == *lnode_->entry_)
            {
                std::cout << "-INF";
            }
            else if (*hnode->entry_ == *rnode_->entry_)
            {
                std::cout << "INF+";
            }
            else
            {
                std::cout << hnode->entry_->getKey();
            }
            
            hnode = hnode->next_;
        }
        std::cout << std::endl;
        vnode = vnode->below_;
    }
    
}
