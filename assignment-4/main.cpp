#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Entry.h"
#include "Heap.h"

using namespace std;

string entriesToString(Entry const* entries, const int n)
{
    string st = "{ ";
    for (int i = 0; i < n; ++i)
    {
        st.append(entries[i].toString());
        if (i != n-1)
            st.append(", ");
    }
    st.append(" }");
    return st;
}

Entry* heapsort1(Entry* entries, const int n)
{
    Heap heap;
    for (int i = 0; i < n; ++i)
        heap.insert(entries[i]);

    for (int i = n-1; i >= 0; --i)
        entries[i] = heap.removeMax();

    return entries;
}

Entry* heapsort2(Entry* entries, const int n)
{
    Heap heap;
    heap.make(entries, n);

    for (int i = n-1; i >= 0; --i)
        entries[i] = heap.removeMax();

    return entries;
}

void test_heapsort1(const int n)
{
    Entry entries[n];
    for (int i = 0; i < n; ++i)
        entries[i].random();
    cout << "unsorted: " << entriesToString(entries, n) << endl;

    heapsort1(entries, n);

    cout << "  sorted: " << entriesToString(entries, n) << endl;
}

void test_heapsort2(const int n)
{
    Entry entries[n];
    for (int i = 0; i < n; ++i)
        entries[i].random();
    
    cout << "unsorted: " << entriesToString(entries, n) << endl;

    heapsort1(entries, n);

    cout << "  sorted: " << entriesToString(entries, n) << endl;
}

int main()
{
    srand(time(0));

    cout << "TEST 1 - heapsort1() n=15 :" << endl;
    test_heapsort1(15);

    cout << "TEST 2 - heapsort2() n=15 :" << endl;
    test_heapsort2(15);

    cout << "TEST 3 - heapsort2() n=31 :" << endl;
    test_heapsort1(31);

    cout << "TEST 4 - heapsort2() n=31 :" << endl;
    test_heapsort2(31);
}