#ifndef DRIVER_H
#define DRIVER_H
#include <iostream>
#include<string>
using namespace std;
//Enis Mert Kuzu 28174
class Driver
{
public:
	Driver(Car &shared,double budget);
	void drive (int);
	void repairCar(string);
	void display();
	void fullFuel();

private:
	Car &sharedcar;
	double driver_budget;
};

#endif // !DRIVER_H
