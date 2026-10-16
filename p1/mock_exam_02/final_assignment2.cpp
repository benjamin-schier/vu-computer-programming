// Assignment 2: IntList - a growable integer list with dynamic memory
//
// See final_mock_exam.md, Part 3, for the full assignment description.
// Implement everything directly inside the class below. The tests in main()
// are split in 4 phases; get phase 1 passing first, then move on.
//
// Suggested time: 45 minutes.
//
// Check for memory errors/leaks (Linux/macOS):
//   g++ -std=c++17 -Wall -Wextra -fsanitize=address,undefined -g final_assignment2.cpp -o a2 && ./a2

#include <cassert>
#include <iostream>
#include <stdexcept>

class IntList
{
public:
    ////////////////////////////////////////////////////////////////////////
    // Phase 1
    IntList()
    // creates an empty list; it must be able to hold at least 2 elements
    // before it needs to grow
    {
    }

    ~IntList()
    // releases all memory owned by the list
    {
    }

    void append(int value)
    // adds value at the end; when the internal array is full, its capacity
    // must double (allocate a bigger array, copy, release the old one)
    {
    }

    int at(int index) const
    // returns the element at index
    // throws std::out_of_range("IntList") if index < 0 or index >= size
    {
        return 0;
    }

    int getSize() const
    // returns the number of elements currently stored
    {
        return 0;
    }

    int getCapacity() const
    // returns the current capacity of the internal array
    {
        return 0;
    }

    ////////////////////////////////////////////////////////////////////////
    // Phase 2
    void removeLast()
    // removes the last element
    // throws std::out_of_range("IntList") if the list is empty
    {
    }

    bool contains(int value) const
    // returns true if value occurs in the list
    {
        return false;
    }

    ////////////////////////////////////////////////////////////////////////
    // Phase 3: both must create independent (deep) copies
    IntList(const IntList& other)
    {
    }

    IntList& operator=(const IntList& other)
    // must also behave correctly for self-assignment (list = list)
    {
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////
    // Phase 4
    IntList operator+(const IntList& other) const
    // returns a NEW list: all elements of this list followed by all elements
    // of other. Neither operand is modified.
    {
        return *this;
    }

    bool operator==(const IntList& other) const
    // true if both lists have the same size and the same elements in the
    // same order (capacity does not matter)
    {
        return false;
    }

private:
    // Put your data members and helper functions here.
};

int main()
{
    // Phase 1: construction, append (with growth), at, destructor
    IntList list;
    assert(list.getSize() == 0);
    for (int value = 0; value < 100; value = value + 1)
    {
        list.append(value);
    }
    assert(list.getSize() == 100);
    assert(list.getCapacity() >= 100);
    assert(list.at(0) == 0);
    assert(list.at(99) == 99);

    bool exceptionThrown = false;
    try
    {
        list.at(100);
    }
    catch (const std::out_of_range&)
    {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    // Phase 2: removeLast, contains
    IntList small;
    small.append(10);
    small.append(20);
    small.append(30);
    assert(small.contains(30));
    small.removeLast();
    assert(small.getSize() == 2);
    assert(!small.contains(30));
    assert(small.contains(20));

    IntList empty;
    exceptionThrown = false;
    try
    {
        empty.removeLast();
    }
    catch (const std::out_of_range&)
    {
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    // Phase 3: copy constructor and copy assignment (deep copies)
    IntList copied = small;
    copied.append(99);
    assert(small.getSize() == 2);
    assert(copied.getSize() == 3);
    assert(copied.at(2) == 99);

    IntList assigned;
    assigned.append(1);
    assigned = small;
    assigned.append(5);
    assert(small.getSize() == 2);
    assert(assigned.getSize() == 3);
    assert(assigned.at(0) == 10);

    IntList& alias = assigned;
    assigned = alias;  // self-assignment must not break anything
    assert(assigned.getSize() == 3);
    assert(assigned.at(2) == 5);

    // Phase 4: operator+ and operator==
    IntList first;
    first.append(1);
    first.append(2);
    IntList second;
    second.append(3);
    const IntList combined = first + second;
    assert(combined.getSize() == 3);
    assert(combined.at(0) == 1);
    assert(combined.at(2) == 3);
    assert(first.getSize() == 2);
    assert(second.getSize() == 1);

    IntList duplicate = combined;
    assert(duplicate == combined);
    duplicate.append(4);
    assert(!(duplicate == combined));

    std::cout << "All tests passed." << std::endl;

    return 0;
}
