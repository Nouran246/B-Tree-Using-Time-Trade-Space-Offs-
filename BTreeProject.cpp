#include "b.h"

// BTreeNode Constructor
BTreeNode::BTreeNode(int t1, bool leaf1) {
    MinDegree = t1;
    leaf = leaf1;
    keys = new int[2 * MinDegree - 1];
    ChildPointer = new BTreeNode * [2 * MinDegree];
    NumOfKeys = 0;
}

// Display the BTree
void BTreeNode::display() {
    int i;
    for (i = 0; i < NumOfKeys; i++) {
        if (leaf == false)
            ChildPointer[i]->display();
        cout << keys[i] << " ";
    }
    if (leaf == false)
        ChildPointer[i]->display();
}

// Split the child y of this node. i is the index of y in child array C[].
void BTreeNode::split(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->MinDegree, y->leaf);
    z->NumOfKeys = MinDegree - 1;

    for (int j = 0; j < MinDegree - 1; j++)
        z->keys[j] = y->keys[j + MinDegree];

    if (y->leaf == false) {
        for (int j = 0; j < MinDegree; j++)
            z->ChildPointer[j] = y->ChildPointer[j + MinDegree];
    }

    y->NumOfKeys = MinDegree - 1;

    for (int j = NumOfKeys; j >= i + 1; j--)
        ChildPointer[j + 1] = ChildPointer[j];

    ChildPointer[i + 1] = z;

    for (int j = NumOfKeys - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[MinDegree - 1];

    NumOfKeys = NumOfKeys + 1;
}

int BTreeNode::getPred(int index) {
    BTreeNode* cur = ChildPointer[index];
    while (!cur->leaf)
        cur = cur->ChildPointer[cur->NumOfKeys];
    return cur->keys[cur->NumOfKeys - 1];
}

int BTreeNode::getSucc(int index) {
    BTreeNode* cur = ChildPointer[index + 1];
    while (!cur->leaf)
        cur = cur->ChildPointer[0];
    return cur->keys[0];
}

void BTreeNode::fill(int index) {
    if (index != 0 && ChildPointer[index - 1]->NumOfKeys >= MinDegree)
        getFromPrevious(index);
    else if (index != NumOfKeys && ChildPointer[index + 1]->NumOfKeys >= MinDegree)
        getFromNext(index);
    else {
        if (index != NumOfKeys)
            merge(index);
        else
            merge(index - 1);
    }
    return;
}

void BTreeNode::getFromPrevious(int index) {
    BTreeNode* child = ChildPointer[index];
    BTreeNode* sibling = ChildPointer[index - 1];

    for (int i = child->NumOfKeys - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->NumOfKeys; i >= 0; --i)
            child->ChildPointer[i + 1] = child->ChildPointer[i];
    }

    child->keys[0] = keys[index - 1];

    if (!child->leaf)
        child->ChildPointer[0] = sibling->ChildPointer[sibling->NumOfKeys];

    keys[index - 1] = sibling->keys[sibling->NumOfKeys - 1];

    child->NumOfKeys += 1;
    sibling->NumOfKeys -= 1;

    return;
}

void BTreeNode::getFromNext(int index) {
    BTreeNode* child = ChildPointer[index];
    BTreeNode* sibling = ChildPointer[index + 1];

    child->keys[(child->NumOfKeys)] = keys[index];

    if (!(child->leaf))
        child->ChildPointer[(child->NumOfKeys) + 1] = sibling->ChildPointer[0];

    keys[index] = sibling->keys[0];

    for (int i = 1; i < sibling->NumOfKeys; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->NumOfKeys; ++i)
            sibling->ChildPointer[i - 1] = sibling->ChildPointer[i];
    }

    child->NumOfKeys += 1;
    sibling->NumOfKeys -= 1;

    return;
}

