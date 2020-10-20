/* 
* By Richard Gao
*/

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

template<typename T>
class ArrayList {
public:

    static const int DEFAULT_CAPACITY_= 4;

    class Iterator;

    explicit ArrayList(int capacity = DEFAULT_CAPACITY_);
    ~ArrayList();
    
    T& operator[](int i);
    
    T& front();
    T& back();

    void insertFront(T const& e);
    void insertBack(T const& e);
    void insert(Iterator p, T const& e);

    void removeFront();
    void removeBack();
    void remove(Iterator p);

    int size();
    bool empty();

    Iterator begin();
    Iterator end();

private:

    T* data_;

    int size_, capacity_;

    Iterator begin_, back_, end_;

    void handleOverflow();
};

class IndexOutOfBoundException {};
class EmptyListException {};
class InvalidListCapacityException {};

template<typename T>
ArrayList<T>::ArrayList(const int capacity)
: size_(0), capacity_(capacity), begin_(this, 0), back_(this, 0), end_(this, 1)
{
    data_ = new T[capacity + 1];
}

template<typename T>
ArrayList<T>::~ArrayList()
{
    if (data_ != nullptr) delete[] data_;
}

template<typename T>
void ArrayList<T>::handleOverflow()
{
    T* new_array = new T[(capacity_*=2)+1];
    int i = 0;
    for (Iterator iter = begin_; iter != end_; ++iter)
    {
        new_array[i] = *iter;
        i++;
    }
    begin_ = Iterator(this, 0);
    back_ = Iterator(this, size_- 1);
    end_ = Iterator(this, size_);
}

template<typename T>
T& ArrayList<T>::operator[](const int i)
{
    if (empty()) throw EmptyListException();
    if (i < 0 || i >= size_) throw IndexOutOfBoundException();

    ArrayList<T>::Iterator iter = this->begin_;
    for (int j = 0; j < i; j++) ++iter;

    return *iter;
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
    if (size_ == capacity_) handleOverflow();

    if (!empty()) --begin_;
    *begin_ = e;
    size_++;
}

template<typename T>
void ArrayList<T>::insertBack(T const& e)
{
    if (size_ == capacity_) handleOverflow();

    if (!empty())
    {
        ++end_;
        ++back_;
    }
    *back_ = e;
    size_++;
}

template<typename T>
void ArrayList<T>::insert(Iterator p, T const& e)
{
    if (size_ == capacity_) handleOverflow();

    if (p == begin_)
    {
        insertFront(e);
    }
    else if (p == end_)
    {
        insertBack(e);
    }
    else
    {
        Iterator get_iter = back_, set_iter = end_;
        while (set_iter != p)
        {
            *set_iter = *get_iter;
            --get_iter;
            --set_iter;
        }
        ++end_;
        ++back_;
        *p = e;
    }
    
}

template<typename T>
void ArrayList<T>::removeFront()
{
    if (empty()) throw EmptyListException();

    ++begin_;
    size_--;
}

template<typename T>
void ArrayList<T>::removeBack()
{
    if (empty()) throw EmptyListException();

    --back_;
    --end_;
    size_--;
}

template<typename T>
void ArrayList<T>::remove(Iterator p)
{
    if (empty()) throw EmptyListException();
    
    if (p == begin_)
    {
        removeFront();
    }
    else if (p == back_)
    {
        removeBack();
    }
    else
    {
        Iterator set_iter = p, get_iter = p;
        ++get_iter;
        while (get_iter != end_)
        {
            *set_iter = *get_iter;
            ++get_iter;
            ++set_iter;
        }
        
    }

}

template<typename T>
int ArrayList<T>::size()
{
    return size_;
}

template<typename T>
bool ArrayList<T>::empty()
{
    return size_ < 1;
}

template<typename T>
typename ArrayList<T>::Iterator ArrayList<T>::begin()
{
    return begin_;
}

template<typename T>
typename ArrayList<T>::Iterator ArrayList<T>::end()
{
    return end_;
}

#endif