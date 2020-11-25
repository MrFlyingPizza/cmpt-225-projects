#ifndef QUAD_NODE_H
#define QUAD_NODE_H

#include "Entry.h"
#include "SkipList.h"

class SkipList::QuadNode
{
    friend SkipList;
private:

    Entry *entry_;
    QuadNode *prev_, *next_, *above_, *below_;

    explicit QuadNode(Entry* entry);
};

#endif