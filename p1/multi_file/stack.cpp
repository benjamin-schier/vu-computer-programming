#include "stack.h"

bool Stack::isEmpty() const {
    if (this->elements.size() == 0) {
        return true;
    }
    return false;
}