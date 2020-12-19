#ifndef MAXHEAP_H
#define MAXHEAP_H

#include<iostream>
#include<vector>

using namespace std;

class MaxHeap {
private:
    vector<int> values;
    int sz = 0;

    int parent(int index) const { return index >> 1; }
    int left(int index) const { return index * 2; }
    int right(int index) const { return (index * 2) + 1; }

    bool isValid(int index) const {
        return (index > 0 && index < sz);
    }

public:
    MaxHeap() { 
        values.push_back(0); 
        this->sz = 1;
    }
    MaxHeap(initializer_list<int> ilist) : MaxHeap() {
        for (auto val : ilist) {
            insert(val);
        }
    }
    MaxHeap(vector<int>& vec) : MaxHeap() {
        for (auto val : vec) {
            insert(val);
        }
    }
    void insert(int value);
    void pushUp(int index);
    void pushDown(int index);
    void heapify();
    bool empty() const { return values.size() == 1; }
    int getBiggerChild(int index) const;
    bool hasValidChild(int index) const;
    int size() const { return values.size(); }
    vector<int> getVector() { return values; }
    void print() const;
};

void MaxHeap::heapify() {
    if (sz > 1) {
        swap(values[1], values[--sz]);
        pushDown(1);
    } else {
        sz--;
    }
}

void MaxHeap::pushDown(int index) {
    if (!hasValidChild(index)) return;
    int biggerChildIndex = getBiggerChild(index);
    if (values[index] < values[biggerChildIndex]) {
        swap(values[index], values[biggerChildIndex]);
        pushDown(biggerChildIndex);
    }
}

int MaxHeap::getBiggerChild(int index) const {
    if (!hasValidChild(index)) throw runtime_error("Error");
    int leftIndex = left(index);
    int leftValue = values[leftIndex];
    int rightIndex = right(index);

    if (isValid(rightIndex)) {
        int rightValue = values[rightIndex];
        if (leftValue > rightValue) {
            return leftIndex;
        } else {
            return rightIndex;
        }
    }
    return leftIndex;
}

bool MaxHeap::hasValidChild(int index) const {
    return isValid(left(index));
}

void MaxHeap::insert(int value) {
    values.push_back(value);
    sz++;
    pushUp(values.size()-1);
}

void MaxHeap::pushUp(int index) {
    if (index == 1) return;
    int parentIndex = parent(index);
    if (values[parentIndex] < values[index]) {
        swap(values[parentIndex], values[index]);
        pushUp(parentIndex);
    }
}

void MaxHeap::print() const {
    for (size_t i = 1; i < values.size(); i++) {
        // if (int(i) == sz) cout << "|";
        cout << values[i];
        if (i < values.size()-1) cout << ", ";
    }
    cout << endl;
}


#endif