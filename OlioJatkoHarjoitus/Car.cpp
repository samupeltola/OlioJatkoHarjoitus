#include "Car.h"
#include<iostream>
using namespace std;

Car::Car() : year( 0 ), model( "" )
{
	cout << "Car constructor" << endl;
}

Car::Car(const string& aModel, int aYear) : year( aYear ), model( aModel )
{
	cout << "Car contructor with 2 parametres" << endl;
}

Car::~Car()
{
	cout << "Car " << model << "'s purkaja" << endl;
}

string Car::getModel() const
{
	return model;
}

void Car::setModel(const string& aModel)
{
	model = aModel;
}

int Car::getYear() const
{
	return year;
}

void Car::setYear(int aYear)
{
	if (year >= 0) {	
		if (aYear != year) {
			year = aYear;
			// if year changed inform observer
			if (listener) {
				listener->yearChanged(aYear);
			}
			if (yearChanged) { // check for function<void(int)>
				yearChanged(aYear);
			}
		}
	}
}

void Car::printInfo() const
{
	cout << "Model: " << model << endl;
	cout << "Year: " << year << endl;
}
