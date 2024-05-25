#include <iostream>
using namespace std;

class BTreeNode {
    int* keys; // An array of keys
    int MinDegree; // Minimum degree (defines the range for the number of keys)
    BTreeNode** ChildPointer; // An array of child pointers
    int NumOfKeys; // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false

public:
    BTreeNode(int _t, bool _leaf); // Constructor
    void display();
    void insertNonFull(int k);
    void split(int i, BTreeNode* y);
    void deletee(int k);
    void removeLeaf(int index);
    void removeNonLeaf(int index);
    int getPred(int index);
    int getSucc(int index);
    void fill(int index);
    void getFromPrevious(int index);
    void getFromNext(int index);
    void merge(int index);
    BTreeNode* search(int k);

    // Make the BTree friend of this so that we can access its members
    friend class BTree;
};

class BTree {
    BTreeNode* root; // Pointer to the root node
    int MinDegree; // Minimum degree

public:
    BTree(int _MinDegree) {
        root = NULL;
        MinDegree = _MinDegree;
    }
    void display() {
        if (root != NULL)
            root->display();
    }

    BTreeNode* search(int k) {
        return (root == NULL) ? NULL : root->search(k);
    }
 bool isEmpty() {
     return root == NULL;
 }

    void insert(int k);
    void deletee(int k);
};
