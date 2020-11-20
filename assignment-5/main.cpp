#include <string>
#include <iostream>

#include "Entry.h"
#include "SkipList.h"

using namespace std;

void test()
{
    SkipList sl;
    Entry temp;
    const int n = 10;
    cout << "Inserted: ";
    for (int i = 0; i < n; ++i)
    {
        temp.random();
        cout << "INSERTING " << temp.toString() << endl;
        sl.put(temp.getKey(), temp.getValue());
        sl.print();
    }
    cout << endl;

    int key = temp.getKey();
    Entry res;
    cout <<  "key to find: " << key << endl;
    res = sl.find(key);
    cout << "find res: " << res.toString() << endl;
    cout << "ERASING " << res.toString() << endl;
    sl.erase(key);
    sl.print();
}

int main()
{
    srand(time(0));
    time_t old = time(0);
    while (true)
    {
        if (time(0) != old)
        {
            test();
            old = time(0);
        }
    }
}