void BTreeNode::merge(int index) {
    BTreeNode* child = ChildPointer[index];
    BTreeNode* sibling = ChildPointer[index + 1];

    child->keys[MinDegree - 1] = keys[index];

    for (int i = 0; i < sibling->NumOfKeys; ++i)
        child->keys[i + MinDegree] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->NumOfKeys; ++i)
            child->ChildPointer[i + MinDegree] = sibling->ChildPointer[i];
    }

    for (int i = index + 1; i < NumOfKeys; ++i)
        keys[i - 1] = keys[i];

    for (int i = index + 2; i <= NumOfKeys; ++i)
        ChildPointer[i - 1] = ChildPointer[i];

    child->NumOfKeys += sibling->NumOfKeys + 1;
    NumOfKeys--;

    delete sibling;
    return;
}

// Search function using m-way search
BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    while (i < NumOfKeys && k > keys[i])
        i++;

    if (keys[i] == k)
        return this;

    if (leaf == true)
        return NULL;

    if (i < NumOfKeys)
        return ChildPointer[i]->search(k);

    return ChildPointer[NumOfKeys - 1]->search(k);
}

void BTree::insert(int k) {
    int max = (2 * MinDegree - 1);

    if (root == NULL) {
        root = new BTreeNode(MinDegree, true);
        root->keys[0] = k;
        root->NumOfKeys = 1;
    }
    else {
        if (root->NumOfKeys == max) {
            BTreeNode* newNode = new BTreeNode(MinDegree, false);
            newNode->ChildPointer[0] = root;
            newNode->split(0, root);

            int index = 0;
            if (newNode->keys[0] < k) {
                index++;
            }
            newNode->ChildPointer[index]->insertNonFull(k);
            root = newNode;
        }
        else {
            root->insertNonFull(k);
        }
    }
}

void BTreeNode::insertNonFull(int k) {
    int max = (2 * MinDegree - 1);
    int i = NumOfKeys - 1;

    if (leaf == true) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        NumOfKeys++;
    }
    else {
        while (i >= 0 && keys[i] > k) {
            i--;
        }
        i++;
        if (ChildPointer[i]->NumOfKeys == max) {
            split(i, ChildPointer[i]);
            if (keys[i] < k)
                i++;
        }
        ChildPointer[i]->insertNonFull(k);
    }
}

void BTree::deletee(int k) {
    if (!root) {
        cout << "The tree is empty\n";
        return;
    }

    root->deletee(k);

    if (root->NumOfKeys == 0) {
        BTreeNode* temp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->ChildPointer[0];
        delete temp;
    }
    return;
}

void BTreeNode::deletee(int k) {
    int index = 0;
    while (index < NumOfKeys && keys[index] < k)
        ++index;

    if (index < NumOfKeys && keys[index] == k) {
        if (leaf)
            removeLeaf(index);
        else
            removeNonLeaf(index);
    }
    else {
        if (leaf) {
            cout << "The key " << k << " is does not exist in the tree\n";
            return;
        }
        bool flag = ((index == NumOfKeys) ? true : false);

        if (ChildPointer[index]->NumOfKeys < MinDegree)
            fill(index);

        if (flag && index > NumOfKeys)
            ChildPointer[index - 1]->deletee(k);
        else
            ChildPointer[index]->deletee(k);
    }
    return;
}

void BTreeNode::removeLeaf(int index) {
    for (int i = index + 1; i < NumOfKeys; ++i)
        keys[i - 1] = keys[i];
    NumOfKeys--;
    return;
}

void BTreeNode::removeNonLeaf(int index) {
    int k = keys[index];

    if (ChildPointer[index]->NumOfKeys >= MinDegree) {
        int pred = getPred(index);
        keys[index] = pred;
        ChildPointer[index]->deletee(pred);
    }
    else if (ChildPointer[index + 1]->NumOfKeys >= MinDegree) {
        int succ = getSucc(index);
        keys[index] = succ;
        ChildPointer[index + 1]->deletee(succ);
    }
    else {
        merge(index);
        ChildPointer[index]->deletee(k);
    }
    return;
}

