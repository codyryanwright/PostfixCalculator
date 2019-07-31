//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT stack: Array-based implementation.
 Listing 7-1
 @file ArrayStack.h */

#ifndef ARRAY_STACK_
#define ARRAY_STACK_

#include "StackInterface.h"

const int MAX_STACK = 5;

template<class ItemType>
class ArrayStack : public StackInterface<ItemType>
{
private:	
	ItemType items[MAX_STACK]; // Array of stack items
	int      top;              // Index to top of stack (last element filled in the array)
	
public:
	 ArrayStack();             // Default constructor
	 bool isEmpty() const;
	 bool push(const ItemType& newEntry); // Add to "top" of stack (last in the array)
	 bool pop();               // Remove from stack
	 ItemType peek() const;	   //  Look at what is in "top" of stack
}; // end ArrayStack

#include "ArrayStack.cpp"
#endif
