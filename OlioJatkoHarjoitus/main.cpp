#include<vector>
#include<algorithm>
#include"Car.h"
#include<iostream>
#include<memory>
#include<functional>
using namespace std;

class MyIntCompare {
public:
	bool operator()(int a, int b) {
		return a > b;
	}
};

// Funktio-objekti, joka vertailee kahden Carn ikaa (pienemmästä suurempaan)
class ComparePersonsByAgeAscending {
public:
	// Funktio-objekti c++:ssa on objekti, jolta löytyy operator() eli objektia voi kutsua (callable object)
	bool operator()(const Car& a, const Car& b) {
		return a.getYear() < b.getYear();
	}
};

class ComparePersonsByAgeAscendingPtr {
public:
	// Funktio-objekti c++:ssa on objekti, jolta löytyy operator() eli objektia voi kutsua (callable object)
	bool operator()( const Car* a, const Car* b) {
		return a->getYear() < b->getYear();
	}
};

class ComparePersonsByAgeAscendingUniquePtr {
public:
	// Funktio-objekti c++:ssa on objekti, jolta löytyy operator() eli objektia voi kutsua (callable object)
	bool operator()(unique_ptr<Car>& a, unique_ptr<Car>& b) {
		return a->getYear() < b->getYear();
	}
};

class HelloWorldFunctionClass {
public:
	void operator() () {
		cout << "Hello world!" << endl;
	}
};



void menu() {
	vector<unique_ptr<Car>> carsUniquePtr;
	carsUniquePtr.push_back(make_unique<Car>("Mustang", 1980));
	carsUniquePtr.push_back(make_unique<Car>("Fiesta", 2019));
	bool running = true;
	while (running == true) {
		system("CLS");
		cout << "What do you want to do? " << endl << "1: Show cars" << endl <<
			"2: Add a car" << endl << "3: Modify car info" << endl << "4: Sort by year" 
			<< endl << "5: Cancel" << endl;
		string choice{ "" };
		cin >> choice;
		if (!cin) {
			cout << "Invalid input" << endl;
			system("pause");
		}
		if (choice == "1") {
			//show cars
			for (unique_ptr<Car>& h : carsUniquePtr) {
				h->printInfo();
			}
			system("pause");
		}
		else if (choice == "2") {
			//add car
			string model_input{ " " };
			int year_input{ 0 };
			cout << "Give the model of the car: " << endl;
			cin >> model_input;
			cout << "Give the year of the model " << endl;
			cin >> year_input;
			carsUniquePtr.push_back(make_unique<Car>(model_input, year_input));
			
			int index{ 1 };
			for (unique_ptr<Car>& h : carsUniquePtr) {
				cout << index << ": ";
				h->printInfo();
				index++;
			}
			system("pause");
		}
		else if (choice == "3") {
			//modify car
			int index{ 1 };
			for (unique_ptr<Car>& h : carsUniquePtr) {
				cout << index << ": ";
				h->printInfo();
				index++;
			}

			cout << "Choose the index of the one to edit: " << endl;
			int modChoice{ 0 };
			cin >> modChoice;
			cout << "Set model: " << endl;
			string model_input{ "" };
			cin >> model_input;
			carsUniquePtr[modChoice - 1]->setModel(model_input);
			int year_input{ 0 };
			cout << "Set year: " << endl;
			cin >> year_input;
			carsUniquePtr[modChoice - 1]->setYear(year_input);
			cout << "New car info: " << endl;
			carsUniquePtr[modChoice - 1]->printInfo();
			system("pause");
		}
		else if (choice == "4") {
			//sort by year
			auto myComparatorUniquePtr = [](unique_ptr<Car>& a, unique_ptr<Car>& b) { return a->getYear() < b->getYear(); };

			sort(carsUniquePtr.begin(), carsUniquePtr.end(), myComparatorUniquePtr);
			cout << "Cars sorted by year." << endl;
			system("pause");
		}
		else if (choice == "5") {
			//stop program
			cout << "Stopping..." << endl;
			running = false;
			system("pause");
		}
		else
		{
			cout << "fail, choose a real option" << endl;
			system("pause");
		}
	}
}

int main() {
	menu();
	system("pause");
	return EXIT_SUCCESS;
}