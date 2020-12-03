#include <iostream>
#include "AVLTree.h"
#include "Node.h"

using namespace std;

void test1()
{
    cout << "\t- TEST 1 -\n";
    AVLTree tree = AVLTree();
    const int num_vals = 7;

    cout << "Inserting " << 7 << " values." << endl; 

    for (int i = 0; i < num_vals; ++i)
        cout << "\tinserted: " << tree.put(i).key() << endl;
    
    cout << tree;

    const int to_erase = 4;

    cout << "Erasing: " << to_erase << endl;

    tree.erase(4);

    cout << tree;

    int to_find = 2;

    cout << "Finding existing key: " << to_find << endl;
    cout << "Result: " << tree.find(to_find) << endl;

    to_find = 99;

    cout << "Finding not existing key: " << to_find << endl;
    cout << "Result: " << tree.find(99) << endl;
}

void test2()
{
    cout << "\t- TEST 2 -\n";
    const int num_vals = 15;
    int entries[num_vals];

    const int rand_cap = 100;

    cout << "Generating " << num_vals << " values with range 0 - " << rand_cap-1 << endl; 
    for (int& i : entries)
        i = rand() % rand_cap;

    cout << "Inserting generated entries." << endl;
    AVLTree tree = AVLTree();
    for (int i : entries)
        cout << "\tinserted: " << tree.put(i) << endl;
    
    cout << tree;

    for (int i = 0; i < 5; ++i)
    {
        cout << "\t erasing: " << entries[i] << endl;
        tree.erase(entries[i]);
    }

    cout << tree;
}

int main(int argc, char const *argv[])
{
    srand(time(0));
    test1();
    test2();

    return 0;
}
