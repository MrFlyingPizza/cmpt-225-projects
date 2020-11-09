#include <string>
#include <iostream>

#include "Entry.h"
#include "SkipList.h"

using namespace std;

void test(int count)
{
    srand(time(0));
    SkipList sl = SkipList();
    for (int i = 0; i < count; i++)
    {
        Entry e;
        e.random();
        sl.put(e.getKey(), e.getValue());
        cout << "Inserted: " << e.toString() << endl;
    }
    
    sl.print();
}

int main()
{
    test(10);
    return 0;
}