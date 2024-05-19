#include "b.h"
int main() {
    BTree t(3);
    t.insert(8);
    t.insert(9);
    t.insert(10);
    t.insert(11);
    t.insert(15);
    t.insert(16);
    t.insert(17);
    t.insert(18);
    t.insert(20);
    t.insert(23);
    cout << "Insertion Done";
    cout << "\nBTree elements before deletion: " << endl;
    t.display();
    int ele = 20;
    cout << "\nThe element to be deleted: " << ele;
    t.deletee(20);
    cout << "\nBTree elements before deletion: " << endl;
    t.display();


    BTreeNode* result = t.search(15);
    if (result != nullptr) {
        cout << "\nFound element in the BTree.";
    }
    else {
        cout << "\nElement  not found in the BTree.";
    }

}