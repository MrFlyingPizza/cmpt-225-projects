#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Entry.h"
#include "Heap.h"

using namespace std;

void heapsort1()
{
    
}

void heapsort2()
{

}

int main()
{
    srand(time(0));
    Entry e = Entry();
    Heap heap = Heap();
    const int count = 15;
    string out_st = "unsorted: {";
    for (int i = 0; i < count; i++)
    {
        e.random();
        out_st.append(e.toString());
        heap.insert(e);
        if (i != count-1) out_st.append(",");
    }
    out_st.append("}");
    cout << out_st << endl;
    
    out_st = "sorted: {";
    for (int i = 0; i < count; i++)
    {
        out_st.append(heap.removeMax().toString());
        if (i != count-1) out_st.append(",");
    }
    out_st.append("}");
    cout << out_st << endl;
}