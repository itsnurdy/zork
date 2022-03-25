#include "stack.h"
#include "room.h"

// This is the main constructor which takes a list.
template <typename T>
Stack<T>::Stack(vector<T> list) {
    this->list = list;
}

// Peaking the stack and returning the last item on the stack.
template <typename T>
T Stack<T>::peek() {
    if(this->list.size() > 0) {
        return this->list.at(this->list.size() -1);
    }
}

// Deleting off the heap.
template <typename T>
T Stack<T>::popDelete() {
    T output;
    T newList = this->list;
    if(this->list.size() > 0){
        output = newList.at(newList.size() - 1);
        delete newList.at(newList.size() - 1);
        this->list.pop_back();
        return output;
    }
    return NULL;
}

// This will clear a stack.
template <typename T>
void Stack<T>::clear() {
    while(this->list.size() != 0) {
        delete this->list.at(this->list.size() - 1);
    }
}
