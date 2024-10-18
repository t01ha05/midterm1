#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; // constants that might be used later in program, but are currently just used to avoid compiler warning

//definition of the DoublyLinkedList class
class DoublyLinkedList {
private:
    //the Node struct basically represents each element(node) in the linked list
    struct Node {
        int data; //value stored in node
        Node* prev; //pointer to previous node in the list
        Node* next; //pointer to the next node in the list
        //node constructor initialized the nodes value and optionally sets its pointers and next nodes
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p; //by default, previous is set to nullptr
            next = n; //by default next is set to nullptr
        }
    };
 
    Node* head; //pointer to the first node of the list
    Node* tail; //pointer to last node of list

public:
    //constructor initializes the head and tail pointers to nullptr(empty list)
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    //method to insert a new node after a given position
    void insert_after(int value, int position) {
        if (position < 0) { //validate position(but it cant be negative)
            cout << "Position must be >= 0." << endl;
            return;
        }

        //create new node with given value
        Node* newNode = new Node(value);
        
        //if the list is empty, we are setting both head and tail to new node
        if (!head) {
            head = tail = newNode;
            return;
        }

        //start travering list stating for head
        Node* temp = head;
        //moving temp to desired postion(only if its in within bounds)
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        //outputting if position is beyond the current list size, do not exert
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        //here we are inserting newNode after the node at the given postion
        newNode->next = temp->next; // set the next of newNode to the next of temp
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}