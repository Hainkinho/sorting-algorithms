#include<iostream>

using namespace std;

int main() {

    int num = 123;
    int indexOfDiget = 1;

    num = num / int(pow(10, indexOfDiget-1));
    num = num % 10;

    cout << num << endl;




    return 0;
}