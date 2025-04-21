#include <iostream>

using namespace std;

class Rat{
        int a;
        int b;
    public:
        Rat(int a,int b){
            this->a = a;
            this->b= b;
                }
            int setA(){
            return this->a=a;
                }
            int setB(){
            return this->b=b;
                }
            int getA(){
            return a;
                }
            int getB(){
            return b;
                }
            void print(){
                cout << a << "/" << b;
            }
           Rat operator+(Rat const& obj)
           {
               Rat res(1,1);
               res.a = a + obj.a;
               res.b = obj.b;
               return res;
           }

};

int main(){
    Rat R1(2,3);
    Rat R2(5,3);
    Rat R3(1,1);

    R1.print();
    cout << "+";

    R2.print();
    cout << "=";

    R3 = R1 + R2;
    R3.print();
    cout << endl;

    return 0;

};
