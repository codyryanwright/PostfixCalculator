//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** Listing 7-4.
    @file LinkedStack.cpp */

#include <cassert>        // For assert
#include "LinkedStack.h"  // Header file

template<class ItemType>
LinkedStack<ItemType>::LinkedStack() : topPtr(nullptr)  // In linked top is an address to a node
{
}  // end default constructor

template<class ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& aStack)
{
   // Point to nodes in original chain
   Node<ItemType>* origChainPtr = aStack.topPtr;
   
   if (origChainPtr == nullptr)  // If stack copied was empty
      topPtr = nullptr;  // This stack will be empty
   else
   {
      // Copy first node
      topPtr = new Node<ItemType>(); // dynamically allocated Node
      topPtr->setItem(origChainPtr->getItem()); // put Item in Node
      
      // Point to last node in new chain
      Node<ItemType>* newChainPtr = topPtr;     
      
      // Advance original-chain pointer
      origChainPtr = origChainPtr->getNext();
      
      // Copy remaining nodes
      while (origChainPtr != nullptr)
      {
         // Get next item from original chain
         ItemType nextItem = origChainPtr->getItem();
         
         // Create a new node containing the next item 
         Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);  
         
         // Link new node to end of new chain
         newChainPtr->setNext(newNodePtr); 
         
         // Advance pointer to new last node      
         newChainPtr = newChainPtr->getNext();
         
         // Advance original-chain pointer
         origChainPtr = origChainPtr->getNext();
      }  // end while
      
      newChainPtr->setNext(nullptr);           // Flag end of chain
   }  // end if
}  // end copy constructor

template<class ItemType>
LinkedStack<ItemType>::~LinkedStack()
{
	// Pop until stack is empty
	while (!isEmpty())
		pop();           // pop's top until empty
}  // end destructor

template<class ItemType>
bool LinkedStack<ItemType>::isEmpty() const
{
	return topPtr == nullptr;  // if the top pointer points to nothing, there is no top, it's empty
}  // end isEmpty

template<class ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newItem)
{
	Node<ItemType>* newNodePtr = new Node<ItemType>(newItem, topPtr);				
	topPtr = newNodePtr;
   newNodePtr = nullptr;
      
	return true;
}  // end push

template<class ItemType>
bool LinkedStack<ItemType>::pop()
{
	bool result = false;
	if (!isEmpty())
	{
      // Stack is not empty; delete top
		Node<ItemType>* nodeToDeletePtr = topPtr;
		topPtr = topPtr->getNext(); // next is the new top
		
		// Return deleted node to system
      nodeToDeletePtr->setNext(nullptr); //set pointer to next in old top to null
		delete nodeToDeletePtr;
      nodeToDeletePtr = nullptr; //
            
      result = true;
	}  // end if
   
	return result;	
}  // end pop

template<class ItemType>	
ItemType LinkedStack<ItemType>::peek() const
{
	assert(!isEmpty());  // Enforce precondition
   
	// Stack is not empty; return top
	return topPtr->getItem();
}  // end peek
// End of implementation file.
