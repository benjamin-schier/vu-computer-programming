// Assignment 3: BST - a binary search tree class template (keys only)
//
// See final_mock_exam.md, Part 4, for the full assignment description.
// Implement everything directly inside the class template below
// (implementing it underneath costs a lot of template-syntax hassle).
// The tests in main() are split in 4 phases; get phase 1 passing first.
//
// Suggested time: 40 minutes.
//
// Check for memory errors/leaks (Linux/macOS):
//   g++ -std=c++17 -Wall -Wextra -fsanitize=address,undefined -g final_assignment3.cpp -o a3 && ./a3

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// Assumes that the type Key can be compared with both the operators == and <
template <typename Key>
class BST
{
public:
    ////////////////////////////////////////////////////////////////////////
    // Phase 1
    BST()
    {
    }

    ~BST()
    // must not leak memory (it will be checked)
    {
    }

    void insert(const Key& newKey)
    // inserts newKey; if newKey is already in the tree, nothing changes
    {
    }

    bool contains(const Key& searchKey) const
    // returns true if searchKey is stored in the tree
    {
        return false;
    }

    ////////////////////////////////////////////////////////////////////////
    // Phase 2
    int getSize() const
    // returns the number of keys stored in the tree (empty tree: 0)
    {
        return 0;
    }

    int getHeight() const
    // returns the number of nodes on the longest path from the root down to
    // a leaf. Empty tree: 0. Tree with only a root: 1.
    {
        return 0;
    }

    ////////////////////////////////////////////////////////////////////////
    // Phase 3
    Key getMinimum() const
    // returns the smallest key
    // throws std::out_of_range("BST") if the tree is empty
    {
        return Key();
    }

    Key getMaximum() const
    // returns the largest key
    // throws std::out_of_range("BST") if the tree is empty
    {
        return Key();
    }

    std::vector<Key> toSortedVector() const
    // returns all keys in ascending order
    {
        return std::vector<Key>();
    }

    ////////////////////////////////////////////////////////////////////////
    // Phase 4
    int countLessThan(const Key& limit) const
    // returns how many stored keys are strictly smaller than limit
    // (hint: use the BST property to avoid visiting subtrees you don't need)
    {
        return 0;
    }

private:
    // Put your Node struct, root pointer and helper functions here.
};

int main()
{
    // Phase 1: insert, contains (duplicates are ignored)
    BST<int> tree;
    assert(!tree.contains(5));

    const std::vector<int> values = {40, 20, 60, 10, 30, 50, 5, 30};
    const int valueCount = values.size();
    for (int i = 0; i < valueCount; i = i + 1)
    {
        tree.insert(values.at(i));
    }
    assert(tree.contains(30));
    assert(tree.contains(5));
    assert(!tree.contains(31));

    // Phase 2: getSize, getHeight
    BST<int> emptyTree;
    assert(emptyTree.getSize() == 0);
    assert(emptyTree.getHeight() == 0);
    assert(tree.getSize() == 7);
    assert(tree.getHeight() == 4);

    BST<int> singleNodeTree;
    singleNodeTree.insert(1);
    assert(singleNodeTree.getHeight() == 1);

    // Phase 3: getMinimum, getMaximum, toSortedVector
    assert(tree.getMinimum() == 5);
    assert(tree.getMaximum() == 60);
    const std::vector<int> expectedOrder = {5, 10, 20, 30, 40, 50, 60};
    assert(tree.toSortedVector() == expectedOrder);

    bool exceptionThrown = false;
    try
    {
        emptyTree.getMinimum();
    }
    catch (const std::out_of_range&)
    {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    BST<std::string> words;
    words.insert("pear");
    words.insert("apple");
    words.insert("zebra");
    const std::vector<std::string> expectedWords = {"apple", "pear", "zebra"};
    assert(words.toSortedVector() == expectedWords);
    assert(words.getMaximum() == "zebra");

    // Phase 4: countLessThan
    assert(tree.countLessThan(35) == 4);
    assert(tree.countLessThan(5) == 0);
    assert(tree.countLessThan(6) == 1);
    assert(tree.countLessThan(100) == 7);
    assert(emptyTree.countLessThan(10) == 0);

    std::cout << "All tests passed." << std::endl;

    return 0;
}
