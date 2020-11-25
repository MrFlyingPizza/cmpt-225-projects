#include "Entry.h"
#include "QuadNode.h"

SkipList::QuadNode::QuadNode(Entry* const entry)
: entry_(entry), prev_(nullptr), next_(nullptr), above_(nullptr), below_(nullptr)
{}