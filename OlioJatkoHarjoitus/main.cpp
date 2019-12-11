#include<vector>
#include<algorithm>
#include"Car.h"
#include<iostream>
#include<memory>
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

#include<functional>

// Vaihtoehto 1: Yksi versio, johon käyvät kaikki lambdat, jotka return==void ja ei parametreja
void funktioJokaKayttaaLambdaaV1(const function<void()>& f, int n) {
	for (int i = 0; i < n; i++) f();
}
// Vaihtoehto 2: kääntäjä generoi jokaiselle lambdalle oman versionsa alla olevasta (template)
template<typename F>
void funktioJokaKayttaaLambdaaV2(F& f, int n) {
	for( int i=0; i<n; i++ ) f();
}
// Esimerkki, jossa lambda saa int -parametrin eikä palauta mitään (void)
void foo(const function<void(int)>& f) {
	f(10);
}

void menu() {
	vector<unique_ptr<Car>> carsUniquePtr;
	carsUniquePtr.push_back(make_unique<Car>("Mustang", 1980));
	carsUniquePtr.push_back(make_unique<Car>("Fiesta", 2019));
	cout << "What do you want to do? " << endl << "1: Show cars" << endl <<
		"2: Add a car" << endl << "3: Modify car info" << endl;
	string choice{ "" };
	cin >> choice;
	if (!cin) {
		cout << "Invalid input" << endl;
	}
	if (choice == "1") {
		//show cars
		auto myComparatorUniquePtr = [](unique_ptr<Car>& a, unique_ptr<Car>& b) { return a->getYear() < b->getYear(); };

		sort(carsUniquePtr.begin(), carsUniquePtr.end(), myComparatorUniquePtr);

		for (unique_ptr<Car>& h : carsUniquePtr) {
			h->printInfo();
		}
	}
	else if (choice == "2") {
		//add car
		string model_input{ " " };
		int year_input{ 0 };
		cout << "Give the model of the car: " << endl;
		cin >> model_input;
		cout << "Give the year of the model " << endl;
	}
	else if (choice == "3") {
		//modify car
		auto myComparatorUniquePtr = [](unique_ptr<Car>& a, unique_ptr<Car>& b) { return a->getYear() < b->getYear(); };

		sort(carsUniquePtr.begin(), carsUniquePtr.end(), myComparatorUniquePtr);
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
	}
	else
	{
		cout << "fail, choose a real option" << endl;
	}
}

int main() {
	menu();
	Car pekka("Pekka", 10);
	// Luodaan kuuntelijaolio (observer, listener, event handler)
	MyClass* myObj = new MyClass();
	// Lisätään pekalle kuunelija ja testataan toimivuus (muutetaan pekan ikää)
	pekka.addCarListener(myObj);
	pekka.setYear(30);

	// Funktionaalinen observer pattern (ei perinteistä olio-interfacea)
	Car kalle("Kalle", 20);
	MyClass* myObj2 = new MyClass();
	kalle.yearChanged = [&](int aNewAge) { myObj2->yearChangedFunctional(aNewAge); };
	kalle.yearChanged = [](int aNewAge) {
		cout << "Ika muuttunut " << aNewAge << endl;
	};


	kalle.setYear(10);

	// Policy -objektin pitää olla void(int)
	pekka.tulostusPolicy = [](int a) { cout << "Hello" << a << endl; };

	kalle.printInfo();
	pekka.printInfo();

	system("pause");


	// Määritellään lambda, joka tulostaa "Hello world"
	auto helloWorldLambda = []() { cout << "Hello World from lambda!";  };
	funktioJokaKayttaaLambdaaV1(helloWorldLambda, 20);

	auto printHelloWorldMultipleTimes = [](int n) {
		for (int i = 0; i < n; i++) {
			cout << "Hello world " << i << endl;
		}
	}; 

	system("pause");
	return EXIT_SUCCESS;
}