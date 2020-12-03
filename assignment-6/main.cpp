#include <iostream>
#include "AVLTree.h"
#include "Node.h"

using namespace std;

void test1()
{
    AVLTree tree = AVLTree();
    const int num_vals = 7;

    cout << "Inserting " << 7 << " values" << endl; 

    for (int i = 0; i < num_vals; ++i)
        tree.put(i);
    
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

int main(int argc, char const *argv[])
{
    srand(time(0));
    test1();

    return 0;
}
