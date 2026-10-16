# Answer Key — Mock Final Exam #1

Don't peek before you're done. All reference solutions below were compiled with `-Wall -Wextra -fsanitize=address,undefined` and pass the tests in the starter files.

---

## Part 1 — Theory Quiz

**A1.** `99 10`. `*p = *q` copies b's value (10) into `a`. `q = p` makes `q` point to `a`. `*q = 99` therefore changes `a`. `b` is never touched.

**A2.**
1. **Memory leak:** `values = new int[10];` overwrites the only pointer to the array returned by `createCounters()` before it is freed. Fix: `delete[] values;` before reassigning, or don't reallocate.
2. **Wrong delete:** memory from `new int[10]` must be released with `delete[] values;`, not `delete values;` (undefined behaviour).
3. (Bonus) `counters[1]` and `counters[2]` are uninitialised, so reading them gives garbage.

**A3.** `Buffer b = a;` uses the compiler-generated copy constructor, which only copies the pointer value (shallow copy). `a` and `b` then point to the same array. At the end of `test`, both destructors run `delete[] data` on the same memory, which is a double free. Missing: a **copy constructor** and a **copy assignment operator** that deep-copy the array (Rule of Three: destructor + copy constructor + copy assignment).

**A4.** (1) copy constructor (initialisation, not assignment, despite the `=`). (2) copy assignment operator (`c` already exists). (3) copy constructor (the by-value parameter is initialised from `a`). (4) copy constructor.

**A5.** `ADF`. `A` is printed, then the exception is thrown, so `B` is skipped. `runtime_error` is not a `logic_error`, so the first handler doesn't match. The second does, printing `D`. After the try/catch, execution continues with `F`.

**A6.** (a) `x == 12`. (b) `true`: `"abc"` can't be read as an int, so `failbit` is set. (c) `z` stays `-1`: once the stream is in a failed state, further extractions do nothing. (d) Call `in.clear()` to reset the error flags, and also get rid of the offending text (e.g. read it into a `std::string` or `ignore` it), otherwise it fails again on the same input.

**A7.** `11 2`. The second `emplace("a", 2)` does **not** overwrite the existing entry, so `a` is still 1. Then `1 + 10 = 11`. The map has two entries: `a` and `b`.

**A8.** Exponential, roughly O(2ⁿ) (strictly about 1.6ⁿ). Each call spawns two more calls, and the same subproblems (`fib(k)`) are recomputed over and over. Fix: compute iteratively with two variables, or memoise (store already computed values), giving O(n).

**A9.** `3 2 1 1 2 3 `. Each call prints `n` before recursing and `n` again after the recursive call returns, so the output is symmetric: down the call chain, then back up.

**A10.** Tree: root 40; 20 left, 60 right; 10 and 30 under 20; 50 left of 60; 5 left of 10.
(a) in-order: `5 10 20 30 40 50 60` (sorted). (b) pre-order: `40 20 10 5 30 60 50`. (c) post-order: `5 10 30 20 50 60 40`. (d) height 4 (path 40 → 20 → 10 → 5).

**A11.** The function moves `head` to the second node and then deletes **that** node (the new head) instead of the old first node. The old first node leaks and `head` is left dangling. It also crashes on an empty list (`head == nullptr`). Correct:
```cpp
void removeFirst(Node*& head)
{
    if (head == nullptr)
    {
        return;
    }
    Node* const oldHead = head;
    head = head->next;
    delete oldHead;
}
```

**A12.** No. The compiler deduces `T = int` from `3` and `T = double` from `4.5`, which conflict (no implicit conversion during template argument deduction). Fixes: call `larger<double>(3, 4.5)`, or write `larger(3.0, 4.5)`, or give the template two type parameters (`template <typename T1, typename T2>`, with a suitable return type).

**A13.** (a) **Yes.** Ignoring directions the graph is connected. (b) **No.** `D` has no outgoing edges, so there is no directed path from `D` to the others. (c) **Yes.** `A→B→C→A` is a cycle.

**A14.** Any four of:
1. `using namespace std;` (use `std::` prefixes).
2. Global variable `Total` (functions may only use their parameters).
3. `Total` starts with an upper-case letter although it's a variable (variables start lower-case).
4. `AddAll` is not lower camelCase (`addAll`; better `calculateSum`).
5. `v[i]` instead of `v.at(i)`.
6. Opening braces on the same line as the function header instead of on their own line.
7. `v` is passed by value (copy) and could be `const std::vector<int>&`. Parameters should be const by default.
8. Parameter name `v` is not meaningful; `i++` style/whitespace is inconsistent with the rest of the course style.
9. The function mixes concerns: it modifies a global *and* returns it.

---

## Part 2 — Assignment 1 Reference Solution

