#include "Car.h"
#include<iostream>
using namespace std;

Car::Car() : year( 0 ), model( "" )
{
	cout << "Carn rakentaja" << endl;
}

Car::Car(const string& aModel, int aYear) : year( aYear ), model( aModel )
{
	cout << "Carn 2 parametrinen rakentaja" << endl;
}

Car::~Car()
{
	// Vapautetaan olion varaama dynaaminen muisti ja muut resurssit
	cout << "Carn " << model << " purkaja" << endl;
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
			// Jos ikä muuttu, informoi kuuntelijoita (observers/listeners)
			if (listener) {
				listener->yearChanged(aYear);
			}
			/* Vektorillinen kuuntelijoita
					for( CarListener* listener : listeners ){
						listener->yearChanged( aYear );
					}
			*/
			// Funktionaalinen eventin lähetys
			if (yearChanged) { // tarkastetaan onko function<void(int)> asetettu
				yearChanged(aYear);
			}
		}
	}
	
}

void Car::printInfo() const
{
	cout << "Model: " << model << endl;
	cout << "Year: " << year << endl;
	if (tulostusPolicy) { // policy -objekti määritelty
		tulostusPolicy(10);
	}

}
