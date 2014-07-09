#include <cstdlib>
#include "list.hpp"

// Creates an empty lone node
template <class Type>
Node<Type>::Node(): next(NULL), prev(NULL) {}

// Creates a lone node with the given data
template <class Type>
Node<Type>::Node(Type _data): data(_data), next(NULL), prev(NULL) {}

template <class Type>
Node<Type>::~Node() {
    // Recursively frees all nodes connected
    if(next != NULL)
        delete next;
}

// Creates an empty list
template <class Type>
List<Type>::List(): length(0), head(NULL), tail(NULL) {}

// Creates a list with the given length
template <class Type>
List<Type>::List(int _length): length(_length) {
    if(length > 0) {
        head = new Node<Type>; // Creates the head node
        tail = head; // Uses the tail pointer as a counter
        for(int i = 1; i < length; i++) { // Loop for creating nodes
            tail->next = new Node<Type>; // Creates a new node after the counter
            tail->next->prev = tail; // Sets the new node's previous pointer to the counter
            tail = tail->next; // Moves the counter one to the right
        }
    } else {
        // If a length that is 0 or less is given, an empty list is created
        head = NULL;
        tail = NULL;
        length = 0;
    }
}

// Frees list memory
template <class Type>
List<Type>::~List() {
    delete head; // Calls the recursive destructor
}

// Length accessor
template <class Type>
int List<Type>::size() {
    return length;
}

// Appends a piece of data to the end of the list
template <class Type>
void List<Type>::add(Type data) {
    if(length > 0) {
        Node<Type>* newNode = new Node<Type>(data); // Creates a new node after the tail
        // Fills in the adjacent node data
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode; // Updates the tail
    } else if(length == 0) {
        // If the length is 0, the head is allocated and given the data
        head = new Node<Type>(data);
        tail = head;
    }
    length++; // Updates the list's length
}

// Inserts an element at the given position
template <class Type>
void List<Type>::insert(int i, Type data) {
    if(length > 0 && i <= length && i >= 0) {
        Node<Type>* newNode = new Node<Type>(data); // New node with the given data
        Node<Type>* counter = NULL; // Counter
        
        // Seeks the node that currently occupies the given position
        // If the position is the length, one after the tail, append the data
        if(i == length)
            this->add(data);
        // If the position is in the first half of the list, start from the head
        else if(i < length / 2) {
            counter = head;
            for(int j = 0; j < i; j++)
                counter = counter->next;
        }
        // If the position is in the second half of the list, start from the tail
        else if(i >= length / 2) {
            counter = tail;
            for(int j = length - 1; j > i; j--)
                counter = counter->prev;
        }
        
        if(counter != NULL) {
            // Inserts the node at the position
            counter->prev = newNode; // Node originally at the position is pushed forward one
            newNode->next = counter; // New node is one previous with respect to the original node
            }
        
        // If the new node is at one of the ends of the list
        if(i == 0)
            head = newNode;
        else if(i == length)
            tail = newNode;
        
        length++; // Updates the length of the list
    }
}

// Removes the element at the given position and returns it
template <class Type>
Type List<Type>::remove(int i) {
    if(length > 0 && i >= 0 && i < length) { // Checks if the position exists in the list
        Node<Type>* counter = NULL; // Counter
        
        // Determines which end of the list to count from for optimal performance
        if(i < length / 2 && i >= 0) {
            counter = head;
            for(int j = 0; j < i; j++)
                counter = counter->next;
        } else if(i >= length / 2 && i < length) {
            counter = tail;
            for(int j = length - 1; j > i; j--)
                counter = counter->prev;
        }
        
        if(counter != NULL) {
            Type data = counter->data; // A copy of the data the node to be removed contains
            
            // Pointers to the adjacent nodes
            Node<Type>* prev = counter->prev;
            Node<Type>* next = counter->next;
            
            if(prev != NULL)
                prev->next = next; // Points to the node after the removed one
            else
                head = counter->next; // If there is no previous node, update the head
            
            if(next != NULL)
                next->prev = prev; // Points to the node before the removed one
            else
                tail = counter->prev; // If there is no node after the removed one
            
            // Sets the adjacent pointers to NULL to prevent recursive destruction of all of the nodes
            counter->next = NULL;
            counter->prev = NULL;
            
            delete counter; // Frees the node's memory
            length--; // Updates the length of the node
            return data; // Returns a copy of the data the node stored
        }
    }
    
    return (Type)0;
}

// Operator that returns a reference to the desired element
template <class Type>
Type& List<Type>::operator [](int i) {
    Node<Type>* counter = NULL; // Counter
    
    // Starts from the optimal end of the list
    if(i < length / 2 && i >= 0) {
        counter = head;
        for(int j = 0; j < i; j++)
            counter = counter->next;
    } else if(i >= length / 2 && i < length) {
        counter = tail;
        for(int j = length - 1; j > i; j--)
            counter = counter->prev;
    }
    
    return counter->data; // Returns the reference
}

template <class Type>
Iterator<Type>::Iterator(): node(NULL) {}

template <class Type>
Iterator<Type>::Iterator(List<Type>* list, int startPos) {
    if(startPos <= list->size() / 2 && startPos >= 0) {
        node = list->head;
        for(int i = 0; i < startPos; i++)
            node = node->next;
    } else if(startPos > list->size() / 2 && startPos < list->size()) {
        node = list->tail;
        for(int i = 0; i < startPos - list->size(); i++)
            node = node->prev;
    } else
        node = NULL;
}

template <class Type>
Iterator<Type>::~Iterator() {}

template <class Type>
Type& Iterator<Type>::get() {
    return node->data;
}

template <class Type>
void Iterator<Type>::next() {
    if(node != NULL)
        node = node->next;
}

template <class Type>
bool Iterator<Type>::valid() {
    return node != NULL;
}

template <class Type>
Iterator<Type>& Iterator<Type>::operator =(Iterator<Type> other) {
    this->node = other.node;
    return *this;
}

template <class Type>
Iterator<Type> Iterator<Type>::operator +(int i) {
    Iterator<Type> retVal = *this;
    for(int j = 0; j < i && retVal.node != NULL; j++)
        retVal.node = retVal.node->next;
    return retVal;
}

template <class Type>
Iterator<Type> Iterator<Type>::operator -(int i) {
    Iterator<Type> retVal = *this;
    for(int j = 0; j < i && retVal.node != NULL; j++)
        retVal.node = retVal.node->prev;
    return retVal;
}

template <class Type>
Iterator<Type>& Iterator<Type>::operator +=(int i) {
    *this = *this + i;
    return *this;
}

template <class Type>
Iterator<Type>& Iterator<Type>::operator -=(int i) {
    *this = *this - i;
    return *this;
}

template <class Type>
Iterator<Type>& Iterator<Type>::operator ++() {
    *this += 1;
    return *this;
}

template <class Type>
Iterator<Type> Iterator<Type>::operator ++(int dummy) {
    Iterator<Type> retVal = *this;
    ++(*this);
    return retVal;
}

template <class Type>
Iterator<Type>& Iterator<Type>::operator --() {
    *this -= 1;
    return *this;
}

template <class Type>
Iterator<Type> Iterator<Type>::operator --(int dummy) {
    Iterator<Type> retVal = *this;
    --(*this);
    return retVal;
}
