#include <iostream>
#include <vector>

class TooFewNumbers {
    public:
        int size ();
        TooFewNumbers (int s);
    private:
        int s;
};
TooFewNumbers::TooFewNumbers (int s) { this->s = s;}
int TooFewNumbers::size () { return this->s;}

class AllTheSameValue {
    public: 
        int value ();
        AllTheSameValue (int);
    private:
        int v;
};
AllTheSameValue::AllTheSameValue (int v) { this->v = v;}
int AllTheSameValue::value () { return this->v;}


void printVector(const std::vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << v.at(i);
    }
    std::cout << std::endl;
}

std::vector<int> partialSums(const std::vector<int>& v) {
    std::vector<int> sums;
    int runningSum = 0;
    for (int i = 0; i < v.size(); i++) {
        runningSum += v.at(i);
        sums.push_back(runningSum);
    }
    return sums;
}

int secondSmallest(const std::vector<int>& v) {
    if (v.size() < 2) {
        throw TooFewNumbers(v.size());
    }

    int smallest = v.at(0);
    for (int i = 1; i < v.size(); i++) {
        if (v.at(i) < smallest) {
            smallest = v.at(i);
        }
    }

    bool found = false;
    int second = 0;
    for (int i = 0; i < v.size(); i++) {
        if (v.at(i) > smallest && (!found || v.at(i) < second)) {
            second = v.at(i);
            found = true;
        }
    }

    if (!found) {
        throw AllTheSameValue(smallest);
    }
    return second;
}