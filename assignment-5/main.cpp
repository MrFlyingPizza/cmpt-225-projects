#include <string>
#include <iostream>

#include "Entry.h"
#include "SkipList.h"

using namespace std;

int main()
{
    SkipList sl = SkipList();
    sl.put(2,"str");
    cout << sl.find(1).getKey() << endl
        << sl.greaterEntry(1).getKey() << endl
        << sl.lesserEntry(1).getKey() << endl;
    return 0;
}