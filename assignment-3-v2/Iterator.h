//
// Created by hga38 on 2020-10-22.
//

#ifndef ASSIGNMENT_3_V2_ITERATOR_H
#define ASSIGNMENT_3_V2_ITERATOR_H

template<typename T>
class ArrayList<T>::Iterator {
    friend class ArrayList;
public:

    T& operator*();
    Iterator& operator++();
    Iterator& operator--();
    bool operator==(Iterator const& i);
    bool operator!=(Iterator const& i);

private:

    explicit Iterator(ArrayList<T> const* arraylist_ptr_ = nullptr, int stored_iter_index = 0);

    ArrayList<T> const* arraylist_ptr_;
    int iter_index_;

};

template<typename T>
ArrayList<T>::Iterator::Iterator(ArrayList<T> const* arraylist_ptr, const int iter_index)
: arraylist_ptr_(arraylist_ptr), iter_index_(iter_index) {}

template<typename T>
T& ArrayList<T>::Iterator::operator*()
{
    return arraylist_ptr_->data_[iter_index_];
}

template<typename T>
typename ArrayList<T>::Iterator &ArrayList<T>::Iterator::operator++()
{
    if (*this == arraylist_ptr_->end_) throw IteratorPastBoundException();

    if (iter_index_ == arraylist_ptr_->array_end_index_)
    {
        iter_index_ = 0;
    }
    else
    {
        ++iter_index_;
    }
    return *this;
}

template<typename T>
typename ArrayList<T>::Iterator &ArrayList<T>::Iterator::operator--()
{
    if (*this == arraylist_ptr_->begin_) throw IteratorPastBoundException();

    if (iter_index_ == 0)
    {
        iter_index_ = arraylist_ptr_->array_end_index_;
    }
    else
    {
        --iter_index_;
    }
    return *this;
}

template<typename T>
bool ArrayList<T>::Iterator::operator==(const ArrayList<T>::Iterator &i)
{
    return i.arraylist_ptr_ == arraylist_ptr_ && i.iter_index_ == iter_index_;
}

template<typename T>
bool ArrayList<T>::Iterator::operator!=(const ArrayList<T>::Iterator &i)
{
    return !(*this == i);
}

#endif //ASSIGNMENT_3_V2_ITERATOR_H
