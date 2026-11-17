#include <stack>
#include <string>

using std::stack;
using std::string;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for(char& c: s) {
            if(!isClosing(c)) {
                st.push(c);
            } else {
                if(st.empty() || !match(st.top(), c)) return false;

                st.pop();
            }
        }

        return st.empty();
    }

    bool isClosing(char c) {
        return c == '}' || c == ')' || c == ']';
    }

    bool match(char open, char close) {
        return (open == '(' && close == ')') || (open == '[' && close == ']') || (open == '{' && close == '}');
    }
};
