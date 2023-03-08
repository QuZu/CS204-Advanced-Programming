#include"Car.h"

/*
Author: Enis Mert Kuzu 28174
Date: December 2021
Description: The following code is written for a Car class and its member funcions.
*/

Car::Car(double f,double i,double km) //constructor for car object
	:fuel(f),insurance(i),passed_km(km),capacityFuel(f)
	//assigning the values of fuel, insurance fee , passed km, fuel capacity
{}
void Car::display() //display the fuel level, insurance fee and the total distance that the car has travelled
{
cout<<"Fuel Level: "<<fuel<<endl;
cout<<"Insurance Fee: "<<insurance<<endl;
cout<<"Total distance that the car has travelled: "<<passed_km<<endl;
}
double Car::get_fuel()
{
 return fuel;
}
void Car::remain_fuel(double x) //removing spent fuel (x) from fuel 
{
	fuel-=x;
}
double Car::get_insurance()
{
	return insurance;
}
double Car::get_km()
{
	return passed_km;
}
void Car::incrase_km(int km) //increasing the total passed km when car driving
{
	passed_km+=km;
}
void Car::increase_insurance(double num)// finding the new insurance amount when it increases as num dolars
{
	insurance+=num;
}
void Car::FullingFuel() // fulling th fuel
{
	fuel=capacityFuel;
}
double Car::max_capacity() //returns the fuel capacity of car 
{
	return capacityFuel;
}