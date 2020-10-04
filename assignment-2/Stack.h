// Stack.h

template<typename T>
class Stack {
private:

    T* stack_array;

    int stack_capacity;
    int stack_size;

public:

    /* Constructor with capactiy */
    Stack(int capacity = 4);

    /* Destructor */
    ~Stack();

    T& pop();
    void push(const T& new_element);
    bool empty() const;
    int size() const;
    int capacity() const;

};

// Exception class
class EmptyStackException{

};

/* Creates a stack of given capacity, defaults to '4' */
template<typename T>
Stack<T>::Stack(const int capacity) : stack_capacity(capacity), stack_size(0)
{
    stack_array = new T[capacity];
}

/* Frees memory allocated for the stack array and destroys stack */
template<typename T>
Stack<T>::~Stack()
{
    if (stack_array != nullptr)
    {
        delete[] stack_array;
    }
    
}

/* Pops an element from top of stack */
template<typename T>
T& Stack<T>::pop()
{
    if (stack_array == nullptr || stack_size < 1)
    {
        throw EmptyStackException();
    }

    T& temp_el = stack_array[stack_size-1];
    stack_size -= 1;

    return temp_el;
}

/* Push an element to the top of stack, allocating memory as needed */
template<typename T>
void Stack<T>::push(const T& new_element)
{
    if (stack_size == stack_capacity)
    {
        T* new_stack_array = new T[stack_capacity*2];
        for (int i = 0; i < stack_size; i++)
        {
            new_stack_array[i] = stack_array[i];
        }
        
        delete[] stack_array;
        stack_array = new_stack_array;
        stack_capacity *= 2;
    }
    
    stack_array[stack_size] = new_element;
    stack_size += 1;
}

/* Return if the stack is empty */
template<typename T>
bool Stack<T>::empty() const
{
    return stack_size == 0;
}

/* Get number of elements in the stack */
template<typename T>
int Stack<T>::size() const
{
    return stack_size;
}

/* Get capacity of stack */
template<typename T>
int Stack<T>::capacity() const
{
    return stack_capacity;
}