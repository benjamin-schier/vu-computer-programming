# XB_40011 — Mock Midterm Exam #2
**Total time: 2 hours 15 minutes (135 minutes) — Closed book, no internet, no autocomplete**

Same rules as last time: no autocomplete, no internet, no notes. Time yourself per section.

**Note:** this exam deliberately avoids anything marked "Optional" in the zyBook (e.g. short-circuit evaluation, break/continue, string/character access operations, default parameters, function overloading, preprocessor/separate files). The theory quiz is harder than mock exam #1 — expect more code tracing and fewer one-liners.

| Section | Suggested time |
|---|---|
| Theory Quiz | 25 min |
| Assignment 1 — Shipping Cost Calculator | 20 min |
| Assignment 2 — Matrix Row & Column Sums | 40 min |
| Assignment 3 — Recursive Search & Palindrome Check | 45 min |
| Buffer / review | 5 min |

Remember the style guidelines: meaningful camelCase names, `const` by default, `at()` instead of `[]`, no `using namespace std`, opening/closing braces on their own line, no global variables, functions that do one thing, verb-phrase function names, noun-phrase variable names.

---

## Part 1 — Theory Quiz (25 minutes)

**Q1.** What is the time complexity (in Big-O notation) of the following code, as a function of `n` (the size of `v`)? Explain in one sentence why.
```cpp
for (int i = 0; i < v.size(); i = i + 1)
{
    for (int j = 0; j < v.size(); j = j + 1)
    {
        std::cout << v.at(i) + v.at(j) << " ";
    }
}
```

**Q2.** Trace the exact output of this nested loop (include spaces and line breaks as printed):
```cpp
for (int row = 1; row <= 3; row = row + 1)
{
    for (int col = 1; col <= row; col = col + 1)
    {
        std::cout << col << " ";
    }
    std::cout << std::endl;
}
```

**Q3.** What is the output of the following, and why? (Pay close attention to every `case`.)
```cpp
int x = 2;
switch (x)
{
    case 1:
        std::cout << "one ";
    case 2:
        std::cout << "two ";
    case 3:
        std::cout << "three ";
        break;
    default:
        std::cout << "other ";
}
```

**Q4.** For each of the following, state whether it is a **valid** C++ identifier. If not, say why.
- `_tempValue`
- `total#Score`
- `double`
- `numberOfCars2`

**Q5.** Given:
```cpp
void printFirst(const std::vector<int>& numbers)
{
    numbers.at(0) = 42;
    std::cout << numbers.at(0) << std::endl;
}
```
Will this code compile? Explain why or why not.

**Q6.** Given the following 2D vector:
```cpp
std::vector<std::vector<int>> grid = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};
```
What value does `grid.at(2).at(0)` refer to?

**Q7.** What is the output of the following, and why? (Think carefully about which conversions happen, and when.)
```cpp
int a = 5;
double b = 2.0;
int c = a / b;
std::cout << c << std::endl;
```

**Q8.** Consider this recursive function:
```cpp
int mystery(int n)
{
    if (n <= 1)
    {
        return 1;
    }
    return n * mystery(n - 1);
}
```
What is `mystery(4)`? Show the sequence of recursive calls and return values (briefly).

**Q9.** A `std::stack<int>` starts empty. The following operations happen in this exact order:
```
push(3); push(7); push(1); pop(); push(9); pop(); pop();
```
What is in the stack at the end (from bottom to top), and what is the value returned by the *last* `pop()`?

**Q10.** A `std::vector<int> v` currently has 5 elements. You call `v.resize(2)` and then `v.resize(5)` again. Does the vector contain the original 5 values afterward? Explain briefly what happens to the "new" elements created by the second `resize`.

**Q11.** Given:
```cpp
enum Season { WINTER, SPRING, SUMMER, FALL };
Season current = SUMMER;
```
What integer value does `SUMMER` have by default, and why?

**Q12.** What is the result of the following comparison, and why?
```cpp
std::string a = "apple";
std::string b = "banana";
std::cout << (a < b) << std::endl;
```

