#include <stdexcept>

class MyVector{
    public:
        MyVector();
        // creates an empty vector
        MyVector(int newSize);
        // creates a vector with newSize elements
        // throws std::out_of_range("MyVector::MyVector") if newSize is negative
        ~MyVector();
        // deletes the current vector, cleans up allocated data
        int& at(int index);
        // returns a reference to the value at position index
        // throws std::out_of_range("MyVector::at") if index is out of bounds
        int size();
        // returns the number of elements that can be stored inside the vector
        void resize(int newsize);
        // changes the size() of the vector to newSize
        // when newSize > allocatedSize, then resize() allocates a new data array, and copies existing values into it
        // otherwise, only the result of size() will be adjusted
        //      add a private variable for implementing this
        // throws std::out_of_range("MyVector::resize") if newSize is negative

    private:
        int allocatedSize;
        int dataSize;
        int* data;
};

MyVector::MyVector() : allocatedSize(0), dataSize(0), data(nullptr) {}

MyVector::MyVector(int newSize) : allocatedSize(newSize), dataSize(newSize)
{
    if ( newSize < 0){
        throw std::out_of_range("MyVector::MyVector");
    }
    data = new int[newSize];
}

MyVector::~MyVector()
{
    delete[] data;
}

int MyVector::size()
{
    return dataSize;
}

int& MyVector::at(int index)
{
    if ( (index < 0) || (index >=dataSize) ){
        throw std::out_of_range("MyVector::at");
    }
    return data[index];
}

void MyVector::resize(int newSize)
{

    if (newSize < 0) {
        throw std::out_of_range("MyVector::resize");
    }
    if (newSize <= allocatedSize) {
        dataSize = newSize;
    }
    else if (newSize > allocatedSize) {
        int* newData = new int[newSize];
        // the vector may have elements between data and allocated, but they souldnt be copied to the new vector
        for (int i = 0; i < dataSize; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        allocatedSize = newSize;
        dataSize = newSize;
    }
    return;

}