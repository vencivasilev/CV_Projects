#include <iostream>

using namespace std;

void myFunction(){
    int number1;
    int number2;

    cout << "Enter a number to compare:" << endl;
    cin >> number1;

    cout << "Enter a second number to compare: " << endl;
    cin >> number2;

    int *pNumber1 = &number1;
    int *pNumber2 = &number2;

    if(*pNumber1 > *pNumber2){
        cout << "The first number is grater" << endl;
    }
    if(*pNumber1 < *pNumber2){
        cout << "The second number is grater" << endl;
    }
    if(*pNumber1 == *pNumber2){
        cout << "They are equal" << endl;
    }

}


int main(){
  myFunction();
  return 0;
};
