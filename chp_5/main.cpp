#include "bintree.h"
#include <iostream>

using namespace std;

int main()
{
    BinTree<int> btree;
    BinNodePosi<int> node_l, node_r;
    node_r = node_l = btree.insert_as_root(1);

    node_l = btree.insert_as_lc(node_l, 2);
    node_l = btree.insert_as_lc(node_l, 3);
    btree.insert_as_rc(node_l, 4);

    node_r = btree.insert_as_rc(node_r, 5);
    btree.insert_as_lc(node_r, 6);
    btree.insert_as_rc(node_r, 7);

    cout << "Height: " << btree.height() << endl;

    btree.trav_pre([](int e) { cout << e << ' '; });
    cout << endl;
    btree.trav_in([](int e) { cout << e << ' '; });
    cout << endl;
    btree.trav_post([](int e) { cout << e << ' '; });
    cout << endl;
    btree.trav_level([](int e) { cout << e << ' '; });
    cout << endl;
}
