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
	virtual void printInfo() const;
	function<void(int)> tulostusPolicy = [](int a) { cout << "Success!" << endl; };

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
};

class MyClass : public CarListener { // MyClass IS-A CarListener
public:
	MyClass() {};
	~MyClass() {};

	void yearChangedFunctional(int aNewYear) {
		cout << "Functional: Car year changed. New model year: " << aNewYear << endl;
	}

	// Kuuntelijarajapinnan (observer interface) toteutus
	virtual void yearChanged(int aNewYear) {
		cout << "Car year changed. New model year: " << aNewYear << endl;
	}

};