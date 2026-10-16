# XB_40011 — Mock Final Exam #1
**Total time: 2 hours 15 minutes (135 minutes) — covers all six modules**

Same rules as before: laptop offline, VS Code with autocompletion disabled, no internet.

**New this time:** you may use the **cheat sheet** (`Cheat_Sheet_Computer_Programming_2024.pdf`) during the three programming assignments. For the theory quiz, work *without* it, because I don't know whether the real quiz allows it. Treat it as closed-book to be safe.

Be careful with the cheat sheet. It is student-made and contains mistakes, and several of its examples break the course style guidelines (`using namespace std`, `[]` on vectors). Copying blindly can cost you points.

| Section | Suggested time |
|---|---|
| Theory Quiz (14 questions, no cheat sheet) | 25 min |
| Assignment 1 — Inventory Log Parser (streams, maps, exceptions) | 20 min |
| Assignment 2 — IntList (dynamic memory, Rule of Three) | 45 min |
| Assignment 3 — BST class template (pointers, recursion, templates) | 40 min |
| Buffer / review | 5 min |

Style guidelines still apply: meaningful camelCase names, `const` by default, `at()` instead of `[]` on vectors, no `using namespace std`, braces on their own lines, no global variables, one job per function. (Raw `new[]` arrays have no `at()`, so indexing those with `[]` is fine.)

**Tip:** do the assignments in the order you feel most confident. Assignment 2 and 3 each have 4 phases. Get phase 1 green before moving on, as in the real exam.

---

## Part 1 — Theory Quiz (25 minutes, no cheat sheet)

**Q1.** What does this program print?
```cpp
int a = 5;
int b = 10;
int* p = &a;
int* q = &b;
*p = *q;
q = p;
*q = 99;
std::cout << a << " " << b << std::endl;
```

**Q2.** Name two different memory problems in this code, and say how to fix each.
```cpp
int* createCounters()
{
    int* counters = new int[3];
    counters[0] = 0;
    return counters;
}

int main()
{
    int* values = createCounters();
    values = new int[10];
    delete values;
    return 0;
}
```

**Q3.** This class has a destructor but crashes (or corrupts memory) when `test` runs. Explain exactly why, and which member functions are missing.
```cpp
class Buffer
{
public:
    Buffer(int size) : data(new int[size]) {}
    ~Buffer() { delete[] data; }
private:
    int* data;
};

void test()
{
    Buffer a(3);
    Buffer b = a;
}
```

**Q4.** For each numbered statement, say whether the **copy constructor**, the **copy assignment operator**, or **neither** is called.
```cpp
void inspect(Buffer b);

Buffer a(3);
Buffer b = a;     // (1)
Buffer c(2);
c = a;            // (2)
inspect(a);       // (3)
Buffer d(a);      // (4)
```

**Q5.** What is the exact output? (`std::runtime_error` and `std::logic_error` are unrelated classes; both derive from `std::exception`.)
```cpp
try
{
    std::cout << "A";
    throw std::runtime_error("x");
    std::cout << "B";
}
catch (const std::logic_error&)
{
    std::cout << "C";
}
catch (const std::runtime_error&)
{
    std::cout << "D";
}
catch (...)
{
    std::cout << "E";
}
std::cout << "F" << std::endl;
```

**Q6.** Consider:
```cpp
std::istringstream in("12 abc 7");
int x = -1;
int y = -1;
int z = -1;
in >> x;
in >> y;
in >> z;
```
(a) What is `x`? (b) What does `in.fail()` return after the second extraction? (c) What happens to `z`, and why? (d) What must you do before the stream can be used for reading again?

**Q7.** What is printed?
```cpp
std::map<std::string, int> m;
m.emplace("a", 1);
m.emplace("a", 2);
m.emplace("b", 5);
m.at("a") = m.at("a") + 10;
std::cout << m.at("a") << " " << m.size() << std::endl;
```

**Q8.** What is the time complexity of this function in terms of `n`? Why is it so slow, and in one sentence, how could you make it fast?
```cpp
int fib(int n)
{
    if (n <= 1)
    {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}
```

**Q9.** What is the exact output of `show(3)`?
```cpp
void show(int n)
{
    if (n == 0)
    {
        return;
    }
    std::cout << n << " ";
    show(n - 1);
    std::cout << n << " ";
}
```

**Q10.** Keys are inserted into an empty binary search tree in this order: `40, 20, 60, 10, 30, 50, 5`. Give (a) the in-order traversal, (b) the pre-order traversal, (c) the post-order traversal, (d) the height of the tree (root only = height 1).

