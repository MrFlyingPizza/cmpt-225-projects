#ifndef SKIP_LIST_H
#define SKIP_LIST_H

class SkipList {
private:

    class QuadNode;

    int size_, max_level_;

    QuadNode *lnode_, *rnode_, *base_node_;

    QuadNode* listInsert(QuadNode* node, int k, std::string) const;

public:
    SkipList();
    ~SkipList();

    Entry const& find(int k) const;
    Entry const& greaterEntry(int k) const;
    Entry const& lesserEntry(int k) const;

    void put(int k, std::string v);
    void erase(int k);

    int size() const;
    bool empty() const;

    void print() const;
};

#endif