#include <iostream>
#include <stack>
using namespace std;

int precedence(char c) {
    if (c == '*' || c == '/') {
        return 2;
    }
    else if (c == '+' || c == '-') {
        return 1;
    }
    return  0;
}


std::string infixToPostfix(std::string expr)
{
    std::string postfixNotation;
    std::stack<char> s;
    for (unsigned i = 0, sz = unsigned(expr.size()); i < sz; i++) {
        if(expr[i] == '(') {
            s.push(expr[i]);
        }
        else if (expr[i] == ')') {
            while (s.size() && s.top() != '(') {
                postfixNotation.push_back(s.top());
                s.pop();
            }
            s.pop();
        }
        else if ((expr[i] >= 'a' &&  expr[i] <= 'z') || (expr[i] >= '0' && expr[i] <= '9')) {
            postfixNotation.push_back(expr[i]);
        }
        else {
            while(s.size() && precedence(s.top()) >= precedence(expr[i]) ) {
                postfixNotation.push_back(s.top());
                s.pop();
            }
            s.push(expr[i]);
        }
    }
    while(s.size()) {
        postfixNotation.push_back(s.top());
        s.pop();
    }
    return postfixNotation;
}


int calculateRPN(std::string expr)
{
    std::string toRPN = infixToPostfix(expr);
    stack<int> s;
    for (unsigned i = 0, sz = unsigned(toRPN.size()); i < sz; i++) {
        if (toRPN[i] >= '0' && toRPN[i] <= '9') {
            s.push(toRPN[i] - '0');
        }
        else {
            int right = s.top();
            s.pop();
            int left = s.top();
            s.pop();
            switch (toRPN[i]) {
            case '+': s.push(left + right);break;
            case '-': s.push(left - right);break;
            case '*': s.push(left * right);break;
            case '/': s.push(left / right);break;
            }
        }
    }
    return s.top();
}

bool isPalindrome(std::string word)
{
    bool isPali = true;
    std::stack<char> reverse;
    for (unsigned i = 0; i < word.size(); i++) {
        reverse.push(word[i]);
    }

    for (unsigned i = 0; i < word.size(); i++) {
        if(reverse.top() != word[i]) {
            isPali = false;
            break;
        }
        reverse.pop();
    }
    return isPali;
}

bool isBalanced(string expr)
{
    stack<char> s;
    for (unsigned i=0, sz = unsigned(expr.size()); i < sz; i++)
    {
        if (expr[i]=='('||expr[i]=='['||expr[i]=='{') {
            s.push(expr[i]);
            continue;
        }
        if (expr[i]==')'||expr[i]==']'||expr[i]=='}') {
            if (s.empty()) {
                return false;
            }
            else {
                switch (expr[i]) {
                case ')':
                    if (s.top() != '(') {
                        return false;
                    }
                    s.pop();
                    break;

                case '}':
                    if (s.top()=='(' || s.top()=='[') {
                        return false;
                    }
                    s.pop();
                    break;

                case ']':
                    if (s.top()=='{' || s.top()=='(') {
                        return false;
                    }
                    s.pop();
                    break;
                }
            }
        }

    }

    return (s.empty());
}



int main()
{
    cout << isPalindrome("aabbaa") << endl;
    cout << isBalanced("(asd[asd{asdasd}]abb)") << " " << isBalanced("(asd[asd{asdasd}]abb)") << "";
    cout << infixToPostfix("a+b*c-d*e") << endl;
    cout << infixToPostfix("(a+b)*c") << endl;
    cout << calculateRPN("2*3+4*(5-6)") << endl;

    return 0;
}
