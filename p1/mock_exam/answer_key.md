# Answer Key — Mock Midterm Exam

Don't peek before you're done (or out of time). Self-grade honestly.

---

## Part 1 — Theory Quiz

**A1.**
- *Syntax error*: code violates C++ grammar, won't compile — e.g. missing semicolon.
- *Runtime error*: code compiles but crashes/misbehaves while running — e.g. accessing `vec.at(10)` on a 3-element vector.
- *Logic error*: code compiles and runs fine but produces the wrong result — e.g. using `+` instead of `*` to compute an area.

**A2.** O(n) means the running time grows linearly with the size of the input `n`. Example: iterating through all elements of a `std::vector` once (e.g. to compute a sum) is O(n).

**A3.** Invalid. Identifiers cannot start with a digit.

**A4.** Output: `3` (not `3.5`). `a / b` is **integer division** (both operands are `int`), so it evaluates to `3` *before* being converted to `double` and stored in `c`.

**A5.** `const double taxRate = 0.21;`

**A6.** `2` (17 divided by 5 is 3 remainder 2).

**A7.** Output: `B`. The conditions are checked in order top to bottom; `score >= 60` is true for `score = 55`... 

Wait — check carefully: `score = 55`. `score >= 90`? No. `score >= 60`? No (55 < 60). `score >= 55`? Yes → prints `C`. So the correct output is **`C`**, not `B`. This illustrates why order of evaluation matters in chained if-else branches — the first true branch wins, and here the boundaries were spaced so only the third condition matches.

**A8.** With `&&`, if the left operand is `false`, C++ does not evaluate the right operand at all (the whole expression is already `false`). In `i < v.size() && v.at(i) == 0`, this matters because if `i` is out of bounds, checking `i < v.size()` first prevents `v.at(i)` from ever being called with an invalid index — avoiding a runtime error.

**A9.** Output: `1 3 5` — the loop skips printing for even `i` because of `continue`, so only odd values 1, 3, 5 get printed (2 and 4 are skipped).

**A10.** Pass-by-value copies the argument into the function's parameter — changes inside the function don't affect the original. Pass-by-reference gives the function direct access to the original variable — changes do affect it, and no copy is made. For a `std::vector`, pass-by-reference (typically `const std::vector<...>&` when not modifying it) avoids the cost of copying potentially large amounts of data.

**A11.** A base case is the condition under which a recursive function stops calling itself and returns a result directly, instead of recursing further. Without one, the function calls itself forever (until it typically crashes with a **stack overflow**).

**A12.** LIFO (Last In, First Out). Core operations: `push` (add to top) and `pop` (remove from top).

---

## Part 2 — Assignment 1 Reference Solution

```cpp
#include <iostream>

int main()
{
    const double childPrice = 6.00;
    const double teenPrice = 9.00;
    const double adultPrice = 12.00;
    const double seniorPrice = 8.00;

    const int teenMinAge = 12;
    const int adultMinAge = 18;
    const int seniorMinAge = 65;

    int ticketCount = 0;
    double totalRevenue = 0.0;

    int age = 0;
    std::cout << "Enter age (-1 to stop): ";
    std::cin >> age;

    while (age != -1)
    {
        double price = 0.0;
        std::string category;

        if (age < teenMinAge)
        {
            price = childPrice;
            category = "child";
        }
        else if (age < adultMinAge)
        {
            price = teenPrice;
            category = "teen";
        }
        else if (age < seniorMinAge)
        {
            price = adultPrice;
            category = "adult";
        }
        else
        {
            price = seniorPrice;
            category = "senior";
        }

        std::cout << "Age " << age << " -> " << category << " ticket: " << price << " euro" << std::endl;

        totalRevenue = totalRevenue + price;
        ticketCount = ticketCount + 1;

        std::cout << "Enter age (-1 to stop): ";
        std::cin >> age;
    }

    std::cout << "Tickets sold: " << ticketCount << ", total revenue: " << totalRevenue << " euro" << std::endl;

    return 0;
}
```

**Self-check points:** sentinel loop correctly excludes `-1` from processing; branch boundaries handle edges (11 vs 12, 17 vs 18, 64 vs 65) correctly; prices declared `const`; running totals updated correctly; no `using namespace std`.

