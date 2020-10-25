#include <iostream>
#include "../libs/list_stack.h"
using namespace std;

char* reverseStr(char* str) {
    Stack<char> s;
    for(int i = 0; str[i] != '\0'; ++i) {
        s.push_back(str[i]);
    }

    for(int i = 0; !s.empty(); ++i) {
        str[i] = s.getTop();
        s.pop_back();
    }

    return str;
}

int main() {
    char testStr[15] = "test sentence";
    cout<< reverseStr(testStr)<< endl;

    return 0;
}
