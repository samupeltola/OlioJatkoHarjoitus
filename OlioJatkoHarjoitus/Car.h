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
	Car();
	Car(const string& aModel, int aYear);
	virtual ~Car(); 

	string getModel() const;
	void setModel(const string& aModel);
	int getYear() const;
	void setYear(int aYear);
	virtual void printInfo() const;
	function<void(int)> tulostusPolicy = [](int a) { cout << "Success!" << endl; };

	void addCarListener(CarListener* aNewListener) {
		listener = aNewListener;
	}
	// functional observer
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

	// observer interface
	virtual void yearChanged(int aNewYear) {
		cout << "Car year changed. New model year: " << aNewYear << endl;
	}

};