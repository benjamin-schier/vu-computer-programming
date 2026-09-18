# XB_40011 — Mock Midterm Exam
**Total time: 2 hours 15 minutes (135 minutes) — Closed book, no internet, no autocomplete**

Simulate real exam conditions as closely as possible:
- No IDE autocompletion (you already disabled this — good)
- No internet, no notes, no zyBook
- Use a pen and scrap paper if you want to sketch logic first
- Time yourself per section using the suggested budget below — stop and move on when time is up, just like you'd have to in CodeGrade

| Section | Suggested time |
|---|---|
| Theory Quiz | 20 min |
| Assignment 1 — Ticket Price Calculator | 25 min |
| Assignment 2 — Exam Score Statistics | 40 min |
| Assignment 3 — Digit Sum & Balanced Brackets | 45 min |
| Buffer / review | 5 min |

Remember: all code must follow the **course style guidelines** — meaningful camelCase names, `const` by default, `at()` instead of `[]`, no `using namespace std`, opening/closing braces on their own line, no global variables, functions that do one thing.

---

## Part 1 — Theory Quiz (20 minutes)

Answer briefly. No need for full essays — this mirrors a short auto-graded quiz.

**Q1.** What is the difference between a *syntax error*, a *runtime error*, and a *logic error*? Give a one-sentence example of each.

**Q2.** What does it mean for an algorithm to run in **O(n)** time? Give one example of an O(n) operation on a `std::vector`.

**Q3.** Is the following variable name valid in C++? If not, explain why: `2ndAttempt`

**Q4.** What is the output of the following code, and why?
```cpp
int a = 7;
int b = 2;
double c = a / b;
std::cout << c << std::endl;
```

**Q5.** Rewrite the line below so `taxRate` cannot be accidentally modified later in the program:
```cpp
double taxRate = 0.21;
```

**Q6.** What is the output of the following?
```cpp
int x = 17;
std::cout << x % 5 << std::endl;
```

**Q7.** What is the output of the following code? Explain why in one sentence.
```cpp
int score = 55;
if (score >= 90) {
    std::cout << "A";
} else if (score >= 60) {
    std::cout << "B";
} else if (score >= 55) {
    std::cout << "C";
} else {
    std::cout << "F";
}
```

**Q8.** What does *short-circuit evaluation* mean for the `&&` operator? Why is the order of the two conditions below important?
```cpp
if (i < v.size() && v.at(i) == 0) { ... }
```

**Q9.** Trace the output of this loop:
```cpp
for (int i = 1; i <= 5; i = i + 1) {
    if (i % 2 == 0) {
        continue;
    }
    std::cout << i << " ";
}
```

**Q10.** What is the difference between passing a function parameter **by value** and **by reference**? Give one reason you would choose pass-by-reference for a `std::vector`.

**Q11.** What is a *base case* in a recursive function, and what happens if a recursive function is missing one?

**Q12.** A `std::stack` follows which access principle: FIFO or LIFO? Name the two core operations used to add and remove elements from a stack.

---

## Part 2 — Assignment 1: Ticket Price Calculator (25 minutes)

Write a complete C++ program (`assignment1.cpp` — starter file provided) that repeatedly asks the user to enter the **age** of a moviegoer and computes the total revenue from ticket sales.

**Pricing rules:**
| Age range | Price |
|---|---|
| 0–11 (child) | €6.00 |
| 12–17 (teen) | €9.00 |
| 18–64 (adult) | €12.00 |
| 65+ (senior) | €8.00 |

**Requirements:**
1. Repeatedly prompt: `"Enter age (-1 to stop): "`.
2. The loop stops when the user enters `-1`.
3. For every valid age entered, print the category and price, e.g.:
   `Age 34 -> adult ticket: 12.00 euro`
4. Keep a running **total revenue** and a running **ticket count**.
5. After the loop ends, print the total number of tickets sold and the total revenue, e.g.:
   `Tickets sold: 3, total revenue: 27.00 euro`
6. Use `const` for the fixed prices. Do not use magic numbers directly in comparisons — give the age boundaries meaningful names if you find that clearer.
7. Assume the user always enters a valid integer (no need to handle non-numeric input).

---

## Part 3 — Assignment 2: Exam Score Statistics (40 minutes)

Write a complete C++ program (`assignment2.cpp` — starter file provided) that reads a number of exam scores into a `std::vector<double>` and reports statistics about them, using **separate functions**.

**Requirements:**
1. Ask the user: `"How many scores? "` and read an integer `n`.
2. Read `n` scores (doubles) from the user into a `std::vector<double>`.
3. Implement and use the following functions (write your own signatures/parameter passing, following the style guidelines on when to use references and `const`):
   - a function that **calculates the average** of the scores in the vector
   - a function that **finds the maximum** score in the vector
   - a function that **counts how many scores are passing**, given a passing threshold of `5.5`
4. In `main`, call these functions and print:
   ```
   Average: <value>
   Maximum: <value>
   Passing (>=5.5): <count> out of <n>
   ```
5. Use `at()` for all vector element access — never `[]`.
6. None of your functions may use global variables or hardcode `n` — they must work for a vector of any size.

---

## Part 4 — Assignment 3: Digit Sum & Balanced Brackets (45 minutes)

This assignment has two independent parts. Put both in `assignment3.cpp` (starter file provided).

### Part A — Recursion (≈20 min)

Write a **recursive** function
```cpp
int digitSum(int number);
```
that returns the sum of the digits of a non-negative integer. For example, `digitSum(4325)` should return `4 + 3 + 2 + 5 = 14`.

- You must use recursion (no loops in this function).
- Think carefully about the base case.
- In `main`, ask the user for a non-negative integer and print the result of calling `digitSum`.

### Part B — Stack (≈25 min)

Write a function
```cpp
bool isBalanced(const std::string& text);
```
that uses a `std::stack<char>` to check whether all brackets in `text` are balanced and correctly nested. Consider three bracket types: `()`, `{}`, `[]`. Any other characters in `text` should simply be ignored.

Examples:
- `isBalanced("f(x) = [a + (b * c)]")` → `true`
- `isBalanced("(a + b]")` → `false` (mismatched types)
- `isBalanced("((a + b)")` → `false` (unclosed bracket)

In `main`, ask the user to enter a line of text and print whether it is balanced.

**Hint:** push opening brackets onto the stack; when you see a closing bracket, check whether it matches the top of the stack.

---

### End of exam
When you're done (or time runs out), compare your work against `answer_key.md`. Be honest with your timing — the point of this mock exam is to know now, not Monday morning, whether your pace is realistic for CodeGrade.
