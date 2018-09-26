#include <iostream>
#include <string>
using namespace std;

class Beverage
{
public:
	void setDescription(string s)
	{
		description = s;
	}
	virtual string getDescription()
	{
		return description;
	}
	virtual double cost() = 0;
private:
	string description = "Unknown Beverage";
};

class CondimentDecorator :public Beverage
{
public:
	virtual string getDescription() = 0;
};

class Espresso :public Beverage
{
public:
	Espresso()
	{
		setDescription("Espresso");
	}
	double cost()
	{
		return 1.99;
	}
};

class Mocha :public CondimentDecorator
{
private:
	Beverage& beverage;
public:
	Mocha(Beverage& b):beverage(b){}
	string getDescription()
	{
		return beverage.getDescription() + ", Mocha";
	}
	double cost()
	{
		return .20 + beverage.cost();
	}
};

class Soy :public CondimentDecorator
{
private:
	Beverage& beverage;
public:
	Soy(Beverage& b):beverage(b){}
	string getDescription()
	{
		return beverage.getDescription() + ", soy";
	}
	double cost()
	{
		return .30 + beverage.cost();
	}
};

int main()
{
	Beverage* beverage = new Espresso();
	cout << beverage->getDescription() << " $" << beverage->cost() << endl;

	Beverage* beverage2 = new Espresso();
	beverage2 = new Mocha(*beverage2);
	beverage2 = new Mocha(*beverage2);
	cout << beverage2->getDescription() << " $" << beverage2->cost()<<endl;

	Beverage* beverage3 = new Espresso();
	beverage3 = new Soy(*beverage3);
	beverage3 = new Mocha(*beverage3);
	cout << beverage3->getDescription() << " $" << beverage3->cost() << endl;

	system("pause");
	return 0;
}