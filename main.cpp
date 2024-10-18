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
        newNode->prev = temp; //set the prev of newNode to temp (the current position)
        if (temp->next) //if there is a node after temp, update its prev pointer
            temp->next->prev = newNode;
        else   //if temp is the tail, update tail to newNode
            tail = newNode;
        temp->next = newNode; //then finally you set temps next to newNode
    }
    //a method to delete the first occurence of a node containing the given value
    void delete_val(int value) {
        if (!head) return; //if the list is empty, there is nothing to delete

        Node* temp = head; //start traversing from the head
        
        //traverse until we find the node with matching value
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; //what this does is that if no node with the value is found, return

        //if node to delete has a previous node, adjust the next pointer
        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; // if deleting the head, update head to the next node
        //if node to delete has a next node, adjust the previous pointer
        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; // if deleting the tail, update tail to previous node

        delete temp; //finally delete the node
    }
    //method to delete a node at a given position
    void delete_pos(int pos) {
        if (!head) { //what this does is if the list is empty, print a message and return
            cout << "List is empty." << endl;
            return;
        }
     
        if (pos == 1) { //if the position is the head, simply pop the front node
            pop_front();
            return;
        }
    
        Node* temp = head;
        //traverses the list to what the desired position is
        for (int i = 1; i < pos; i++){
            if (!temp) { //if position exceeds list size, print a message, in this case "position doesnt exist"
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        //if position doesent exist, return message
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
        //if deleting the last node, pop back
        if (!temp->next) {
            pop_back();
            return;
        }
        //adjust the previous and next pointers of surrounding nodes
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        //delete node
        delete temp;
    }
    //a method to add a node at end of the list
    void push_back(int v) {
        Node* newNode = new Node(v); //create new node
        if (!tail)  //if list is empty, set both heads and tail to newNode
            head = tail = newNode;
        else {  //otherwise, link the new node to the end and update tail
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    //adding node at front of list 
    void push_front(int v) {
        Node* newNode = new Node(v); //create new node
        if (!head)
            head = tail = newNode;
        else { //otherwise link the new node to the front and update head
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    //method to remove the first node from the list
    void pop_front() {

        if (!head) { //if the list is empty print message and return
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head; //this is a temporary pointer to store the current head

        //update head to next node in list
        if (head->next) {
            head = head->next; 
            head->prev = nullptr; //update prev of the new head
        }
        else
            head = tail = nullptr; //if this was the only node, set head and tail to nulptr
        delete temp; //delete old head
    }
    //way to remove last node from list
    void pop_back() {
        if (!tail) { //if the list is empty, print message and return
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail; //temporary pointer to store current tail

        //update tail to previous node
        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr; //update next of the new tail
        }
        else
            head = tail = nullptr; //if this was the only node, set head and tail to nullptr
        delete temp; //delete old tail
    }
    //
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