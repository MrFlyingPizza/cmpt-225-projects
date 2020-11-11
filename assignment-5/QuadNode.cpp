#include "Entry.h"
#include "QuadNode.h"

const SkipList::QuadNode SkipList::QuadNode::P_INF = SkipList::QuadNode(QuadNode::InfKey::PLUS);
const SkipList::QuadNode SkipList::QuadNode::M_INF = SkipList::QuadNode(QuadNode::InfKey::MINUS); 

SkipList::QuadNode::QuadNode(Entry const* entry)
: inf_key_(InfKey::NONE), entry_(entry), prev_(nullptr), next_(nullptr), above_(nullptr), below_(nullptr)
{}

SkipList::QuadNode::QuadNode(const InfKey inf_key)
: inf_key_(inf_key), prev_(nullptr), next_(nullptr), above_(nullptr), below_(nullptr)
{
    switch (inf_key)
    {
    case QuadNode::InfKey::PLUS:
        entry_ = &Entry::P_INF;
        break;
    case QuadNode::InfKey::MINUS:
        entry_ = &Entry::M_INF;
        break;
    default:
        entry_ = &Entry::END_ENTRY;
        break;
    }
}

bool SkipList::QuadNode::operator==(QuadNode const& node)
{
    return (node.inf_key_ != InfKey::NONE || inf_key_ != InfKey::NONE) ? node.inf_key_ == inf_key_ : node.entry_->getKey() == entry_->getKey();
}
bool SkipList::QuadNode::operator!=(QuadNode const& node)
{
    return !((node.inf_key_ != InfKey::NONE || inf_key_ != InfKey::NONE) ? node.inf_key_ == inf_key_ : node.entry_->getKey() == entry_->getKey());
}