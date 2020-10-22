/*
* main.cpp
* By Han Gao
*/


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

        cout << "did not catch exception" << endl;
    }
    catch(const EmptyListException& e)
    {
        cout << "Caught EmptyListException" << endl;
    }
    
    try
    {
        ArrayList<int> test = ArrayList<int>();
        test.insertBack(1);
        test.removeBack();
        test.removeBack();

        cout << "did not catch exception" << endl;
    }
    catch(const EmptyListException& e)
    {
        cout << "Caught EmptyListException" << endl;
    }
    
    try
    {
        ArrayList<int> test = ArrayList<int>();
        ArrayList<int>::Iterator p = test.begin();
        test.insert(p, 1);
        test.remove(p);
        test.remove(p);
    }
    catch(const EmptyListException& e)
    {
        cout << "Caught EmptyListException" << endl;
    }
    
}

void testIntegerIterator()
{
    ArrayList<int> L = ArrayList<int>(4);
    for (int i = 0; i < 6; i++)
    {
        L.insertBack(i*2);
    }
    
    for (ArrayList<int>::Iterator iter = L.begin(); iter != L.end(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;

    for (int i = 0; i < 3; i++)
    {
        L.removeFront();
    }
    
    for (int i = 0; i < 3; i++)
    {
        L.insertBack(i*3);
    }
    
    for (ArrayList<int>::Iterator iter = L.begin(); iter != L.end(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;
}

void testStringIterator()
{
    ArrayList<string> L = ArrayList<string>(4);
    const string C_TEST_STR = "test";
    const char C_TEST_START_CHAR = 'A';
    for (int i = 0; i < 6; i++)
    {
        L.insertBack((char)(C_TEST_START_CHAR + i) + C_TEST_STR);
    }
    
    for (ArrayList<string>::Iterator iter = L.begin(); iter != L.end(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;

    for (int i = 0; i < 3; i++)
    {
        L.removeFront();
    }

    for (int i = 0; i < 3; i++)
    {
        L.insertBack((char)(C_TEST_START_CHAR + i) + C_TEST_STR);
    }

    for (ArrayList<string>::Iterator iter = L.begin(); iter != L.end(); ++iter)
    {
        cout << *iter << " ";
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    testArrayListUnderflow();
    cout << endl;
    testIntegerIterator();
    cout << endl;
    testStringIterator();
    
    return 0;
}
