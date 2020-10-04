// ArrayUltils.h

template<typename T>
class ArrayUtils {

public:

    /* Reverse an array */
    static T* reverse(T* given_array, const int given_array_size);
};

template<typename T>
T* ArrayUtils<T>::reverse(T* given_array, const int given_array_size)
{
    Stack<T> temp_stack = Stack<T>(given_array_size);
    for (int i = 0; i < given_array_size; i++)
    {
        temp_stack.push(given_array[i]);
    }

    for (int i = 0; i < given_array_size; i++)
    {
        given_array[i] = temp_stack.pop();
    }
    
    return given_array;
}