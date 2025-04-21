#include <iostream>
#include <string>

using namespace std;

class Human{
    private:
        string name;
        int age;
        double salary;
    public:
        Human(string n, int a, double s){
            this->name = n;
            this->age = a;
            this->salary = s;
        }

        string getName() const{
            return name;
        }
        int getAge() const{
            return age;
        }
        double getSalary() const{
            return salary;
        }
};

int main(){
    Human person1("Venci", 20, 3000);

    cout << "Името на човека:" << person1.getName()  << endl;
    cout << "Годините на човека:" << person1.getAge()  << endl;
    cout << "Заплатата на човека:" << person1.getSalary()  << endl;
};


