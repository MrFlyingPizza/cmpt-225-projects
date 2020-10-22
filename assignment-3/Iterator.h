/*
* Iterator.h
* By Han Gao
*/


#ifndef ITERATOR_H
#define ITERATOR_H

template<typename T>
class ArrayList<T>::Iterator {
public:

    static const int DEFAULT_INITIAL_INDEX_ = 0;

    Iterator(ArrayList<T>* ref, int initial_index = DEFAULT_INITIAL_INDEX_);

    T& operator*() const;

    Iterator& operator++();
    Iterator& operator--();

    bool operator==(Iterator const& i);
    bool operator!=(Iterator const& i);

private:

    ArrayList<T> const* array_list_ptr_;
    int index_;

};

/* Constructs a Iterator using a pointer to a ArrayList and an int index. */
template<typename T>
ArrayList<T>::Iterator::Iterator(ArrayList<T>* const array_list_ptr, const int initial_index)
: array_list_ptr_(array_list_ptr), index_(initial_index)
{}

/* Returns the a reference to the value at Iterator's position,
positions outside of written positions results in undefined behaviour. */
template<typename T>
T& ArrayList<T>::Iterator::operator*() const
{
    return array_list_ptr_->data_[index_];
}

/* Moves Iterator forwards once. */
template<typename T>
typename ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator++()
{
    index_ == array_list_ptr_->capacity_ ? index_ = 0 : index_++;
    return *this;
}

/* Moves Iterator backwards once. */
template<typename T>
typename ArrayList<T>::Iterator& ArrayList<T>::Iterator::operator--()
{
    index_ == 0 ? index_ = array_list_ptr_->capacity_ : index_--;
    return *this;
}

/* True if this Iterator's ArrayList and index matches Iterator 'i'. */
template<typename T>
bool ArrayList<T>::Iterator::operator==(Iterator const& i)
{
    return (array_list_ptr_ == i.array_list_ptr_ && index_ == i.index_);
}

/* False if this Iterator's ArrayList and index matches Iterator 'i'. */
template<typename T>
bool ArrayList<T>::Iterator::operator!=(Iterator const& i)
{
    return !(*this == i);
}

#endif