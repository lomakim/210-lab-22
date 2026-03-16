// COMSC-210 | Lab 22 | Loma Kim
#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
    private: struct Node {
        int data;
        Node * prev;
        Node * next;
        Node(int val, Node * p = nullptr, Node * n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };
    Node * head;
    Node * tail;

    public:
    // constructor
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void push_back(int value) {
        Node * newNode = new Node(value);
        if (!tail) // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail -> next = newNode;
            newNode -> prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node * newNode = new Node(value);
        if (!head) // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode -> next = head;
            head -> prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }
        Node * newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }
        Node * temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp -> next;
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        newNode -> next = temp -> next;
        newNode -> prev = temp;
        if (temp -> next)
            temp -> next -> prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp -> next = newNode;
    }
    
    void delete_val(int value) {
        if (!head) 
            return; // Empty list
        Node * temp = head;
        while (temp && (temp->data != value))
            temp = temp->next;

        if (!temp) 
            return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next; 
        } 
        else {
            head = temp->next; // Deleting the head
        }
        if (temp->next) {
            temp->next->prev = temp->prev;
        } 
        else {
            tail = temp->prev; // Deleting the tail
        }
        delete temp;
    }

    void delete_pos(int pos) {
        Node * current = head;
        Node * successor = nullptr;
        Node * predecessor = nullptr;

        if(!head) {
            cout << "List is empty!";
            return;
        }

        for(int i = 0; i < pos; i++) {
            current = current->next;
            successor = current->next;
            predecessor = current->prev;
        }

        if (successor)
            successor->prev = predecessor;
        if (predecessor)
            predecessor->next = successor;
        if (current == head)
            head = successor;
        if (current == tail)
            tail = predecessor;

        delete current;
    }

    void pop_front() {
        if (!head) {
            cout << "List is empty!";
            return;
        }
        else {
            Node * temp = head;
            head = head->next;
            delete temp;
        }
    }

    void pop_back() {
        if (!head) {
            cout << "List is empty!";
            return;
        }
        else {
            Node * temp = tail;
            tail = tail->prev;
            delete temp;
        }
    }

    void print() {
        Node * current = head;
        if (!current) return;
        while (current) {
            cout << current -> data << " ";
            current = current -> next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node * current = tail;
        if (!current) return;
        while (current) {
            cout << current -> data << " ";
            current = current -> prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node * temp = head;
            head = head -> next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(time(0));
    DoublyLinkedList list;
    int size = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS;

    for (int i = 0; i < 16; ++i) {
        list.push_back(rand() % (MAX_NR - MIN_NR + 1) + MIN_NR);
    }
    
    cout << "List forward: ";
    list.print();
    cout << "List backward: ";
    list.print_reverse();

    cout << "Now deleting head using pop_front() function." << endl;
    list.pop_front();

    cout << "List forward: ";
    list.print();
    cout << "List backward: ";
    list.print_reverse();

    cout << "Now deleting tail using pop_back() fucntion." << endl;
    cout << "List forward: ";
    list.print();
    cout << "List backward: ";
    list.print_reverse();

    cout << "Now deleting list item #5 using delete_pos() fucntion. " << endl;
    list.delete_pos(5);
    cout << "List forward: ";
    list.print();
    cout << "List backward: ";
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();

    cout << "List forward: ";
    list.print();

    return 0;
}