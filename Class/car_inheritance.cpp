#include <bits/stdc++.h>

using namespace std;

class Car {
protected:
    bool isSedan;
    string seats;
    
public:
    Car(bool isSedan, string seats) {
        this->isSedan = isSedan;
        this->seats = seats;
    }

    bool getIsSedan() {
        return this->isSedan;
    }

    string getSeats() {
        return this->seats;
    }

    virtual string getMileage() = 0;

    void printCar(string name) {
        cout << "A " << name << " is " << (this->getIsSedan() ? "" : "not ")
            <<"Sedan, is " << this->getSeats() << "-seater, and has a mileage of around "
            << getMileage() << ".\n";
    }
};
// Write your code here.

/**
*   WagonR class
**/
class WagonR: public Car{
private:
    int mileage;
public:
    WagonR(int mileage): Car(false, "4"){
        this->mileage = mileage;
    }
    string getMileage(){
        return to_string(mileage) + " kmpl";
    }
};
/**
*   HondaCity class
**/
class HondaCity: public Car{
private:
    int mileage;
public:
    HondaCity(int mileage): Car(true, "4"){
        this->mileage = mileage;
    }
    string getMileage(){
        return to_string(mileage) + " kmpl";
    }
};
*   InnovaCrysta class
**/
class InnovaCrysta: public Car{
private:
    int mileage;
public:
    InnovaCrysta(int mileage): Car(false, "6"){
        this->mileage = mileage;
    }
    string getMileage(){
        return to_string(mileage) + " kmpl";
    }
};