#ifndef HEAP_H
#define HEAP_H

class Heap {
private:
    Entry* entries_;
    int size_, capacity_;
    int insertion_index_;

    void handleOverflow();

    void swap(int j, int k);
    void upHeap(int c_i);
    void downHeap(int c_i);
public:
    explicit Heap(int capacity = 3);
    ~Heap();

    Entry& removeMax();
    void insert(Entry const& e);

    int size() const;
    bool empty() const;

    void make(Entry const* entries, int n);
};

class EmptyHeapException {};

#endif