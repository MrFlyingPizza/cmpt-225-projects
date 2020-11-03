#include <string>
#include <iostream>

#include "Entry.h"
#include "Heap.h"

Heap::Heap(const int capacity)
: size_(0), capacity_(capacity)
{
    entries_ = new Entry[capacity+1];
}

Heap::~Heap()
{
    if (entries_ != nullptr) delete[] entries_;
}

void Heap::handleOverflow()
{
    const int new_capacity = capacity_ * 2;
    Entry* new_entries = new Entry[new_capacity+1];
    for (int i = 0; i <= capacity_; ++i)
    {
        new_entries[i] = entries_[i];
    }
    entries_ = new_entries;
    capacity_ = new_capacity;
}

void Heap::swap(const int l_i, const int r_i)
{
    if (l_i == r_i) return;
    Entry temp = entries_[l_i];
    entries_[l_i] = entries_[r_i];
    entries_[r_i] = temp;
}

void Heap::upHeap(const int c_i)
{
    const int p_i = c_i/2;
    if (p_i == 0) return;
    if (entries_[c_i].getKey() > entries_[p_i].getKey())
    {
        swap(c_i, p_i);
        upHeap(p_i);
    }
}

void Heap::downHeap(const int c_i)
{
    int l_i = c_i*2;
    int r_i = l_i+1;
    if (l_i > size_) return;
    if (r_i > size_ && entries_[c_i].getKey() < entries_[l_i].getKey())
    {
        swap(c_i, l_i);
        return;
    }

    bool is_l_greater = entries_[c_i].getKey() < entries_[l_i].getKey();
    bool is_r_greater = entries_[c_i].getKey() < entries_[r_i].getKey();
    bool is_swap_left;
    if (!(is_l_greater || is_r_greater)) return;

    if (is_l_greater && is_r_greater)
    {
        is_swap_left = entries_[l_i].getKey() >= entries_[r_i].getKey();
    }
    else
    {
        is_swap_left = is_l_greater;
    }
    
    if (is_swap_left)
    {
        swap(c_i, l_i);
        downHeap(l_i);
    }
    else
    {
        swap(c_i, r_i);
        downHeap(r_i);
    }
    
}

Entry& Heap::removeMax()
{
    if (empty()) throw EmptyHeapException();
    entries_[0] = entries_[1];
    entries_[1] = entries_[size_];
    --size_;
    downHeap(1);
    return entries_[0];
}

void Heap::insert(Entry const& e)
{
    if (size_ == capacity_) handleOverflow();

    entries_[++size_] = e;
    upHeap(size_);
}

int Heap::size() const
{
    return size_;
}

bool Heap::empty() const
{
    return size_ <= 0;
}

void Heap::makeHeap(const int cap, Entry const* entries, const int n) //test
{
    if (cap == 0) return;

    const int l_cap = cap/2;
    const int max = (cap >= n) ? n : cap;
    for (int i = l_cap; i <= max; ++i)
    {
        entries_[i] = entries[i-1];
        downHeap(i);
    }

    makeHeap(l_cap, entries, n);
}

void Heap::make(Entry const* entries, const int n)
{
    int count = 1;
    while (count < n) count *= 2;

    if (entries_ != nullptr) delete[] entries_;
    entries_ = new Entry[count];

    capacity_ = count + 1;
    size_ = n;

    makeHeap(count, entries, n);
}