**Q11.** This function should remove the first node of a singly linked list. What is wrong, and what is the correct version?
```cpp
void removeFirst(Node*& head)
{
    head = head->next;
    delete head;
}
```

**Q12.** Will this compile? If not, explain why and give two ways to fix it.
```cpp
template <typename T>
T larger(T a, T b)
{
    return a > b ? a : b;
}

int main()
{
    std::cout << larger(3, 4.5) << std::endl;
    return 0;
}
```

**Q13.** A directed graph has the edges `A→B`, `B→C`, `C→A`, `C→D`. Answer yes/no with a one-line reason each: (a) weakly connected? (b) strongly connected? (c) cyclic?

**Q14.** List at least four violations of the course style guidelines in this code:
```cpp
#include <iostream>
#include <vector>
using namespace std;

int Total = 0;

int AddAll(vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        Total += v[i];
    }
    return Total;
}
```

---

## Part 2 — Assignment 1: Inventory Log Parser (20 minutes)

Use `final_assignment1.cpp`. Read an inventory log from `std::cin` until end of input and print a summary. **Do not print any prompts.** The autotests compare your output exactly.

**Input format:** one entry per line: `<item> <quantity>`, where `<item>` is a single word and `<quantity>` is a non-negative integer. Nothing may follow the quantity.

**Rules:**
1. Blank lines (empty, or only spaces) are ignored. They are not errors.
2. A line is **invalid** if the quantity is missing, not an integer, negative, or if anything follows it (`kiwi 3 extra`, `a 4.5` and `b 5abc` are all invalid).
3. Write a function that handles **one line** and **throws `std::invalid_argument`** (with the offending line as message) when the line is invalid. `main` must catch it, print `Error: invalid line "<line>"` immediately, count the error, and continue with the next line.
4. Valid lines add their quantity to the item's running total (the same item can appear several times).
5. At the end print the items in alphabetical order, then the error count, exactly like this:

```
Inventory:
apple: 7
pear: 2
Errors: 3
```

A sample is provided: run `./a1 < final_a1_input.txt | diff - final_a1_expected.txt`. The sample does not cover all edge cases, so invent your own: whitespace-only lines, trailing spaces, `4.5`, a huge number like `99999999999`.

Use `std::istringstream` for parsing and a `std::map<std::string, int>` for the totals.

---

## Part 3 — Assignment 2: IntList (45 minutes)

Use `final_assignment2.cpp`. Implement a class `IntList`, a growable list of `int` backed by a **raw dynamic array** (`new[]` / `delete[]`). You may not use `std::vector` or any other container inside it. The signatures and the full test suite are in the file. The phases:

1. **Phase 1:** constructor, destructor, `append` (the capacity doubles when full), `at`, `getSize`, `getCapacity`
2. **Phase 2:** `removeLast`, `contains`
3. **Phase 3:** copy constructor and copy assignment operator (deep copies, safe for self-assignment)
4. **Phase 4:** `operator+` (concatenation into a new list) and `operator==`

Requirements:
- No memory leaks, double frees or out-of-bounds access. On Linux/macOS compile with `-fsanitize=address,undefined` as shown at the top of the file. On Windows/MinGW that flag is often unavailable, so re-read your destructor and copy code carefully instead.
- Methods that don't modify the list must be `const`.
- Errors: `at` and `removeLast` throw `std::out_of_range("IntList")` as described in the file.

---

## Part 4 — Assignment 3: BST class template (40 minutes)

Use `final_assignment3.cpp`. Implement a **binary search tree class template** `BST<Key>` that stores keys only (no values). `Key` supports `==` and `<`. Duplicate keys are ignored. The signatures and tests are in the file. The phases:

1. **Phase 1:** constructor, destructor (no leaks!), `insert`, `contains`
2. **Phase 2:** `getSize`, `getHeight` (empty tree: 0, root only: 1)
3. **Phase 3:** `getMinimum`, `getMaximum` (throw `std::out_of_range("BST")` on an empty tree), `toSortedVector` (in-order traversal)
4. **Phase 4:** `countLessThan(limit)`: how many keys are strictly smaller than `limit`. Use the BST property so you don't visit subtrees you don't need.

Hints:
- Recursion needs helper functions that take a `Node*` (or `Node*&` for insert). Put them in the `private` section.
- Implement everything inside the class body. Defining template members outside the class costs you a lot of syntax hassle.
- Your tests use `int` and `std::string` keys, so don't assume the key is a number.

---

### End of exam
Compare with `final_answer_key.md` once you are done or time is up. Note which phases you completed, how long each assignment took, and whether the time went on syntax, on logic, or on looking things up in the cheat sheet.
