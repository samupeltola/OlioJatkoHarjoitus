#include "Car.h"
#include<iostream>
using namespace std;

Car::Car() : ika( 0 ), model( "" )
{
	cout << "Carn rakentaja" << endl;
}

Car::Car(const string& aModel, int aIka) : ika( aIka ), model( aModel )
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
	return ika;
}

void Car::setIka(int aIka)
{
	if (ika >= 0) {	
		if (aIka != ika) {
			ika = aIka;
			// Jos ikä muuttu, informoi kuuntelijoita (observers/listeners)
			if (listener) {
				listener->ageChanged(aIka);
			}
			/* Vektorillinen kuuntelijoita
					for( CarListener* listener : listeners ){
						listener->ageChanged( aIka );
					}
			*/
			// Funktionaalinen eventin lähetys
			if (ageChanged) { // tarkastetaan onko function<void(int)> asetettu
				ageChanged(aIka);
			}
		}
	}
	
}

void Car::printInfo() const
{
	cout << "Model: " << model << endl;
	cout << "Year: " << ika << endl;
	if (tulostusPolicy) { // policy -objekti määritelty
		tulostusPolicy(10);
	}

}
