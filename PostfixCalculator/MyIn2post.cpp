#include<iostream>
#include<cstring>
#include <string>

#include "LinkedStack.h" // I chose to use LinkedStack for my implementation

using namespace std;

// get weight of operators as per precedence
// higher weight given to operators with higher precedence
// for non operators, return 0 
int getWeight(char ch)
{
   switch (ch)
   {
      case '/':
      case '*': return 2;
      case '+':
      case '-': return 1;
      default : return 0;
   }
}

// convert infix expression to postfix using a stack
string infix2postfix(string infix, const int size)
{
   LinkedStack<char> s; //buffer
   int weight;
   int i = 0; // iterator for infix
   char ch;
   string postfix{""};
   
   // iterate over the infix expression   
   while (i < size)
   {
      ch = infix[i];
      if (ch == '(') 
      {
         // simply push the opening parenthesis
         s.push(ch);
         i++;
         continue;
      }
      if (ch == ')') 
      {
         // if we see a closing parenthesis,
         // pop of all the elements and append it to
         // the postfix expression till we encounter
         // a opening parenthesis
         while (!s.isEmpty() && s.peek() != '(') 
         {
            postfix+=s.peek();
            s.pop();
         }
         // pop off the opening parenthesis also
         if (!s.isEmpty())
         {
            s.pop();
         }
         i++;
         continue;
      }
      weight = getWeight(ch);
      if (weight == 0)
      {
         // we saw an operand
         // simply append it to postfix expression
         postfix+=ch; // Start-up uses "k" as index, I got rid of k and just += append
      }
      else
      {
         // we saw an operator
         if (s.isEmpty())
         {
            // simply push the operator onto stack if
            // stack is isEmpty
            s.push(ch);
         }
         else
         {
            // pop of all the operators from the stack and
            // append it to the postfix expression till we
            // see an operator with a lower precedence that
            // the current operator
            while (!s.isEmpty() && s.peek() != '(' && weight <= getWeight(s.peek())) 
            { 
              postfix+=s.peek();
              s.pop();
            }
            // push the current operator onto stack
            s.push(ch);
         }
      }
      i++;
   }
  
//    pop of the remaining operators present in the stack
//    and append it to postfix expression 
   while (!s.isEmpty()) {
      postfix+=s.peek();
      s.pop();
   }
//   postfix[k] = 0; // null terminate the postfix expression // postfix tail already null
  return postfix;
}

//// main
//int main()
//{
//  while(true)
//  {
//   string infix{""};
//   string postfix{""};
//   
//   cout <<"Please enter the Infix Expression below\n";
//   getline(cin, infix);
// 
//   int size = infix.length();
//   postfix = infix2postfix(infix, size);
//   cout<<"\nInfix Expression :: "<<infix;
//   cout<<"\nPostfix Expression :: " <<postfix<<endl<<endl;
//  }
//  return 0;
//}

// TEST OUTPUT

//Please enter the Infix Expression below
//(1+2)*(4-3)
//
//Infix Expression :: (1+2)*(4-3)
//Postfix Expression (Reverse Order) :: 12+43-*
//
//Please enter the Infix Expression below
//(4+8)*(6-5)/((3-2)*(2+2))
//
//Infix Expression :: (4+8)*(6-5)/((3-2)*(2+2))
//Postfix Expression (Reverse Order) :: 48+65-*32-22+*/
//
//Please enter the Infix Expression below
//3+4*5+(6*7+8)*9
//
//Infix Expression :: 3+4*5+(6*7+8)*9
//Postfix Expression (Reverse Order) :: 345*+67*8+9*+
//
//Please enter the Infix Expression below
//1-(2+3*4)/5
//
//Infix Expression :: 1-(2+3*4)/5
//Postfix Expression (Reverse Order) :: 1234*+5/-

