# Answer Key — Mock Midterm Exam #2

Don't peek before you're done (or out of time).

---

## Part 1 — Theory Quiz

**A1.** O(n²). For every element `i` (n iterations), the inner loop runs through all `n` elements again — n work done n times, giving n × n = n² total operations.

**A2.**
```
1
1 2
1 2 3
```
Row 1 prints just `1`, row 2 prints `1 2`, row 3 prints `1 2 3` — each followed by a newline from `std::endl`.

**A3.** Output: `two three `. Since `x == 2`, execution jumps to `case 2:`. There is **no `break` after `case 2`**, so execution "falls through" into `case 3:` as well, printing `"two "` then `"three "`, and only then hits the `break`. `case 1` is never reached at all.

**A4.**
- `_tempValue` — valid (identifiers may start with an underscore).
- `total#Score` — invalid (`#` is not allowed in identifiers).
- `double` — invalid (it's a reserved keyword).
- `numberOfCars2` — valid (digits are allowed anywhere except as the first character).

**A5.** This does **not** compile. `numbers` is declared as `const std::vector<int>&`, meaning the function promises not to modify the vector it refers to. Attempting `numbers.at(0) = 42;` tries to modify an element through a `const` reference, which the compiler rejects.

**A6.** `7`. `grid.at(2)` is the third row, `{7, 8, 9}`, and `.at(0)` of that row is `7`.

**A7.** Output: `2`. Because `b` is a `double`, the expression `a / b` triggers **implicit conversion of `a` to double** before the division happens — so it's `5.0 / 2.0 = 2.5`, true floating-point division, not integer division. However, that `2.5` is then assigned into `int c`, which **truncates** the decimal part, giving `2`. (This is a classic case where two different conversions happen in the same line, in opposite directions.)

**A8.** `mystery(4) = 4 * mystery(3) = 4 * (3 * mystery(2)) = 4 * 3 * (2 * mystery(1)) = 4 * 3 * 2 * 1 = 24`. (This function computes a factorial.)

**A9.** Trace step by step:
```
push(3)  -> [3]
push(7)  -> [3, 7]
push(1)  -> [3, 7, 1]
pop()    -> [3, 7]        (removes 1)
push(9)  -> [3, 7, 9]
pop()    -> [3, 7]        (removes 9)
pop()    -> [3]           (removes 7)
```
Final stack (bottom to top): `[3]`. The value returned by the last `pop()` is `7`.

**A10.** No — the original values are **not** preserved after shrinking and growing again. `resize(2)` discards elements beyond index 1 (elements at index 2, 3, 4 are gone). `resize(5)` then grows the vector back to 5 elements, but the 3 newly added elements are **default-initialized** (`0` for `int`), not restored to their old values — that data is permanently lost once the vector was shrunk.

**A11.** `2`. Enum values default to consecutive integers starting at `0` unless explicitly assigned otherwise: `WINTER = 0`, `SPRING = 1`, `SUMMER = 2`, `FALL = 3`.

**A12.** Output: `1` (i.e. `true`). `std::string` comparison with `<` is **lexicographic** (dictionary order, comparing characters left to right by their character codes): `'a' < 'b'`, so `"apple" < "banana"` is `true`. `std::cout` prints `bool` values as `1`/`0` by default.

**A13.** `data` contains `{2, 4, 6}` after the call — because `numbers` is a reference (`std::vector<int>&`), `doubleAll` operates directly on the original vector, and the doubling is visible to the caller. If the parameter were `std::vector<int> numbers` (pass by value), the function would receive and modify only a **copy**; `data` in `main` would remain `{1, 2, 3}`, completely unchanged.

---

## Part 2 — Assignment 1 Reference Solution

```cpp
#include <iostream>

int main()
{
    const double smallPrice = 4.50;
    const double mediumPrice = 7.00;
    const double largePrice = 11.00;
    const double oversizedPrice = 18.00;

    int packageCount = 0;
    double totalCost = 0.0;

    int category = 0;
    std::cout << "Enter package category (1-4, 0 to stop): ";
    std::cin >> category;

    while (category != 0)
    {
        double price = 0.0;
        std::string name;
        bool validCategory = true;

        switch (category)
        {
            case 1:
                price = smallPrice;
                name = "small";
                break;
            case 2:
                price = mediumPrice;
                name = "medium";
                break;
            case 3:
                price = largePrice;
                name = "large";
                break;
            case 4:
                price = oversizedPrice;
                name = "oversized";
                break;
            default:
                validCategory = false;
                break;
        }

        if (validCategory)
        {
            std::cout << "Category " << category << " -> " << name << ": " << price << " euro" << std::endl;
            totalCost = totalCost + price;
            packageCount = packageCount + 1;
        }
        else
        {
            std::cout << "Invalid category, skipped." << std::endl;
        }

        std::cout << "Enter package category (1-4, 0 to stop): ";
        std::cin >> category;
    }

    std::cout << "Packages: " << packageCount << ", total cost: " << totalCost << " euro" << std::endl;

    return 0;
}
```

**Self-check points:** `switch` used instead of if-else chain; every `case` has a `break` (no accidental fallthrough); invalid categories handled gracefully via `default`; totals only updated for valid packages; prices declared `const`.

---

## Part 3 — Assignment 2 Reference Solution

```cpp
#include <iostream>
#include <vector>

int calculateRowSum(const std::vector<std::vector<int>>& matrix, int row)
{
    int sum = 0;
    for (int col = 0; col < matrix.at(row).size(); col = col + 1)
    {
        sum = sum + matrix.at(row).at(col);
    }
    return sum;
}

int calculateColumnSum(const std::vector<std::vector<int>>& matrix, int column)
{
    int sum = 0;
    for (int row = 0; row < matrix.size(); row = row + 1)
    {
        sum = sum + matrix.at(row).at(column);
    }
    return sum;
}

int calculateTotalSum(const std::vector<std::vector<int>>& matrix)
{
    int sum = 0;
    for (int row = 0; row < matrix.size(); row = row + 1)
    {
        sum = sum + calculateRowSum(matrix, row);
    }
    return sum;
}

int main()
{
    int rows = 0;
    int columns = 0;
    std::cout << "Rows: ";
    std::cin >> rows;
    std::cout << "Columns: ";
    std::cin >> columns;

    std::vector<std::vector<int>> matrix(rows, std::vector<int>(columns));

    for (int row = 0; row < rows; row = row + 1)
    {
        for (int col = 0; col < columns; col = col + 1)
        {
            std::cin >> matrix.at(row).at(col);
        }
    }

    for (int row = 0; row < rows; row = row + 1)
    {
        std::cout << "Row " << row << " sum: " << calculateRowSum(matrix, row) << std::endl;
    }

    for (int col = 0; col < columns; col = col + 1)
    {
        std::cout << "Column " << col << " sum: " << calculateColumnSum(matrix, col) << std::endl;
    }

    std::cout << "Total sum: " << calculateTotalSum(matrix) << std::endl;

    return 0;
}
```

**Self-check points:** matrix passed by `const&` everywhere; `at()` used for all element access, including nested `.at(row).at(col)`; no function hardcodes matrix dimensions — they all derive bounds from `.size()`; `calculateTotalSum` reuses `calculateRowSum` rather than duplicating the summing logic (each function does one thing).

---

## Part 4 — Assignment 3 Reference Solution

```cpp
#include <iostream>
#include <stack>
#include <vector>

int recursiveBinarySearch(const std::vector<int>& sortedNumbers, int low, int high, int target);
bool isPalindrome(const std::vector<int>& numbers);

int main()
{
    std::vector<int> sortedNumbers = {2, 5, 8, 12, 16, 23, 38, 45};

    int target = 0;
    std::cout << "Enter a target value to search for: ";
    std::cin >> target;

    int result = recursiveBinarySearch(sortedNumbers, 0, sortedNumbers.size() - 1, target);
    if (result != -1)
    {
        std::cout << "Found at index " << result << std::endl;
    }
    else
    {
        std::cout << "Not found" << std::endl;
    }

    int count = 0;
    std::cout << "How many integers? ";
    std::cin >> count;

    std::vector<int> numbers;
    for (int i = 0; i < count; i = i + 1)
    {
        int value = 0;
        std::cin >> value;
        numbers.push_back(value);
    }

    if (isPalindrome(numbers))
    {
        std::cout << "Palindrome" << std::endl;
    }
    else
    {
        std::cout << "Not a palindrome" << std::endl;
    }

    return 0;
}

int recursiveBinarySearch(const std::vector<int>& sortedNumbers, int low, int high, int target)
{
    if (low > high)
    {
        return -1;
    }

    int middle = (low + high) / 2;

    if (sortedNumbers.at(middle) == target)
    {
        return middle;
    }
    else if (sortedNumbers.at(middle) < target)
    {
        return recursiveBinarySearch(sortedNumbers, middle + 1, high, target);
    }
    else
    {
        return recursiveBinarySearch(sortedNumbers, low, middle - 1, target);
    }
}

bool isPalindrome(const std::vector<int>& numbers)
{
    std::stack<int> reversedNumbers;
    for (int i = 0; i < numbers.size(); i = i + 1)
    {
        reversedNumbers.push(numbers.at(i));
    }

    for (int i = 0; i < numbers.size(); i = i + 1)
    {
        if (numbers.at(i) != reversedNumbers.top())
        {
            return false;
        }
        reversedNumbers.pop();
    }

    return true;
}
```

**Self-check points (Part A):** base case `low > high` correctly signals "not found" (empty range); the found-case returns immediately; recursion narrows to exactly one half of the range each call, never both; no loops used.

**Self-check points (Part B):** all elements pushed onto the stack first (this naturally reverses their order); comparing the vector front-to-back against the stack top-to-bottom is equivalent to comparing forwards vs. backwards; function returns `false` as soon as a mismatch is found rather than checking everything first; `std::stack` actually used as the mechanism (not just a vector iterated backwards "by hand", even though that would also work).

---

## Rough self-grading guide
- Theory quiz: 1 point per question (13 pts) — this set leaned harder on tracing than mock exam #1, so don't be discouraged by a lower raw score; look at *which kind* of mistake you made (conceptual misunderstanding vs. a careless trace)
- Each assignment: roughly 40/30/30 split between "compiles and handles the basic case", "handles edge cases correctly", "follows style guidelines"

If Q7, Q9, and Q13 (the trickiest tracing questions) gave you trouble, that's a sign to practice tracing code by hand — line by line, writing down variable values as you go — rather than reading code and guessing the output. That's exactly the skill CodeGrade's theory quiz tests.
