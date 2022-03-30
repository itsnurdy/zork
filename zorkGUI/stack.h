#ifndef STACK_H
#define STACK_H

#include <vector>
#include <iostream>

using std::vector;

template <typename T>
class Stack{
private:
    vector<T> list;
    size_t max = 8;

public:
    Stack(){};
    Stack(vector<T>);
    T peek();
    T popDelete();

    void clear();

    // Popping the last item on the stack and removing it.
    T pop() {
        T output = NULL;
        if(this->list.size() > 0) {
            output = this->list.at(this->list.size() - 1);
            this->list.pop_back();
            return output;
        }
        return output;
    }

    // This will push an item onto the stack.
    void push(T item) {
        // Checks to see if the size of the stack is excedeed.
        if(this->list.size() <= this->max) {
            this->list.push_back(item);
        } else {
            this->list.erase(this->list.begin());
            this->list.push_back(item);
        }
    };
};

#endif // STACK_H
