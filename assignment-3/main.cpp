#include <iostream>
#include <string>

#include "ArrayList.h"
#include "Iterator.h"

using namespace std;

void testArrayListUnderflow()
{
    try
    {
        ArrayList<int> test = ArrayList<int>();
        test.insertBack(1);
        test.removeFront();
        test.removeFront();
    }
    catch(const EmptyListException& e)
    {
        std::cerr << "Caught EmptyListException" << endl;
    }
    
}

void testIntegerIterator()
{

}

void testStringIterator()
{

}

int main(int argc, char const *argv[])
{
    testArrayListUnderflow();
    testIntegerIterator();
    testStringIterator();
    
    return 0;
}
