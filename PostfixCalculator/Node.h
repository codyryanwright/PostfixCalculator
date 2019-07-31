//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** @file Node.h 
    Listing 4-1 */
#ifndef NODE_
#define NODE_

template<class ItemType>
class Node
{
private:
   ItemType        item; // A data item
   Node<ItemType>* next; // Pointer to next node
   
public:
   Node();
   Node(const ItemType& anItem);
   Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
   void setItem(const ItemType& anItem);        // Put item into node
   void setNext(Node<ItemType>* nextNodePtr);   // Set the pointer (can be used to set null or change where it points)
   ItemType getItem() const ;                   // Returns the object in the node
   Node<ItemType>* getNext() const ;            // Returns the pointer to the next node
}; // end Node

#include "Node.cpp"
#endif
