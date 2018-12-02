#include <iostream>
#include <string>

using namespace std;

class ChocolateBoiler
{
private:
	bool empty;
	bool boiled;
	static ChocolateBoiler* chocolateBoiler;

	ChocolateBoiler()
	{
		empty = true;
		boiled = false;
		cout << "construct" << endl;
	}

public:
	static ChocolateBoiler& getInstance()
	{
		if (chocolateBoiler == NULL)
			chocolateBoiler = new ChocolateBoiler();
		return *chocolateBoiler;
	}
	
	void fill()
	{
		if (isEmpty())
		{
			empty = false;
			boiled = false;
			cout << "fill" << endl;
		}
	}

	void drain()
	{
		if (!isEmpty() && isBoiled())
		{
			empty = true;
			cout << "drain" << endl;
		}
	}

	void boil()
	{
		if (!isEmpty() && !isBoiled())
		{
			boiled = true;
			cout << "boil" << endl;
		}
	}

	bool isEmpty()
	{
		return empty;
	}

	bool isBoiled()
	{
		return boiled;
	}
};

ChocolateBoiler* ChocolateBoiler::chocolateBoiler = NULL;

int main()
{
	ChocolateBoiler& boiler1 = ChocolateBoiler::getInstance();
	ChocolateBoiler& boiler2 = ChocolateBoiler::getInstance();

	boiler1.fill();
	boiler2.boil();
	boiler1.drain();

	system("pause");
	return 0;
}