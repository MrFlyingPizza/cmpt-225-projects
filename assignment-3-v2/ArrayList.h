//
// Created by hga38 on 2020-10-22.
//

#ifndef ASSIGNMENT_3_V2_ARRAYLIST_H
#define ASSIGNMENT_3_V2_ARRAYLIST_H

template<typename T>
class ArrayList {
public:

    class Iterator;

    explicit ArrayList(int capacity = 4);

    T& operator[](int i);
    T& front();
    T& back();

    void insertFront(T const& e);
    void insertBack(T const& e);
    void insert(Iterator& p, T const& e);

    void removeFront();
    void removeBack();
    void remove(Iterator p);

    int size();
    bool empty();

    Iterator begin();
    Iterator end();

private:

    T* data_;

    int capacity_, size_, array_end_index_;

    Iterator begin_, back_, end_;

    void handleOverflow();

    bool isValid(Iterator const& p);

};

class InvalidIndexException {};
class EmptyListException {};
class IteratorPastBoundException {};

template<typename T>
ArrayList<T>::ArrayList(const int capacity)
: capacity_(capacity), size_(0), array_end_index_(capacity-1)
{
    begin_ = Iterator(this, 0);
    back_ = Iterator(this, 0);
    end_ = Iterator(this, 1);
}

/* stub */
template<typename T>
void ArrayList<T>::handleOverflow()
{

}

template<typename T>
bool ArrayList<T>::isValid(Iterator const& p)
{
    bool valid = false;
    if (p.arraylist_ptr_ == this)
    {
        valid = (begin_.iter_index_ < end_.iter_index_
                && begin_.iter_index_ < p.iter_index
                && p.iter_index_ < end_.iter_index_)
                || (begin_.iter_index_ > end_.iter_index_
                && p.iter_index_ >= 0
                && p.iter_index_ < end_.iter_index_
                && p.iter_index_ >= begin_.iter_index_
                && p.iter_index_ <= capacity_);
    }
    return valid;
}

template<typename T>
T& ArrayList<T>::operator[](const int i)
{
    if (i < 0 || i >= size_) throw InvalidIndexException();

    const int offset_index = begin_.iter_index_;
    return data_[(offset_index > capacity_) ? offset_index - capacity_ : offset_index];
}

template<typename T>
T& ArrayList<T>::front()
{
    if (empty()) throw EmptyListException();
    return *begin_;
}

template<typename T>
T& ArrayList<T>::back()
{
    if (empty()) throw EmptyListException();
    return *back_;
}

template<typename T>
void ArrayList<T>::insertFront(T const& e)
{
    if (capacity_ == size_) handleOverflow();
    if (!empty()) --begin_;
    *begin_ = e;
    ++size_;
}

template<typename T>
void ArrayList<T>::insertBack(T const& e)
{
    if (capacity_ == size_) handleOverflow();
    if (!empty())
    {
        ++back_;
        ++end_;
    }
    *back_ = e;
    ++size_;
}

template<typename T>
void ArrayList<T>::insert(Iterator& p, const T &e)
{
    if (!isValid(p)) throw IteratorPastBoundException();
    if (capacity_ == size_) handleOverflow();

    Iterator get_iter = back_, set_iter = end_;
    while (set_iter != p)
    {
        *set_iter = *get_iter;
        --get_iter;
        --set_iter;
    }
    *p = e;
    ++back_;
    ++end_;
    ++size_;
}

template<typename T>
void ArrayList<T>::removeFront()
{
    if (empty()) throw EmptyListException();
    --begin_;
    --size_;
}

#endif //ASSIGNMENT_3_V2_ARRAYLIST_H
