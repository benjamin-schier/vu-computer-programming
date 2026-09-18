// Assignment 3: Digit Sum & Balanced Brackets
//
// See midterm_mock_exam.md, Part 4, for the full assignment description.
//
// Suggested time: 45 minutes total (~20 min Part A, ~25 min Part B).

#include <iostream>
#include <stack>
#include <string>

// Part A
int digitSum(int number);

// Part B
bool isBalanced(const std::string& text);

int main()
{
    // Your code here: call digitSum and isBalanced based on user input.
    // unsigned int number = 4325;
    // std::cout << "Please enter a non negative integer: ";
    // std::cin >> number;
    // std::cout << "Sum of digits: " << digitSum(number) << std::endl;

    std::string s;
    std::cout << "Please enter a line of text: ";
    std::cin >> s;
    std::getline(std::cin, s);
    if (isBalanced(s)) {
        std::cout << "Is balanced" << std::endl;
    }
    else {
        std::cout << "is not balanced" << std::endl;
    }
    return 0;
}

// Part A
int digitSum(int number)
{
    if (number / 100 == 0) {
        return (number / 10) + (number % 10);
    }
    int sum;
    sum = (number % 10) + digitSum(number / 10);
    return sum;
}

// Part B
bool isBalanced(const std::string& text)
{
    std::stack<char> s;
    for (int i = 0; i < text.length(); i++) {
        char c = text.at(i);
        switch (c) {
            case '(':
                s.push(c);
                break;
            case ')':
                if (s.top() != '(') {
                    return false;
                }
                s.pop();
                break;
            case '[':
                s.push(c);
                break;
            case ']':
                if (s.top() != '[') {
                    return false;
                }
                s.pop();
                break;
            case '{':
                s.push(c);
                break;
            case '}':
                if (s.top() != '{') {
                    return false;
                }
                s.pop();
                break;
            default:
                break;
        }

    }
    return true;
}
