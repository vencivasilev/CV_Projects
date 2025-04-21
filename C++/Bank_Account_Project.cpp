#include <iostream>
#include <string>

using namespace std;


class Person_Account{
    virtual void setPerson(){

    }
    virtual void setBalance(){

    }
    virtual void setCheckBalance(){
    }

};
class BankAccount:Person_Account{
private:
    string owner_name;
    double balance;

public:
    BankAccount(string on,double b){
        this->owner_name = on;
        this->balance = b;
    }
    void setOwner_Name(string on){
        this->owner_name = on;
    }
    void setBalance(double b){
        this->balance = b;
    }
    void setPerson(){
        cout << "Who is the owner of the card?" << endl;
        cin >> owner_name;
        std::cout << "The owner is: " << owner_name << endl;
    }
    void setBalance(){
        cout << "What is the balance in his bank account?" << endl;
        std::cin >> balance;
        cout << "His balance is: " << balance << endl;
    }

};

int main(){
   BankAccount ba1 = BankAccount("Pesho", 7988.39);

    ba1.setPerson();
    ba1.setBalance();

};
