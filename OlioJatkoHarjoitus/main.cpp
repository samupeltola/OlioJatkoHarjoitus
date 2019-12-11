#include<vector>
#include<algorithm> // mm. sort
#include"Car.h"
#include<iostream>
using namespace std;

void doSomething() {
   // Heap (dynaaminen muisti)
	Car* p = new Car();
	p->setIka(10);
	p->setModel("Pekka");
	p->printInfo();

	delete p; // vapautetaan dynaaminen muisti
	
	// Stack (automaattinen pinomuisti)
	Car k("Kalle", 10);
	k.printInfo();

	Car v(k);
	v.printInfo();

	Car s = k;
	s.printInfo();
}


#include<memory> // unique_ptr, shared_ptr ja weak_ptr


void fooSmart() {
	unique_ptr<Car> pekka{ new Car{"Pekka", 30} };
	pekka->printInfo();
} 

void foo() {
	Car* pekka = new Car{ "Pekka", 30 };
	pekka->printInfo();
	Car* x = pekka;
	Car* y = x;
	delete pekka; 
}

void fooSmartShared() {
	shared_ptr<Car> pekka;
	{
		shared_ptr<Car> x { new Car{"Pekka", 30 } };
		x = nullptr; // Mitä tapahtuu?
		pekka->printInfo();
		shared_ptr<Car> y = x;
	} // x ja y vapautuvat
} // pekka vapautuu


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
		carsUniquePtr[modChoice - 1]->setIka(year_input);
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
	pekka.setIka(30);

	// Funktionaalinen observer pattern (ei perinteistä olio-interfacea)
	Car kalle("Kalle", 20);
	MyClass* myObj2 = new MyClass();
	kalle.ageChanged = [&](int aNewAge) { myObj2->ageChangedFunctional(aNewAge); };
	kalle.ageChanged = [](int aNewAge) {
		cout << "Ika muuttunut " << aNewAge << endl;
	};


	kalle.setIka(10);

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
	foo(printHelloWorldMultipleTimes);

	int a = 10;
	auto printHelloWorldMultipleTimesCapture = [=, &a]() { //kaikki muut arvoparametrina, paitsi a viitteenä
		for (int i = 0; i < a; i++) {
			cout << "Hello world " << i << endl;
		}
		a++;
	};

	// Kutsutaan Lambdaa...
	printHelloWorldMultipleTimes(10); // a:n arvo kasvaa yhdellä..
	printHelloWorldMultipleTimesCapture(); // jälkimmäisellä lambdalla ei parametreja (vain variable capture)

	system("pause");
	
	// Vektori, jossa Car -objekteja
	vector<Car> cars = { { "Pekka", 80 }, {"Tony", 50}, {"Hanna", 30} };
	cars.push_back(Car{ "Pekka", 20 });
	cars.push_back(Car{ "Marja", 30 });
	cars.push_back(Car{ "Ville", 10 });
	cars.push_back(Car{ "Kalle", 15 });


	auto myComparator = [](const Car& a, const Car& b) { return a.getYear() < b.getYear(); };

	sort(cars.begin(), cars.end(), myComparator );

	for (const Car& h : cars) {
		h.printInfo();
	}
	
	// Vektori, jossa Car -osoittimia
	vector<Car*> carsPtr = { new Car{ "Pekka", 80 }, new Car{"Tony", 50}, new Car{"Hanna", 30} };
	carsPtr.push_back(new Car{ "Pekka", 20 });
	carsPtr.push_back(new Car{ "Marja", 30 });
	carsPtr.push_back(new Car{ "Ville", 10 });
	carsPtr.push_back(new Car{ "Kalle", 15 });

	// luodaan funktio-objekti: TODO sorting
	auto myComparatorPtr = [](auto& a, auto& b) { return a->getYear() < b->getYear(); };

	sort(carsPtr.begin(), carsPtr.end(), myComparatorPtr);

	for (Car* h : carsPtr) {
		h->printInfo();
	}

	for (Car* h : carsPtr) {
		delete h;
		h = nullptr;
	}

	// 3. Vektori, jossa unique_ptr<Car> -smart pointtereita
	vector<unique_ptr<Car>> carsUniquePtr; 
	carsUniquePtr.push_back(make_unique<Car>("Pekka", 80));
	carsUniquePtr.push_back(make_unique<Car>("Pekka", 20 )); 
	carsUniquePtr.push_back(make_unique<Car>("Marja", 30 ));
	carsUniquePtr.push_back(make_unique<Car>("Ville", 10 ));
	carsUniquePtr.push_back(make_unique<Car>("Kalle", 15 ));

	// luodaan funktio-objekti
	// ComparePersonsByAgeAscendingUniquePtr myComparatorUniquePtr;
	auto myComparatorUniquePtr = [](unique_ptr<Car>& a, unique_ptr<Car>& b) { return a->getYear() < b->getYear(); };

	sort(carsUniquePtr.begin(), carsUniquePtr.end(), myComparatorUniquePtr);

	for (unique_ptr<Car>& h : carsUniquePtr) {
		h->printInfo();
	}

	// Lambda, joka muuttaa henkilön iän, jos hlö on alle 18
	auto changeChildAgeTo18 = [](auto& h) {
		if (h->getYear() < 18) {
			h->setIka(18);
		}
	};
	// Perinteisellä silmukalla
	for (auto& h : carsUniquePtr) {
		changeChildAgeTo18(h); // Muutetaan henkilön ikä, jos henkilö alle 18
	}
	// Moderni vaihtoehto: For_each -algoritmilla (vaihtoehto #include<algorithm>)
	for_each(carsUniquePtr.begin(), carsUniquePtr.end(), changeChildAgeTo18);

	int numAdults = 0;
	int numChildren = 0;

	auto countAdultsAndChildren = [&](const auto& p) { p->getYear() < 18 ? numChildren++ : numAdults++; };
	

	for_each(carsUniquePtr.begin(), carsUniquePtr.end(), countAdultsAndChildren );

	cout << "Adults: " << numAdults << endl;
	cout << "Children: " << numChildren << endl;

	/*
	unique_ptr<Car> h(new Car{ "Kalle", 30 }); // C++11->
	unique_ptr<Car> j = make_unique<Car>("Kalle", 30); // C++ 14->


	vector<unique_ptr<Car>> cars;
	cars.push_back(make_unique<Car>("Pekka", 20));
	cars.push_back(make_unique<Car>("Marja", 20));
	cars.push_back(make_unique<Car>("Ville", 20));

	// käytetään olioita
	for (auto& h : cars) {
		h->printInfo();
	}

	// vapautetaan dynaaminen muisti
	//for (Car* h : cars) {
	//	delete h;
	//}

	//foo();
	//system("pause");
	//fooSmart();
	//system("pause");
	fooSmartShared();
	*/
	system("pause");
	return EXIT_SUCCESS;
}