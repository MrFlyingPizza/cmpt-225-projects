#include <string>
#include <iostream>

#include "Entry.h"
#include "SkipList.h"

using namespace std;

int main()
{
    srand(time(0));

    const int n = 8;

    SkipList sl = SkipList();
    Entry e[n];
    /* put test */
    for (int i = 0; i < n; ++i)
    {
        e[i].random();
        sl.put(e[i].getKey(), e[i].getValue());

    }
    sl.print();

    /* erase test */
    const int to_erase = e[n-1].getKey();
    cout << "Key to erase: " << to_erase << endl;
    sl.erase(to_erase);
    sl.print();

    /* find existing test */
    int to_find = e[rand()%sl.size()].getKey();
    cout << "Finding an existing entry with key " << to_find << endl
        << "Result: " << sl.find(to_find).toString() << endl;

    /* find deleted test */
    cout << "Finding an deleted entry with key " << to_erase << endl
        << "Result: " << sl.find(to_erase).toString() << endl;

    /* greater than test */
    const int k = rand()%100;
    cout << "Finding an entry greater than " << k << ':'
        << " result: " << sl.greaterEntry(k).toString() << endl;

    /* less than test */
    cout << "Finding an entry less than " << k << ':'
        << " result: " << sl.lesserEntry(k).toString() << endl;
    
    /* large put test */
    SkipList sl_other = SkipList();
    Entry q;
    const int m = 40;
    cout << "Inserting " << m << " elements to new skiplist:" << endl;
    for (int i = 0; i < m; i++)
    {
        q.random();
        sl.put(q.getKey(), q.getValue());
    }
    
    sl.print();
}