**Q13.** Given this function:
```cpp
void doubleAll(std::vector<int>& numbers)
{
    for (int i = 0; i < numbers.size(); i = i + 1)
    {
        numbers.at(i) = numbers.at(i) * 2;
    }
}
```
and this call:
```cpp
std::vector<int> data = {1, 2, 3};
doubleAll(data);
```
What does `data` contain after the call? Would the answer change if the parameter were `std::vector<int> numbers` (no `&`)? Explain.

---

## Part 2 — Assignment 1: Shipping Cost Calculator (20 minutes)

Write a complete C++ program (`assignment1.cpp` — starter file provided) that repeatedly asks the user for a **package size category** and computes the total shipping cost, using a **switch statement**.

**Categories and prices:**
| Category (int) | Meaning | Price |
|---|---|---|
| 1 | small | €4.50 |
| 2 | medium | €7.00 |
| 3 | large | €11.00 |
| 4 | oversized | €18.00 |

**Requirements:**
1. Repeatedly prompt: `"Enter package category (1-4, 0 to stop): "`.
2. The loop stops when the user enters `0`.
3. Use a `switch` statement (not if-else) to determine the price for each valid category (1–4).
4. If the user enters a number outside 0–4, print `"Invalid category, skipped."` and continue asking (don't count it as a package, don't crash).
5. For every valid package, print the category name and price, e.g.: `Category 3 -> large: 11.00 euro`
6. Keep a running **total cost** and **package count**. After the loop ends, print both, e.g.: `Packages: 3, total cost: 22.50 euro`
7. Use `const` for the fixed prices.

---

## Part 3 — Assignment 2: Matrix Row & Column Sums (40 minutes)

Write a complete C++ program (`assignment2.cpp` — starter file provided) that reads a small matrix of integers into a `std::vector<std::vector<int>>` and reports row/column sums using separate functions.

**Requirements:**
1. Ask the user for the number of rows and columns: `"Rows: "`, `"Columns: "`.
2. Read `rows * columns` integers from the user, filling the matrix row by row.
3. Implement and use the following functions:
   - a function that **computes the sum of a given row**, given the matrix and a row index
   - a function that **computes the sum of a given column**, given the matrix and a column index
   - a function that **computes the sum of the entire matrix** (all elements)
4. In `main`, print:
   - the sum of every row, one per line, e.g. `Row 0 sum: 12`
   - the sum of every column, one per line, e.g. `Column 0 sum: 9`
   - the total sum of the whole matrix, e.g. `Total sum: 45`
5. Pass the matrix to your functions by `const` reference (they must not copy or modify it).
6. Use `at()` for all element access — never `[]`.
7. Do not hardcode the number of rows or columns anywhere inside your functions — they must work for any matrix size.

---

## Part 4 — Assignment 3: Recursive Search & Palindrome Check (45 minutes)

This assignment has two independent parts. Put both in `assignment3.cpp` (starter file provided).

### Part A — Recursive binary search (≈20 min)

Write a **recursive** function
```cpp
int recursiveBinarySearch(const std::vector<int>& sortedNumbers, int low, int high, int target);
```
that returns the index of `target` in `sortedNumbers` (which is guaranteed to already be sorted ascending), or `-1` if `target` is not present. Use the standard binary search idea: check the middle element, and recurse into only the half that could contain `target`.

- You must use recursion (no loops in this function).
- `low` and `high` are the inclusive bounds of the range currently being searched.
- Think carefully about the base case(s): what happens when the range is empty, and what happens when you find the target?
- In `main`, create a sorted vector of at least 6 integers, ask the user for a target value, and print either the index where it was found or a message saying it wasn't found. Call your function with `low = 0` and `high = sortedNumbers.size() - 1`.

### Part B — Palindrome check using a stack (≈25 min)

Write a function
```cpp
bool isPalindrome(const std::vector<int>& numbers);
```
that uses a `std::stack<int>` to check whether the vector reads the same forwards and backwards. For example, `{1, 2, 3, 2, 1}` is a palindrome; `{1, 2, 3, 4}` is not.

- You must use a `std::stack<int>` as part of your approach (think about how pushing all elements and then popping them relates to reversing their order).
- Do not use any string/character functions — this is about a vector of integers.
- In `main`, ask the user how many integers to read, read them into a vector, and print whether that vector is a palindrome.

---

### End of exam
Compare your work against `answer_key_2.md` once done or time's up.