```cpp
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

void processLine(const std::string& line, std::map<std::string, int>& inventory)
{
    std::istringstream lineStream(line);

    std::string itemName;
    lineStream >> itemName;
    const bool isBlankLine = lineStream.fail();
    if (isBlankLine)
    {
        return;
    }

    int quantity = 0;
    lineStream >> quantity;
    const bool quantityIsValid = !lineStream.fail() && quantity >= 0;
    if (!quantityIsValid)
    {
        throw std::invalid_argument(line);
    }

    std::string extraText;
    lineStream >> extraText;
    const bool hasExtraText = !lineStream.fail();
    if (hasExtraText)
    {
        throw std::invalid_argument(line);
    }

    const bool itemExists = inventory.count(itemName) == 1;
    if (itemExists)
    {
        inventory.at(itemName) = inventory.at(itemName) + quantity;
    }
    else
    {
        inventory.emplace(itemName, quantity);
    }
}

int main()
{
    std::map<std::string, int> inventory;
    int errorCount = 0;

    std::string line;
    while (std::getline(std::cin, line))
    {
        try
        {
            processLine(line, inventory);
        }
        catch (const std::invalid_argument& error)
        {
            std::cout << "Error: invalid line \"" << error.what() << "\"" << std::endl;
            errorCount = errorCount + 1;
        }
    }

    std::cout << "Inventory:" << std::endl;
    for (const auto& entry : inventory)
    {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }
    std::cout << "Errors: " << errorCount << std::endl;

    return 0;
}
```

**Self-check points:** blank/whitespace-only lines silently ignored; `4.5`, `5abc`, negative numbers, missing quantity and huge numbers are all rejected; trailing spaces are fine; the error is printed *when it occurs* (before the summary); one function handles one line; `std::invalid_argument` comes from `<stdexcept>`; map keeps items alphabetically sorted on its own.

**Why the checks are in this order:** reading `quantity` fails for `x`, ``, or overflow; the `>= 0` check catches `-4`; an extra `>> extraText` that *succeeds* means leftover text. A quantity that ends the string only sets `eofbit`, not `failbit`, so the extra-text read fails and the line is accepted.

---

## Part 3 — Assignment 2 Reference Solution

```cpp
class IntList
{
public:
    IntList() : elements(new int[INITIAL_CAPACITY]), size(0), capacity(INITIAL_CAPACITY)
    {
    }

    ~IntList()
    {
        delete[] elements;
    }

    IntList(const IntList& other) : elements(new int[other.capacity]), size(other.size), capacity(other.capacity)
    {
        copyElementsFrom(other);
    }

    IntList& operator=(const IntList& other)
    {
        if (this != &other)
        {
            int* const newElements = new int[other.capacity];
            delete[] elements;
            elements = newElements;
            size = other.size;
            capacity = other.capacity;
            copyElementsFrom(other);
        }
        return *this;
    }

    void append(int value)
    {
        if (size == capacity)
        {
            growCapacity();
        }
        elements[size] = value;
        size = size + 1;
    }

    int at(int index) const
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("IntList");
        }
        return elements[index];
    }

    void removeLast()
    {
        if (size == 0)
        {
            throw std::out_of_range("IntList");
        }
        size = size - 1;
    }

    bool contains(int value) const
    {
        for (int i = 0; i < size; i = i + 1)
        {
            if (elements[i] == value)
            {
                return true;
            }
        }
        return false;
    }

    int getSize() const
    {
        return size;
    }

    int getCapacity() const
    {
        return capacity;
    }

    IntList operator+(const IntList& other) const
    {
        IntList result = *this;
        for (int i = 0; i < other.size; i = i + 1)
        {
            result.append(other.elements[i]);
        }
        return result;
    }

    bool operator==(const IntList& other) const
    {
        if (size != other.size)
        {
            return false;
        }
        for (int i = 0; i < size; i = i + 1)
        {
            if (elements[i] != other.elements[i])
            {
                return false;
            }
        }
        return true;
    }

private:
    static const int INITIAL_CAPACITY = 2;

    int* elements;
    int size;
    int capacity;

    void growCapacity()
    {
        const int newCapacity = capacity * 2;
        int* const newElements = new int[newCapacity];
        for (int i = 0; i < size; i = i + 1)
        {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
    }

    void copyElementsFrom(const IntList& other)
    {
        for (int i = 0; i < other.size; i = i + 1)
        {
            elements[i] = other.elements[i];
        }
    }
};

```

