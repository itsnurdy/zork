#ifndef STACK_H
#define STACK_H

#include <vector>
#include <iostream>

using std::vector;

template <typename T>
class Stack{
private:
    vector<T> list;
    void setList(vector<T>);
    int max = 8;

public:
    Stack(){};
    Stack(vector<T>);
    T peek();

    T pop(){
        T output = NULL;
        if(this->list.size() > 0) {
            output = this->list.at(this->list.size() - 1);
            this->list.pop_back();
            return output;
        }
        return output;
    };

    T popDelete();
    void clear();

    void push(T item) {
        // If size exceeds, remove the bottom item of the stack and then add new item.
        if(this->list.size() <= this->max){
            this->list.push_back(item);
        }
        else{
            this->list.erase(this->list.begin());
            this->list.push_back(item);
        }
    };
};

#endif // STACK_H
