#include <iostream>
#include <stack>
#include <bits/stdc++.h>
#include <ctype.h>
#include <fstream>
#include <string>

using namespace std;

template <class T>
struct node{
	T data;
	node<T> * next;
};
template <class T>
class Stack
{
    public:
        Stack(); //constructor
        virtual ~ Stack();//destructor
        bool empty(); //returns true if stack is empty
        bool push(T data); //insert data
        T peek(); //return top data without removing
        T pop();  //remove top data
       void clearst();//truncate the stack to empty
    protected:
    private:
        node<T> * top;
        int counter;
};
template <class T>
Stack<T>::Stack()
{
    counter=0;
    top=NULL;
}
template <class T>
Stack<T>::~Stack()
{
     clearst();
     delete top;
}
template <class T>
bool Stack<T>::empty()
{
   return counter==0;
}
template <class T>
bool Stack<T>::push(T data)
{
     node<T>* p;
     p=new node<T>;
     p->data=data;
     p->next=top;
     top=p;
     counter++;
}
template <class T>
T Stack<T>::peek()
{
     if(!empty()){

          return top->data;
     }
}
template <class T>
T Stack<T>::pop()
{
     if(!empty()){
          T data;
          node<T> *p;
          p=top;
          top=top->next;
          data=p->data;
          delete p;
          counter --;
          return data;
     }
}
template <class T>
void Stack<T>::clearst()
{
     node<T>* p;
     while(!empty()){
          p=top;
          top=top->next;
          delete p;
     }
     counter=0;
     top=NULL;
}


int associativity(char opr);
int CmpPrec(char oprStck, char operInp);
int symbolType(char symbol);
int precValue(char symbol);
int toPostfix(string infix, string & postfix);
int evaluate(string  postfix);

enum symbolType{ OPERATOR=')' || '+'|| '-' || '*' || '/'|| '^'|| '(' , OPERAND, UNKNOWN=',' || '@' || '#' };
enum Operator{ CPAR=')', ADD='+', SUB='-', MULT='*', DIV='/', EXP='^', OPAR='(' };
enum preced { PCPAR=0, PADD=10, PMULT=15, PEXP=20, PSIGN=25, POPAR=30, PDIV, PSUB};

int associativity(char opr) {
 if(opr == EXP)
    return 1;
 else
    return 0;
 }

int CmpPrec(char oprStck, char operInp) //To check precedence
{

  if( precValue(oprStck)==precValue(operInp))
  {
      return 0;
  }
  else if (precValue(oprStck)>precValue(operInp))
    {
        return -1;
    }
    else{
        return 1;
    }

}

int symbolType(char symbol) {
    if (symbol ==ADD || symbol ==SUB || symbol ==MULT || symbol ==DIV || symbol ==EXP)
        return 1;
    else
        return 0;
}
int precValue(char symbol) {
    if (symbol == '^')
        return 3;
    else if(symbol == '/' || symbol == '*')
        return 2;
    else if(symbol == '+' || symbol == '-')
        return 1;
    else
        return -1;

}

int toPostfix(string infix, string & postfix) {

ifstream istring("miki.txt");
ofstream ostring("miki.txt");
stack <char> s;
string d;

for (int i=0;i<infix.length();i++){
    if (isdigit(infix[i])){

          while( !infix[i] == Operator() && (!symbolType(infix[i])== 1)){
             ostring <<infix[i];
             d+=infix[i];
                i++;
         }
            i--;
            ostring << "," ;
    }

    else if (infix [i] == '(' )
                s.push(infix[i]);
    else if (infix [i] == ')'){
        while ((s.top()!= '(') && (!s.empty())){
                char temp=s.top();
              //  postfix+=temp;
                ostring << temp;
                s.pop();
                d+=temp;
        }

        if(s.top() == '(')
            s.pop();
    }
    else if ( symbolType(infix[i])== 1){
        if(s.empty()){
            s.push(infix[i]);
            }
        else{
            if (CmpPrec(s.top(),infix[i]) == 1)
                s.push(infix[i]);
            else if ((CmpPrec(s.top(),infix[i]) == 0) && (associativity(infix[i]) == 1))
                s.push(infix[i]);
        else{
              while ((!s.empty() &&precValue(infix[i]) <= precValue(s.top()))){
                char temp=s.top();
                ostring << temp ;
                s.pop();
                d+=temp;
                    }
               s.push(infix[i]);

                }
    }
}
}
   while (!s.empty()){
    ostring << s.top();
    d+=s.top();
    s.pop();
  }
ostring.close();

    istring >> postfix;
    cout << "The Postfix is  "<< d << endl;
    return -1;

}
int evaluate(string  postfix) {
    string result;
    stack <string> st;

  for (int i=0;i<postfix.length();i++){
    if (isdigit(postfix[i])){
        string temp;
            while (!(postfix[i]==',')){
            temp+=postfix[i];
            i++;
            }

            st.push(temp);
              i--;

         }

 else if (symbolType(postfix[i])== 1)
    {
            string x = st.top();
            double a = stod(x);
            st.pop();
            string y = st.top();
            double b = stod(y);
            st.pop();
            double r = 0.0;
            string temp1;

        switch (postfix[i])
            {
                case ADD: // addition
                          r=b+a;
                          temp1 = to_string(r);
                          st.push(temp1);
                          break;
                case SUB: // subtraction
                          r=b-a;
                          temp1 = to_string(r);
                          st.push(temp1);
                          break;
                case MULT: // multiplication
                          r=b*a;
                          temp1 = to_string(r);
                          st.push(temp1);
                          break;
                case DIV: // division
                          r=b/a;
                          temp1 = to_string(r);
                          st.push(temp1);
                          break;
                case EXP: // exponent
                          r=pow(b,a);
                          temp1 = to_string(r);
                          st.push(temp1);
                          break;
            }
        }
    }

   result=st.top();
    cout << "The Result is :- " << result << endl;
return -1;
}


int main()
{
    string infix,postfix;

    cout << "Enter The Infix expressions- When you are done hit Enter " << endl;
    cin >> infix;
    toPostfix(infix,postfix);
    evaluate(postfix);
    return 0;

}





















