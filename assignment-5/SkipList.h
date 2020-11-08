#ifndef SKIP_LIST_H
#define SKIP_LIST_H

class SkipList {
private:
    class QuadNode {
        friend class SkipList;

    private:
        explicit QuadNode(Entry const& entry);
        explicit QuadNode(int inf_key);
        Entry const& entry_;
        QuadNode *prev_, *next_, *below_, *above_;
    };

    int size_, max_level_;

    QuadNode *lnode_, *rnode_;

    QuadNode* listInsert(QuadNode* node, Entry k) const;

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
};

#endif