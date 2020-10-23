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


string infixToPostfix(const string& expr)
{
    string postfixNotation;
    stack<char> s;
    for (size_t i = 0, sz = expr.size(); i < sz; i++) {
        if(expr[i] == '(') {
            s.push(expr[i]);
        }
        else if (expr[i] == ')') {
            while (!s.empty() && s.top() != '(') {
                postfixNotation.push_back(s.top());
                s.pop();
            }
            s.pop();
        }
        else if ((expr[i] >= 'a' &&  expr[i] <= 'z') || (expr[i] >= '0' && expr[i] <= '9')) {
            postfixNotation.push_back(expr[i]);
        }
        else {
            while(!s.empty() && precedence(s.top()) >= precedence(expr[i]) ) {
                postfixNotation.push_back(s.top());
                s.pop();
            }
            s.push(expr[i]);
        }
    }
    while(!s.empty()) {
        postfixNotation.push_back(s.top());
        s.pop();
    }
    return postfixNotation;
}


int calculateRPN(const string& expr)
{
    string toRPN = infixToPostfix(expr);
    stack<int> s;
    for (size_t i = 0, sz = toRPN.size(); i < sz; i++) {
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

bool isPalindrome(const string& word)
{
    bool isPali = true;
    stack<char> reverse;
    for (size_t i = 0, sz = word.size(); i < sz; i++)
        reverse.push(word[i]);

    for (size_t i = 0, sz = word.size(); i < sz; i++) {
        if(reverse.top() != word[i]) {
            isPali = false;
            break;
        }
        reverse.pop();
    }
    return isPali;
}


int checkTable(const string& table, char key)
{
    for (size_t i = 0, sz = table.size(); i < sz; i++)
        if (table[i] == key)
            return i;
    return -1;
}

bool isBalanced(const string& expr)
{
    stack<char> s;

    const string open("({[");
    const string close(")}]");


    int at  = 0;
    for (size_t i=0, sz = size_t(expr.size()); i < sz; i++) {
        if(checkTable(open, expr[i]) >= 0) {
            s.push(expr[i]);
            continue;
        }

        if(!s.empty() && (at = checkTable(close, expr[i])) >= 0 && expr[i] == close[at])
            s.pop();
        else if(at < 0)
            continue;
        else
            return false;
    }

    return s.empty();
}



int main()
{
    cout << isPalindrome("aabbaa") << endl;
    cout << isBalanced("(asd[asd{asdasd}a]bb)") << " " << isBalanced("(asd[asd{asdasd}]abb)") << endl;
    cout << infixToPostfix("a+b*c-d*e") << endl;
    cout << infixToPostfix("(a+b)*c") << endl;
    cout << calculateRPN("2*3+4*(5-6)") << endl;

    return 0;
}