---

## Part 3 — Assignment 2 Reference Solution

```cpp
#include <iostream>
#include <vector>

double calculateAverage(const std::vector<double>& scores)
{
    double sum = 0.0;
    for (int i = 0; i < scores.size(); i = i + 1)
    {
        sum = sum + scores.at(i);
    }
    return sum / scores.size();
}

double findMaximum(const std::vector<double>& scores)
{
    double maximum = scores.at(0);
    for (int i = 1; i < scores.size(); i = i + 1)
    {
        if (scores.at(i) > maximum)
        {
            maximum = scores.at(i);
        }
    }
    return maximum;
}

int countPassing(const std::vector<double>& scores, double passingGrade)
{
    int count = 0;
    for (int i = 0; i < scores.size(); i = i + 1)
    {
        if (scores.at(i) >= passingGrade)
        {
            count = count + 1;
        }
    }
    return count;
}

int main()
{
    const double passingGrade = 5.5;

    int n = 0;
    std::cout << "How many scores? ";
    std::cin >> n;

    std::vector<double> scores(n);
    for (int i = 0; i < n; i = i + 1)
    {
        std::cout << "Enter score " << (i + 1) << ": ";
        std::cin >> scores.at(i);
    }

    std::cout << "Average: " << calculateAverage(scores) << std::endl;
    std::cout << "Maximum: " << findMaximum(scores) << std::endl;
    std::cout << "Passing (>=5.5): " << countPassing(scores, passingGrade) << " out of " << n << std::endl;

    return 0;
}
```

**Self-check points:** vectors passed by `const&` (no unnecessary copying, no accidental modification); `at()` used throughout, never `[]`; each function does exactly one thing; `n` not hardcoded anywhere inside the functions.

---

## Part 4 — Assignment 3 Reference Solution

```cpp
#include <iostream>
#include <stack>
#include <string>

int digitSum(int number);
bool isBalanced(const std::string& text);

int main()
{
    int number = 0;
    std::cout << "Enter a non-negative integer: ";
    std::cin >> number;
    std::cout << "Digit sum: " << digitSum(number) << std::endl;

    std::cin.ignore();
    std::string text;
    std::cout << "Enter a line of text: ";
    std::getline(std::cin, text);
    if (isBalanced(text))
    {
        std::cout << "Balanced" << std::endl;
    }
    else
    {
        std::cout << "Not balanced" << std::endl;
    }

    return 0;
}

int digitSum(int number)
{
    if (number < 10)
    {
        return number;
    }
    return number % 10 + digitSum(number / 10);
}

bool isBalanced(const std::string& text)
{
    std::stack<char> brackets;

    for (int i = 0; i < text.size(); i = i + 1)
    {
        char currentChar = text.at(i);

        if (currentChar == '(' || currentChar == '[' || currentChar == '{')
        {
            brackets.push(currentChar);
        }
        else if (currentChar == ')' || currentChar == ']' || currentChar == '}')
        {
            if (brackets.empty())
            {
                return false;
            }

            char top = brackets.top();
            brackets.pop();

            if ((currentChar == ')' && top != '(') ||
                (currentChar == ']' && top != '[') ||
                (currentChar == '}' && top != '{'))
            {
                return false;
            }
        }
    }

    return brackets.empty();
}
```

**Self-check points (Part A):** base case handles single-digit numbers (including `0`); recursive case correctly splits off the last digit with `% 10` and recurses on `/ 10`; no loops used.

**Self-check points (Part B):** stack used correctly (push on open, pop-and-compare on close); mismatched types detected (`)` closing a `[`); unclosed brackets detected (stack not empty at the end); empty-stack-on-close case handled (extra closing bracket with nothing to match).

---

## Rough self-grading guide
- Theory quiz: 1 point per question (12 pts)
- Each assignment: roughly 40/30/30 split between "compiles and handles the basic case", "handles edge cases correctly", "follows style guidelines"

If you finished all three assignments within 135 minutes *and* they compile and behave correctly on the examples given, you're in solid shape for Monday. If you ran significantly over time, focus your remaining practice on writing loops/functions faster without hesitating over syntax — that's usually the bottleneck, not understanding the concepts.
