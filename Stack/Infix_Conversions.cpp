#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "StackLL.h"
using namespace std;

string infixToPostfix(string);
string infixToPrefix(string);
string postfixToInfix(string);
string prefixToInfix(string);
string postfixToPrefix(string);
string prefixToPostfix(string);

// valid parenthesis...
bool areValidParenthesis(string);
int getPriority(char);
bool isSymbol(char);

int main() {

    // string s1 = "(a+b)^b^(c+x)";
    // string s1 = "a-b/c*d+e";
    // string s1 = "a+b*c";
    // string s1 = "(a+b)*c-d*f+c";
    // string s1 = "(A-2*(B+C)-D*E)*F";
    // string s1 = "(A * (B + (C / D) ) )"; // -- ABCD/+*
    // string s1 = "K+L-M*N+(O^P)*W/U/V*T+Q";
    string s1 = "K+L-M*N";
    string postfix = infixToPostfix(s1);
    string prefix = infixToPrefix(s1);


    cout << "Input: " << s1 << endl << endl;

    cout << "Infix to postfix: " << postfix << endl;
    cout << "Infix to prefix: " << prefix << endl << endl;

    cout << "Postfix to infix: " << postfixToInfix(postfix) << endl;
    cout << "Prefix to infix: " << prefixToInfix(prefix) << endl << endl;

    cout << "Postfix to prefix: " << postfixToPrefix(postfix) << endl;
    cout << "Prefix to postfix: " << prefixToPostfix(prefix) << endl << endl;
    return 0;
}

// !infix to postfix
string infixToPostfix(string infix) {

    if (infix.size() == 0) {
        cout << "Empty string: " << infix << endl;
        return "";
    }

    if (!(areValidParenthesis(infix))) {
        cout << "Invalid string: " << infix << endl;
        return "";
    }

    string result = "";
    Stack<char> stk;
    for (int i = 0; i < infix.size(); i++) {

        // go through each char from a string.
        char ch = infix[i];
        if (ch == ' ') continue;
        if (ch == '(' || ch == '^') {
            stk.push(ch);
        } else if (ch == ')') {
            while (stk.peek() != '(') {
                char op = stk.peek();
                if (op != ')' && op != '(')
                    result += op;
                stk.pop();
            }
            stk.pop(); // poping '('
        } else if (isSymbol(ch)) {
            while (stk.getStackSize() != 0 && stk.peek() != '(' && getPriority(stk.peek()) >= getPriority(ch)) {
                char op = stk.peek();
                // if (op != ')')
                result += op;
                stk.pop();
            }
            stk.push(ch);
        } else {
            result += ch;
        }

    }
    while (stk.getStackSize() != 0) {
        result += stk.peek();
        stk.pop();
    }
    return result;

}

// !infix to prefix
string infixToPrefix(string infix) {

    if (infix.size() == 0) {
        cout << "Empty string" << endl;
        return "";
    }

    // check for valid parenthesis.
    if (!(areValidParenthesis(infix))) {
        cout << "Invalid string" << endl;
        return "";
    }

    reverse(infix.begin(), infix.end());

    string result = "";
    Stack<char> stk;

    for (int i = 0; i < infix.size(); i++) {
        char ch = infix[i];
        if (ch == ' ') continue;

        if (ch == ')' || ch == '^') {
            stk.push(ch);
        } else if (ch == '(') {
            while (stk.peek() != ')') {
                char op = stk.peek();
                if (op != ')' && op != '(')
                    result += op;
                stk.pop();
            }
            stk.pop(); // poping ')'
        } else if (isSymbol(ch)) {
            while (stk.getStackSize() != 0 && stk.peek() != ')' && getPriority(stk.peek()) > getPriority(ch)) {
                char op = stk.peek();
                // if (op != ')')
                result += op;
                stk.pop();
            }
            stk.push(ch);
        } else {
            result += ch;
        }
    }

    while (stk.getStackSize() != 0) {
        result += stk.peek();
        stk.pop();
    }
    reverse(result.begin(), result.end());
    return result;
}

// !postfix to infix
string postfixToInfix(string postfix) {

    if (postfix.length() == 0) return "";

    string result = "";
    Stack<string> stk;
    for (int i = 0; i < postfix.length();i++) {
        char ch = postfix[i];
        if (ch == ' ') continue;
        // if char is an operand then push on stk.
        if (!isSymbol(ch)) {
            string temp = "";
            temp += ch;
            stk.push(temp);
        }
        // else if char is an operator.
        else {
            string temp2 = stk.peek();
            stk.pop();
            string temp1 = stk.peek();
            temp1 += ch;
            temp1 += temp2;
            stk.pop();
            stk.push(temp1);
        }
    }
    result += stk.peek();
    return result;
}

// !prefix to infix
string prefixToInfix(string prefix) {

    if (prefix.length() == 0) return "";

    reverse(prefix.begin(), prefix.end());
    string result = "";
    Stack<string> stk;
    for (int i = 0; i < prefix.length();i++) {
        char ch = prefix[i];
        if (ch == ' ') continue;
        // if char is an operand then push on stk.
        if (!isSymbol(ch)) {
            string temp = "";
            temp += ch;
            stk.push(temp);
        }
        // else if char is an operator.
        else {
            string temp2 = stk.peek();
            stk.pop();
            string temp1 = stk.peek();
            temp1 += ch;
            temp1 += temp2;
            stk.pop();
            stk.push(temp1);
        }
    }
    result += stk.peek();
    reverse(result.begin(), result.end());
    return result;
}

// !prefix to postfix
string prefixToPostfix(string prefix) {

    if (prefix.length() == 0) return "";

    string result = prefixToInfix(prefix);
    result = infixToPostfix(result);

    return result;
}

// !postfix to prefix
string postfixToPrefix(string postfix) {

    if (postfix.length() == 0) return "";

    string result = postfixToInfix(postfix);
    result = infixToPrefix(result);

    return result;
}

// !is current char a symbol
bool isSymbol(char ch) {
    if (ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == '(' || ch == ')' || ch == '^') return true;
    return false;
}


// !getting priority of a char
int getPriority(char ch) {
    if (ch == '+' || ch == '-') return 1;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '^') return 3;

    return 0;
}

// !are parenthesis valid
bool areValidParenthesis(string s) {

    Stack<char> stk;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') stk.push('(');
        else if (s[i] == ')') {
            if (stk.getStackSize() == 0) return false;
            stk.pop();
        }
    }

    if (stk.getStackSize() == 0) return true;
    return false;
}