#include"Car.h"
#include "Driver.h"

/*
Author: Enis Mert Kuzu 28174
Date: December 2021
Description: The following code is written for a Driver class and its member funcions.
*/ 

Driver::Driver(Car &shared,double budget) //constructor for Driver
	: sharedcar(shared), driver_budget(budget)
{ }

void Driver::drive(int drived_km)
{
	double cost=(0.25)*drived_km; // calculating the total cost when the car is driven drived_km km
	sharedcar.remain_fuel(cost); //decreasing te total fuel of car
	sharedcar.incrase_km(drived_km); //increasing the total passed km of car
}
void Driver::repairCar(string type) // to calculate the repairing cost
{
	double insurance=sharedcar.get_insurance(); // getting current insurance amount
	double inc_fee;
	if (type=="SMALL") // if driver did a small damage
	{
		driver_budget-=50; //reducing driver budget when damage is small
		inc_fee=(insurance*5 /100); //finding 5% of insurance fee
		sharedcar.increase_insurance(inc_fee); //increasing the insurance fee
		cout<<endl;
		cout<<50<<"$ is reduced from the driver's budget because of the SMALL accident"<<endl;
		cout<<"Yearly insurance fee is increased to "<<sharedcar.get_insurance() <<" because of the SMALL accident"<<endl;
	}
	else if (type=="MEDIUM") // if damage is medium
	{
		driver_budget-=150;//reducing driver budget when damage is medium
		inc_fee=(insurance*10/100); //finding 10% of insurance fee
		sharedcar.increase_insurance(inc_fee);//increasing the insurance fee
		cout<<endl;
		cout<<150<<"$ is reduced from the driver's budget because of the MEDIUM accident"<<endl;
		cout<<"Yearly insurance fee is increased to "<<sharedcar.get_insurance() <<" because of the MEDIUM accident"<<endl;
	}
	else //Large accident
	{
		driver_budget-=300;//reducing driver budget when damage is large
		inc_fee=(insurance*20/100); //finding 20% of insurance fee
		sharedcar.increase_insurance(inc_fee); //increasing the insurance fee
		cout<<endl;
		cout<<300<<"$ is reduced from the driver's budget because of the LARGE accident"<<endl;
		cout<<"Yearly insurance fee is increased to "<<sharedcar.get_insurance() <<" because of the LARGE accident"<<endl;
	}
}
void Driver::display() //displaying the current budget of driver.
{
	cout<<endl;
	cout<<"Driver Budget: "<<driver_budget<<endl;
}
void Driver::fullFuel()
{
	cout<<endl;
	cout<<"Fuel is full"<<endl;
	double to_full=sharedcar.max_capacity()-sharedcar.get_fuel(); //Calculating the amount to be filled
	sharedcar.FullingFuel();//fulling the fuel
	driver_budget-=to_full;//decreasing the budget of the drive accordingly.
}