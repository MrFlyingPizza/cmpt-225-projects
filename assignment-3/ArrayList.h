/* 
* ArrayList.h
* By Han Gao
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
    
    T& operator[](int i) const;
    
    T& front() const;
    T& back() const;

    void insertFront(T const& e);
    void insertBack(T const& e);
    void insert(Iterator& p, T const& e);

    void removeFront();
    void removeBack();
    void remove(Iterator& p);

    int size() const;
    bool empty() const;
    bool validate(Iterator& p) const;

    Iterator begin() const;
    Iterator end() const;

private:

    T* data_;

    int size_, capacity_;

    Iterator begin_, back_, end_;

    void handleOverflow();
};

class InvalidIndexException {};
class InvalidIteratorException {};
class EmptyListException {};
class InvalidListCapacityException {};

/* Constructs a ArrayList of given capacity (default: 4). */
template<typename T>
ArrayList<T>::ArrayList(const int capacity)
: size_(0), capacity_(capacity), begin_(this, 0), back_(this, 0), end_(this, 1)
{
    data_ = new T[capacity + 1];
}

/* Frees memory allocated to ArrayList and destructs the object */
template<typename T>
ArrayList<T>::~ArrayList()
{
    if (data_ != nullptr) delete[] data_;
}

/* Handles doubling the capacity of ArrayList */
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
    
    delete[] data_;
    data_ = new_array;

    begin_ = Iterator(this, 0);
    back_ = Iterator(this, size_- 1);
    end_ = Iterator(this, size_);
}

/* Returns a reference to the value at index 'i' in the ArrayList. */
template<typename T>
T& ArrayList<T>::operator[](const int i) const
{
    if (empty()) throw EmptyListException();
    if (i < 0 || i >= size_) throw InvalidIndexException();

    ArrayList<T>::Iterator iter = begin_;
    for (int j = 0; j < i; j++) ++iter;

    return *iter;
}

/* Returns a reference to the first value of ArrayList. */
template<typename T>
T& ArrayList<T>::front() const
{
    if (empty()) throw EmptyListException();
    return *begin_;
}

/* Returns a reference to the last value of ArrayList. */
template<typename T>
T& ArrayList<T>::back() const
{
    if (empty()) throw EmptyListException();
    return *back_;
}

/* Inserts a value to the front of ArrayList. */
template<typename T>
void ArrayList<T>::insertFront(T const& e)
{
    if (size_ == capacity_) handleOverflow();

    if (!empty()) --begin_;
    *begin_ = e;
    size_++;
}

/* Inserts a value to the back of ArrayList. */
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

/* Inserts a value at 'p'. */
template<typename T>
void ArrayList<T>::insert(Iterator& p, T const& e)
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
        if (!validate(p)) throw InvalidIteratorException();
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
        ++size_;
    }
    
}

/* Remove the first element of ArrayList. */
template<typename T>
void ArrayList<T>::removeFront()
{
    if (empty()) throw EmptyListException();

    ++begin_;
    size_--;
}

/* Removes the last element of ArrayList */
template<typename T>
void ArrayList<T>::removeBack()
{
    if (empty()) throw EmptyListException();

    --back_;
    --end_;
    size_--;
}

/* Removes the element at 'p'. */
template<typename T>
void ArrayList<T>::remove(Iterator& p)
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
        if (!validate(p)) throw InvalidIteratorException();
        Iterator set_iter = p, get_iter = p;
        ++get_iter;
        while (get_iter != end_)
        {
            *set_iter = *get_iter;
            ++get_iter;
            ++set_iter;
        }
        --size_;
    }
    
}

/* Returns the number of elements in the ArrayList. */
template<typename T>
int ArrayList<T>::size() const
{
    return size_;
}

/* Checks if the ArrayList is empty. */
template<typename T>
bool ArrayList<T>::empty() const
{
    return size_ < 1;
}

/* Check if Iterator 'i' belongs to ArrayList and within range. */
template<typename T>
bool ArrayList<T>::validate(Iterator& p) const
{
    bool valid = false;
    if (p == end_)
    {
        valid = true;
    }
    else
    {
        Iterator iter = begin_;
        while (valid == false && iter != end_)
        {
            if (iter == p)
            {
                valid = true;
            }
            else
            {
                ++iter;
            }

        }

    }
    return valid;
}

/* Returns an Iterator to the start of ArrayList. */
template<typename T>
typename ArrayList<T>::Iterator ArrayList<T>::begin() const
{
    return begin_;
}

/* Returns an Iterator to 1 past the last position. */
template<typename T>
typename ArrayList<T>::Iterator ArrayList<T>::end() const
{
    return end_;
}

#endif