**Self-check points:**
- Members are declared in the order `elements, size, capacity`, matching the initialiser list.
- `append` grows **before** writing; growth allocates new, copies, deletes the old array, then updates the pointer and capacity.
- The copy constructor allocates its **own** array (deep copy). The copy assignment operator checks `this != &other`, allocates the new array, frees the old one, then copies. Returning `*this` allows chained assignments.
- `operator+` starts from a copy of `*this` and appends the other's elements, so neither operand changes.
- `operator==` ignores capacity and compares only size and contents.
- `const` on every method that doesn't modify the list.
- Indexing the raw array with `[]` is fine here (`at()` doesn't exist for raw arrays).

---

## Part 4 — Assignment 3 Reference Solution

```cpp
// Assumes that Key can be compared with the operators == and <
template <typename Key>
class BST
{
public:
    BST() : root(nullptr)
    {
    }

    ~BST()
    {
        destroyTree(root);
    }

    void insert(const Key& newKey)
    {
        insertNode(root, newKey);
    }

    bool contains(const Key& searchKey) const
    {
        return containsNode(root, searchKey);
    }

    int getSize() const
    {
        return countNodes(root);
    }

    int getHeight() const
    {
        return calculateHeight(root);
    }

    Key getMinimum() const
    {
        if (root == nullptr)
        {
            throw std::out_of_range("BST");
        }
        const Node* current = root;
        while (current->left != nullptr)
        {
            current = current->left;
        }
        return current->key;
    }

    Key getMaximum() const
    {
        if (root == nullptr)
        {
            throw std::out_of_range("BST");
        }
        const Node* current = root;
        while (current->right != nullptr)
        {
            current = current->right;
        }
        return current->key;
    }

    std::vector<Key> toSortedVector() const
    {
        std::vector<Key> sortedKeys;
        collectInOrder(root, sortedKeys);
        return sortedKeys;
    }

    int countLessThan(const Key& limit) const
    {
        return countNodesLessThan(root, limit);
    }

private:
    struct Node
    {
        Key key;
        Node* left;
        Node* right;

        Node(const Key& newKey) : key(newKey), left(nullptr), right(nullptr)
        {
        }
    };

    Node* root;

    static void destroyTree(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

    static void insertNode(Node*& node, const Key& newKey)
    {
        if (node == nullptr)
        {
            node = new Node(newKey);
        }
        else if (newKey < node->key)
        {
            insertNode(node->left, newKey);
        }
        else if (node->key < newKey)
        {
            insertNode(node->right, newKey);
        }
    }

    static bool containsNode(const Node* node, const Key& searchKey)
    {
        if (node == nullptr)
        {
            return false;
        }
        if (searchKey == node->key)
        {
            return true;
        }
        if (searchKey < node->key)
        {
            return containsNode(node->left, searchKey);
        }
        return containsNode(node->right, searchKey);
    }

    static int countNodes(const Node* node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    static int calculateHeight(const Node* node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        const int heightLeft = calculateHeight(node->left);
        const int heightRight = calculateHeight(node->right);
        if (heightLeft > heightRight)
        {
            return 1 + heightLeft;
        }
        return 1 + heightRight;
    }

    static void collectInOrder(const Node* node, std::vector<Key>& sortedKeys)
    {
        if (node == nullptr)
        {
            return;
        }
        collectInOrder(node->left, sortedKeys);
        sortedKeys.push_back(node->key);
        collectInOrder(node->right, sortedKeys);
    }

    static int countNodesLessThan(const Node* node, const Key& limit)
    {
        if (node == nullptr)
        {
            return 0;
        }
        if (node->key < limit)
        {
            return 1 + countNodes(node->left) + countNodesLessThan(node->right, limit);
        }
        return countNodesLessThan(node->left, limit);
    }
};

```

**Self-check points:**
- `insertNode` takes `Node*&`. Without the `&` you only change a local copy of the pointer and nothing is inserted (this is also a warning on the cheat sheet).
- Duplicates are ignored using only `<` (neither `key < node` nor `node < key` is true).
- The destructor deletes children first (post-order) and then the node itself. No leaks.
- `getHeight` of an empty tree is 0, so a lone root has height 1.
- `countLessThan` prunes: if `node->key < limit`, then the node **and its whole left subtree** qualify (use `countNodes` on the left) and only the right subtree needs recursion. Otherwise nothing in the right subtree qualifies, so only the left is searched.
- Helpers are `static` or `const` where possible; public methods that don't modify the tree are `const`.

---

## Mistakes in the cheat sheet (verify before relying on it)

Found while preparing this exam. Check these in your own copy:
1. **"Quick extra review", 2D array:** `int matrix = new int[rows];` is wrong. It should be `int** matrix = new int*[rows];`.
2. **Same section:** `classname objectname = new classname;` is missing the `*`: `classname* objectname = new classname;`.
3. **"Destructor on LinkedList" example:** the `LinkedListNode` constructor never initialises `next`. The last node's `next` is then garbage, so the destructor loop runs into undefined behaviour. Set `next = nullptr` in the constructor.
4. **Second linked-list (RabbitNode) example:** `RabbitNode* current = headRabbit;` is declared twice in `main`, so it won't compile.
5. **Style conflicts:** the bubble-sort example uses `vec[j]` and many examples use `using namespace std`. Both break the course style guidelines (the guidelines page says `[]` on vectors is not allowed).
6. **BST "INSERT" snippet** is incomplete (no recursion into left/right). Rely on the reference above instead.

---

## Rough self-grading guide
- Quiz: 1 point per question (14 pts).
- Assignment 1: ~half for correct valid-line handling, ~half for edge cases (blank lines, `4.5`, trailing text) and exact output.
- Assignments 2 and 3: count phases passed. Phase 1 alone is worth the least; correct memory handling (copy/destructor, no leaks) matters just as much as passing the asserts.

If you finished everything in time: very good. If not, note where the time went. The usual culprits are pointer/`Node*&` mistakes, template syntax, and hunting through the cheat sheet. Make a habit of opening the cheat sheet only for specific syntax, not to find the approach.
