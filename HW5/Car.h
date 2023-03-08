#ifndef CAR_H
#define CAR_H
#include <iostream>
#include<string>
using namespace std;
//Enis Mert Kuzu 28174
class Car
{
public:
	Car(double,double,double);
	void display();
	double get_fuel(); //returns the remaining fuel
	double get_insurance(); //returns the insurance cost
	double get_km(); //returns the total passed km
	double max_capacity(); //returns the fuel capacity of car 
	void remain_fuel(double); //to calculate remaining fuel based on spent fuel
	void incrase_km(int); //to add passed km to total km
	void increase_insurance(double); //to increase insurance fee in case of an accident
	void FullingFuel(); // to full the fuel

private:
	double fuel;
	double insurance;
	int passed_km;
	double capacityFuel;

};

#endif // !CAR_H
