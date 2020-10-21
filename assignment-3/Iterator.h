#ifndef ITERATOR_H
#define ITERATOR_H

template<typename T>
class ArrayList<T>::Iterator {
public:

    static const int DEFAULT_INITIAL_INDEX_ = 0;

    Iterator(ArrayList<T>* ref, int initial_index = DEFAULT_INITIAL_INDEX_);

    T& operator*();

    Iterator operator++();
    Iterator operator--();

    bool operator==(Iterator const& i);
    bool operator!=(Iterator const& i);

private:

    ArrayList<T>* array_list_ptr_;
    int index_;

};

template<typename T>
ArrayList<T>::Iterator::Iterator(ArrayList<T>* array_list_ptr, const int initial_index)
: array_list_ptr_(array_list_ptr), index_(initial_index)
{}

template<typename T>
T& ArrayList<T>::Iterator::operator*()
{
    return array_list_ptr_->data_[index_];
}

template<typename T>
typename ArrayList<T>::Iterator ArrayList<T>::Iterator::operator++()
{
    index_ == array_list_ptr_->capacity_ ? index_ = 0 : index_++;
    return *this;
}

template<typename T>
typename ArrayList<T>::Iterator ArrayList<T>::Iterator::operator--()
{
    index_ == 0 ? index_ = array_list_ptr_->capacity_ : index_--;
    return *this;
}

template<typename T>
bool ArrayList<T>::Iterator::operator==(Iterator const& i)
{
    return (array_list_ptr_ == i.array_list_ptr_ && index_ == i.index_);
}

template<typename T>
bool ArrayList<T>::Iterator::operator!=(Iterator const& i)
{
    return !(*this == i);
}

#endif