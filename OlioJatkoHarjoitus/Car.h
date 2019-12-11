#pragma once
#include<string>
#include<memory>
#include<functional>
#include<iostream>
using namespace std;

class CarListener {
public:
	virtual void yearChanged(int aNewYear) = 0;
};

class Car
{
public:
	Car(); // Oletusrakentaja ei luo osoitetta, vaan osoite on nullptr
	Car(const string& aModel, int aYear);
	// Muistetaan vapauttaa resurssit, jos sellaisia on varattuna
	virtual ~Car(); 

	string getModel() const;
	void setModel(const string& aModel);
	int getYear() const;
	void setYear(int aYear);
	// Osoite p‰ivitet‰‰n, jos oliolla on jo osoite
	// Muuten luodaan osoite dynaamisesti nullptr:n tilalle
	virtual void printInfo() const;

	// M‰‰ritell‰‰n luokalle Policy Object -tietoj‰sen (lambda)
	// eli jokaisella oliolla on oma, uniikki toiminnallisuutensa
	function<void(int)> tulostusPolicy = [](int a) { cout << "TulostusPolicy" << endl; };

	void addCarListener(CarListener* aNewListener) {
		listener = aNewListener;
		// listeners.push_back( aNewListener )
	}
	// Funktionaalinen observer
	function<void(int)> yearChanged;

private:
	int year = 0;
	string model = "";
	CarListener* listener = nullptr;
	//vector<CarListener*> listeners;

};

class MyClass : public CarListener { // MyClass IS-A CarListener
public:
	MyClass() {};
	~MyClass() {};

	void yearChangedFunctional(int aNewYear) {
		cout << "Functional: Carn year muuttunut. Uusi year: " << aNewYear << endl;
	}

	// Kuuntelijarajapinnan (observer interface) toteutus
	virtual void yearChanged(int aNewYear) {
		cout << "Car model year changed. New year: " << aNewYear << endl;
	}

};