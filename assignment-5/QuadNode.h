#ifndef QUAD_NODE_H
#define QUAD_NODE_H

#include "Entry.h"
#include "SkipList.h"

class SkipList::QuadNode
{
    friend SkipList;
private:
    const static QuadNode P_INF;
    const static QuadNode M_INF;

    enum InfKey
    {
        NONE = 0,
        PLUS = 1,
        MINUS = -1
    };

    const InfKey inf_key_;
    Entry const* entry_;
    QuadNode *prev_, *next_, *above_, *below_;

    explicit QuadNode(Entry const* entry);
    explicit QuadNode(const InfKey inf_key);

    bool operator==(QuadNode const& node);
    bool operator!=(QuadNode const& node);
};

#endif