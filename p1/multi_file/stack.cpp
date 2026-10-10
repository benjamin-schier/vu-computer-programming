#include "stack.h"

Stack::Stack() {}

bool Stack::isEmpty() const {
    if (this->elements.size() == 0) {
        return true;
    }
    return false;
}

int Stack::top() const {
    if (this->isEmpty()) {
        throw std::runtime_error("stack is empty");
    }
    return this->elements.at(this->elements.size()-1);
}

int Stack::pop() {
    if (this->isEmpty()) {
        throw std::runtime_error("stack is empty");
    }
    int tmp = this->elements.at(this->elements.size()-1);
    this->elements.pop_back();
    return tmp;
}

void Stack::push(int newElement) {
    this->elements.push_back(newElement);
}

std::string Stack::toString() const {
    std::string s = "[";
    for (int i = this->elements.size() - 1; i >= 0; i--) {
        if (i < this->elements.size() - 1) {
            s+= ",";
        }
        s += std::to_string(this->elements.at(i));
    }
    s += "]";
    return s;
}