#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

template <typename T>
void printVector (const vector<T>& v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v.at(i) << " ";
    }
    cout << endl;
} 
template <typename T>
void sortVector (vector<T>& v) {
    for (int i = 0; i < v.size() - 1; i++) {
        for (int j = 0; j < v.size() - 1; j++) {
            if (v.at(j) > v.at(j + 1)) {
                T tmp = v.at(j);
                v.at(j) = v.at(j + 1);
                v.at(j + 1) = tmp;
            }
        }
    }
}
template <typename T>
int binSearch (const vector<T>& v, int minIndex, int maxIndex, T searchValue) {
    if (maxIndex < minIndex) {
        return -1;
    }
    int midIndex = (maxIndex + minIndex) / 2;
    if (v.at(midIndex) == searchValue) {
        return midIndex;
    }
    else if (v.at(midIndex) > searchValue) {
        return binSearch(v, minIndex, midIndex - 1, searchValue);
    }
    else {
        return binSearch(v, midIndex + 1, maxIndex, searchValue);
    }
}


int main () {

    vector<int> v (1000);
    srand(time(0));
    for (int i = 0; i < v.size(); i++) {
        v.at(i) = rand();
    }
    sortVector(v);
    // printVector(v);

    for (int i = 0; i < v.size(); i++) {
        cout << binSearch(v, 0, v.size() -1, v.at(i)) << " ";
    }
    return 0;
}