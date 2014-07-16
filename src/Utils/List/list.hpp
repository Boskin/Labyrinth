/* This is a simple, user-define double linked list class. */

#ifndef LIST_HPP
#define LIST_HPP

// Nodes that make up the list
template <class Type> class Node {
    public:
    
    Type data; // Data the node contains
    
    // Adjacent nodes
    Node* next; // Next node, NULL if last node in the list
    Node* prev; // Previous node, NULL if first node in this list
    
    // Constructors
    Node();
    Node(Type _data);
    
    // Destructor
    ~Node();
};

template<class Type> class Iterator; // Forward declaration of iterator class

template <class Type> class List {
    private:
    
    int length; // Current length of the list
    
    // Endpoints of the list
    Node<Type>* head; // Start of the list
    Node<Type>* tail; // End of the list
    
    public:
    
    int size(); // Returns the length of the list
    void add(Type data); // Appends a new node containing the specified data to the list
    void insert(int i, Type data); // Inserts a new node containing the specified data at the specified location
    Type remove(int i); // Removes the data at the specified location
    
    Type& operator [](int i); // Array-like reference operator
    
    friend class Iterator<Type>; // Iterator class is specified as a friend
    
    // Constructors
    List(); // Creates an empty list
    List(int _length); // Creates a list with the specified length
    
    // Destructor
    ~List();
};

template <class Type> class Iterator {
    private:
    
    Node<Type>* node; // Node being pointed at
    
    public:
    
    Type& get(); // Returns a reference to the data
    
    void next(); // Moves to the next node in the list
    void prev(); // Moves to the previous node in the list
    
    bool valid(); // Checks to see if it is pointing to a valid node
    
    // Overloaded operators
    Iterator<Type>& operator =(Iterator<Type> other); // Assignment overload
    Iterator<Type> operator +(int i); // Makes an iterator i nodes ahead
    Iterator<Type> operator -(int i); // Moves an iterator i nodes behind
    Iterator<Type>& operator +=(int i); // Moves forward in the list i times
    Iterator<Type>& operator -=(int i); // Moves backward in the list i times
    Iterator<Type>& operator ++(); // Moves forward once
    Iterator<Type> operator ++(int);
    Iterator<Type>& operator --(); // Moves backward once
    Iterator<Type> operator --(int);
    
    Iterator();
    Iterator(List<Type>* list, int startPos = 0);
    ~Iterator();
};

#include "list.cxx"

#endif

