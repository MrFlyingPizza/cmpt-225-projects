#include "Stack.h"
#include "ArrayUtils.h"
#include "Employee.h"

#include <iostream>
#include <string>

using namespace std;

void testStackUnderflow()
{
    try
    {
        Stack<int> test_stack = Stack<int>();
        test_stack.push(69);

        test_stack.pop();
        test_stack.pop();

        cout << "did not catch exception" << endl;
    }
    catch(const EmptyStackException& e)
    {
        cout << "caught EmptyStackException" << endl;
    }

}

void testStackGrowth()
{
    Stack<int> test_stack = Stack<int>();

    /* push 5 items */
    for (int i = 0; i < 9; i++)
    {
        test_stack.push(i);
        cout << "Pushed onto stack: " << i << endl;

        /* print capacity at 4th and 8th push */
        if (i == 4 || i == 8)
        {
            cout << "Current stack capacity: " << test_stack.capacity() << endl;
        }
        
    }

    for (int i = 0; i < 9; i++)
    {
        cout << "Popped from stack: " << test_stack.pop() << endl;
    }
    
}

/* utility printing function */
template<typename T>
void print_array(const T* array, const int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "Element at i=" << i << ": " << array[i] << endl;
    }
    
}

void testReverseIntegers()
{
    int test_array[12];
    for (int i = 0; i < 12; i++)
    {
        test_array[i] = i*2;
    }
    
    print_array(test_array, 12);

    ArrayUtils<int>::reverse(test_array, 12);
    
    print_array(test_array, 12);
}

void testReverseStrings()
{
    string test_array[12];
    for (int i = 0; i < 12; i++)
    {
        test_array[i] = (char) (65+i);
        test_array[i].append("test");
    }
    
    print_array(test_array, 12);

    ArrayUtils<string>::reverse(test_array, 12);
    
    print_array(test_array, 12);
}

void testReverseEmployees()
{
    Employee test_array[12];
    test_array[0] = Employee("John", 928576);
    test_array[1] = Employee("Olivia", 164853);
    test_array[2] = Employee("Oliver", 386736);
    test_array[3] = Employee("Karen", 948266);
    test_array[4] = Employee("Jose", 386746);
    test_array[5] = Employee("Ben", 207995);
    test_array[6] = Employee("Cameron", 768390);
    test_array[7] = Employee("Abigail", 223968);
    test_array[8] = Employee("Lenny", 293858);
    test_array[9] = Employee("Leah", 556938);
    test_array[10] = Employee("Simon", 770394);
    test_array[11] = Employee("Sarah", 739948);

    for (int i = 0; i < 12; i++)
    {
        cout << test_array[i].toString() << endl;
    }

    ArrayUtils<Employee>::reverse(test_array, 12);

    for (int i = 0; i < 12; i++)
    {
        cout << test_array[i].toString() << endl;
    }
    
}

int main()
{
    testStackUnderflow();
    testStackGrowth();

    cout << endl;

    testReverseIntegers();
    testReverseStrings();

    cout << endl;

    testReverseEmployees();
    return 0;
}
