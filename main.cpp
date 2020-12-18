#include<iostream>
#include<vector>
#include"heap.h"

using namespace std;

void print(const vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size()-1) {
            cout << ", ";
        }
    }
    cout << "\n";
}

void print(const vector<int>& vec, int firstIndex, int lastIndex) {
    for (int i = firstIndex; i <= lastIndex; i++) {
        cout << vec[i];
        if (i < lastIndex) {
            cout << ", ";
        }
    }
    cout << "\n";
}

// vector<int> void mergeSort(vector<int>& vec) {
//     if (vec.size() <= 2) {
//         return vec;
//     }
//     int middleIndex = int(vec.size()/2);
//     vector<int> vec1{vec.begin(), vec.begin()+middleIndex};
//     vector<int> vec2{vec.begin()+middleIndex, vec.end()};
//     mergeSort(vec1);
//     mergeSort(vec2);
// }

//TODO:
void countingSort(vector<int>& vec, int maxValue) {
    vector<int> indizes;
    for (int i = 0; i <= maxValue; i++) {
        indizes.push_back(0);
    }

    for (size_t i = 0; i < vec.size(); i++) {
        indizes[vec[i]] += 1;
    }

    int sum = 0;
    for (size_t i = 0; i < indizes.size(); i++) { 
        sum += indizes[i];
        indizes[i] = sum;
    }

    vector<int> res;
    res.reserve(vec.size());
    for (auto num : vec) {
        int index = (indizes[num]--)-1;
        res[index] = num;
    }

    // print(vec);
    // print(indizes);
    for (size_t i = 0; i < vec.size(); i++) {
        vec[i] = res[i];
    }
    // vec = res;
}

void selectionSort(vector<int>& vec) {
    for (size_t numOfSorted = 0; numOfSorted < vec.size(); numOfSorted++) {
        int smallestIndex = numOfSorted;
        for (size_t i = numOfSorted; i < vec.size(); i++) {
            if (vec[i] < vec[smallestIndex]) {
                smallestIndex = i;
            }
        }
        swap(vec[numOfSorted], vec[smallestIndex]);
    }
}

void bubbleSort(vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        int numberOfSwaps = 0;
        for (size_t k = 1; k < vec.size()-i; k++) {
            if (vec[k-1] > vec[k]) {
                swap(vec[k-1], vec[k]);
                numberOfSwaps++;
            }
        }
        if (numberOfSwaps == 0) break;
    }
}

void insertionSort(vector<int>& vec) {
    for (size_t i = 1; i < vec.size(); i++) {
        if (vec[i] < vec[i-1]) {
            for (int k = i;k != 0; k--) {
                if (vec[k] < vec[k-1]) {
                    swap(vec[k], vec[k-1]);
                } else {
                    break;
                }
            }
        }   
    }
}

void radixSort(vector<int>& vec, int digits) {
    for (int round = 1; round <= digits; round++) {
        vector<int> tmp;
        for (int digit = 0; digit < 10; digit++) {
            for (auto val : vec) {
                int tmpVal = val / pow(10, round-1);
                if ((tmpVal % 10) == digit) {
                    tmp.push_back(val);
                }
            }
        }
        vec = tmp;
    }
}

int getPivotIndex(const vector<int>& vec, int firstIndex, int lastIndex) {
    int midIndex = firstIndex + int((lastIndex - firstIndex) / 2);
    int res = (vec[firstIndex] < vec[midIndex]) ? midIndex : 0;
    res = (vec[res] < vec[lastIndex]) ? midIndex : lastIndex;
    return res;
}

void quickSort(vector<int>& vec, int firstIndex, int lastIndex) {
    if ((lastIndex - firstIndex) <= 0) { return; }
    else if ((lastIndex - firstIndex) == 1) {
        if (vec[firstIndex] > vec[lastIndex]) {
            swap(vec[firstIndex], vec[lastIndex]);
            return;
        }
    }
    int pivotIndex = getPivotIndex(vec, firstIndex, lastIndex);
    int pivot = vec[pivotIndex];
    swap(vec[pivotIndex], vec[lastIndex]);

    int left = firstIndex;
    int right = lastIndex-1;
    while(left <= right) {
        while(vec[left] < pivot) {
            if (left > right) break;
            left++;
        }
        while(vec[right] > pivot) {
            if (left > right) break;
            right--;
        }
        if (left > right) break;
        swap(vec[left], vec[right]);
        left++;
        right--;
    }
    swap(vec[left], vec[lastIndex]);
    quickSort(vec, firstIndex, left-1);
    quickSort(vec, left+1, lastIndex);
}


bool isEqual(const vector<int>& vec1, const vector<int>& vec2) {
    if (vec1.size() != vec2.size()) return false;
    for (size_t i = 0; i < vec1.size(); i++) {
        if (vec1[i] != vec2[i]) return false;
    }
    return true;
}


int normalFind(const vector<int>& vec, int num) {
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i] == num) {
            return i;
        }
    }
    return -1;
}


int betterFind(const vector<int>& vec, int num, int startIndex, int endIndex) {
    int middleIndex = startIndex + int((endIndex - startIndex) / 2);
    // cout << startIndex << "-" << endIndex << " | " << middleIndex << "\t";
    // cin.ignore();
    if (vec[middleIndex] == num) {
        return middleIndex;
    } else {
        if ((endIndex - startIndex) <= 1) return -1;
    }

    if (num < vec[middleIndex]) {
        return betterFind(vec, num, startIndex, middleIndex-1);
    } else {
        return betterFind(vec, num, middleIndex+1, endIndex);
    }
}



class Timer {
    string suffix;
    std::__1::chrono::steady_clock::time_point start;

    public:
    Timer(string suffix) {
        this->suffix = suffix;
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        cout << suffix << ": " << duration << " milliseconds" << endl;
    }
};

void trackPerformance() {

    int numberOfValues = 10'000;
    vector<int> numbers;
    for (int i = 0; i < numberOfValues; i++) {
        // numbers.push_back(arc4random() % (numberOfValues * 7));
        numbers.push_back(i);
    }
    vector<int> numbers2 = numbers;
    vector<int> numbers3 = numbers;
    cout << "Start" << endl;

    // {
    //     Timer t {"BubbleSort"};
    //     bubbleSort(numbers);
    // }

    // {
    //     Timer t {"InsertionSort"};
    //     insertionSort(numbers2);
    // }

    {
        Timer t {"QuickSort"};
        quickSort(numbers3, 0, numbers3.size()-1);
    }
    {
        Timer t {"RadixSort"};
        radixSort(numbers2, 5);
    }

    {
        Timer t {"NormalFind"};
        int index = normalFind(numbers, int(numberOfValues/3*2));
        cout << numbers[index] << endl;
        // normalFind(numbers, 500'000);
    }

    {
        Timer t {"BetterFind"};
        int index = betterFind(numbers, int(numberOfValues/3*2), 0, numbers.size()-1);
        cout << numbers[index] << endl;
    }
}

void insertAt(vector<int>& vec, int value) {
    vec.push_back(value);
    for (int i = vec.size()-1; i > 0; i--) {
        if (vec[i] < vec[i-1]) {
            swap(vec[i], vec[i-1]);
        } else break;
    }
}

int main() {
    vector<int> vec{1,2,3,4,5,6,7,8,9,11,12,13,14,15};
    insertAt(vec, 10);

    print(vec);


    // trackPerformance();


    return 0;
}