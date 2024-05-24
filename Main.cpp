#include "b.h"
#include <iostream>
using namespace std;

void displayMenu() {
    cout << "--------------- B-Tree -----------------" << endl;
    cout << "1. Insert element" << endl;
    cout << "2. Delete element" << endl;
    cout << "3. Display tree" << endl;
    cout << "4. Search element" << endl;
    cout << "5. Exit" << endl;
    cout << "-------------------------" << endl;
    cout << "Enter your choice: ";
}

int main() {
    BTree t(3);
    int choice, element;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter element to insert: ";
            cin >> element;
            t.insert(element);
            cout << "Element inserted." << endl;
            break;

        case 2:
            cout << "Enter element to delete: ";
            cin >> element;
            t.deletee(element);
            cout << "Element deleted." << endl;
            break;

        case 3:
            cout << "B-Tree elements:" << endl;
            t.display();
            cout << endl;
            break;

        case 4:
            cout << "Enter element to search: ";
            cin >> element;
            if (t.search(element) != nullptr)
                cout << "Element found." << endl;
            else
                cout << "Element not found." << endl;
            break;

        case 5:
            cout << "Exiting..." << endl;
            return 0;

        default:
            cout << "Invalid choice! Try again!" << endl;
            break;
        }
    }

}
