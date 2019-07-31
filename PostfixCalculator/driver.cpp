// Author:          Cody Wright
// Lab:             Lab 4 Postfix Calculator
// Purpose:         Calculator Accepts Infix or Postfix
// Data Structures: StackInterface, LinkedStack, ArrayStack, Node
// Date:            3/27/2018

#include <iostream>
#include <cstdlib>
#include <string>

#include "LinkedStack.h"
#include "ArrayStack.h"
#include "MyIn2Post.cpp"

using namespace std;

template <typename ItemType>
void postFixCalc(string expression, ItemType &stack )
{
  for (unsigned int i = 0; i<expression.length(); ++i)
  {
    if (isdigit(expression[i])) // is operand
    {
      stack.push(expression[i]-'0'); // converts char to int and pushes to top of stack
    }
    else if (isblank(expression[i])); // ignore, do nothing
    else // is operator
    {
      int operand2 = stack.peek(); stack.pop();
      int operand1 = stack.peek(); stack.pop();
      
      int result{0};
      
      if (expression[i]=='+') result = operand1 + operand2;
      else if (expression[i]=='-') result = operand1 - operand2;
      else if (expression[i]=='*') result = operand1 * operand2;
      else if (expression[i]=='/' && operand2!=0) result = operand1 / operand2;
      else if (expression[i]=='/' && operand2==0)
      {
        cout<<"Malformed Expression: Divide by Zero"<<endl; // Easier to check for this here than in raw expression
        break;
      }
            
      stack.push(result);
    }
  }
}

bool isOperator(char op)
{
  bool validOp{false};
  
  if (op=='+' || op=='-' || op=='*' || op=='/') validOp = true;
  
  return validOp;
}

bool isValidInfix(string expression)
{
  bool validation{false};
  int opCount{0}, digitCount{0};
  
  // validation is initialized as false so just break, no need to keep evaluating, error message thrown in Postfix Check
  // Start Type-checks
  for (unsigned int index = 0; index<expression.length(); index++)
  {
    if (isblank(expression[index]) || expression[index]=='(' || expression[index]==')'); // always ok
    else if (isdigit(expression[index])) ++digitCount; // keep count for operand comparison
    else if (isOperator(expression[index]))
    {
      if (index==0)break; // can't have leading operator
      if (index==expression.length()-1) break; // no trailing operators, MUST proceed next statement
      // Overrunning index is protected by checking if last index before the following check
      if (isOperator(expression[index+1])) break; // no consecutive operators
      ++opCount;
    }
    else break; // not blank, digit, or operator (some illegal special character)
    
    
    // Start Count-checks at final index
    if(index==(expression.length()-1))
    {
      if(opCount>=digitCount) break; // can't have as many or more operators than operands in string
      if(opCount==0 && digitCount>1) break; // if multiple digits, require operand, single digit just returns digit
      if(digitCount > opCount+1) break; // no double digit numbers with this algorithm, so digit count should always be one less than opCount
      
      validation = true;
    }
}
  
  return validation;
};

// Postfix Check happens after Infix, so error messages will print from this check
bool isValidPostfix(string expression)
{
  bool validation{false};
  int opCount{0}, digitCount{0};
  
  for (unsigned int index = 0; index<expression.length(); ++index)
  {
    if (isblank(expression[index]));
    else if (isdigit(expression[index]))
    {
      if((index==expression.length()-1)) // postfix will always end with operator unless just a single digit entered
      {
        cout << "Malformed Expression: Trailing Integer"<<endl;
        break;
      }
      ++digitCount;
    }
    else if (isOperator(expression[index]))
    {
      ++opCount;
      if(index<=1) // can't have leading operator or even operator second in sequence
      {
        cout << "Malformed Expression: Leading Operator"<<endl;
        break;
      }
    }
    else
    {
      cout << "Malformed Expression: Illegal Character"<<endl;
      break;
    }
    
    if(index==(expression.length()-1))
    {
      if(opCount>=digitCount)
      {
        cout << "Malformed Expression: Too Many Operators"<<endl;
        break;
      }
      if(opCount==0 && digitCount>1)
      {
        cout << "Malformed Expression: Missing Operator"<<endl;
        break;
      }
      if(digitCount > opCount+1)
      {
        cout << "Malformed Expression: Missing Operator / Too Many Integers"<<endl;
        break;
      }
      
      validation = true;
    } 
  }
  
  return validation;
};

template <typename ItemType>
void driver(ItemType &stack)
{
  cin.clear();cin.ignore(); // ready for getline

  while(true)
  {
    string expression{""};
    
    cout << "\nEnter your expression: (Press Enter to Quit)"<<endl;
    getline(cin, expression);
  
    if(expression=="") break;
  
    if(isValidInfix(expression)) expression = infix2postfix(expression, expression.length());
  
    if(isValidPostfix(expression))
    {
     // pre: postfix expression, empty stack passed by refference
     // post: stack contains result of expression
     postFixCalc(expression, stack);
     
     if(!stack.isEmpty())
     {
       cout << expression << " = " << stack.peek()<<endl;
       while(!stack.isEmpty()) stack.pop(); //clear for next round
     }
    }
  }
}

int main()
{
  cout<<"This program accepts either infix or postfix integer math expressions and calculates them."<<endl;
  
  while(true)
  {
    string choice{""};
    
    cout<<"\n    Menu"<<endl
        <<" ----------"<<endl
        <<"1) LinkedStack"<<endl
        <<"2) ArrayStack"<<endl
        <<"3) Quit"<<endl
        <<"\nChoice: ";
        
    cin>>choice;
        
    while(choice!="1" && choice!="2" && choice!="3")
    {
      cout<<"\n  Invalid Choice, Please enter option 1, 2, or 3 : ";
      cin>>choice;
    }
   
    LinkedStack<int> lStack;
    ArrayStack<int> aStack;
    
    if(choice == "1")
    {
      cout<<"\n\n  LinkedStack"<<endl
          <<" -------------"<<endl;
      driver(lStack);
    }
    else if (choice=="2")
    {
      cout<<"\n\n  ArrayStack"<<endl
          <<" ------------"<<endl;
      driver(aStack);
    }
    else break;
  }
  return 0;
}

/* Test output:
  In folder as TestOutput.txt
*/
