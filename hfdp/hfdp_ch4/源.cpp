#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Pizza
{
protected:
	string name;
	string dough;
	string sauce;
	vector<string> toppings;
public:
	virtual void prepare()
	{
		cout << "Preparing " << name << endl;
		cout << "Tossing dough..." << endl;
		cout << "Adding sauce..." << endl;
		cout << "Adding toppings:" << endl;
		for (auto s : toppings)
		{
			cout << "    " << s << endl;
		}
	}
	virtual void bake()
	{
		cout << "Bake for 25 minutes at 350" << endl;
	}
	virtual void cut()
	{
		cout << "Cutting the pizza into diagonal slices" << endl;
	}
	virtual void box()
	{
		cout << "Place pizza in official PizzaStore box" << endl;
	}
	string getName()
	{
		return name;
	}
};
class NYStyleCheesePizza: public Pizza
{
public:
	NYStyleCheesePizza()
	{
		name = "NY Style Sauce and Cheese Pizza";
		dough = "Thin Crust Dough";
		sauce = "Marinara Sauce";

		toppings.push_back("Grated Reggiano Cheese");
	}
};
class ChicagoStyleCheesePizza: public Pizza
{
public:
	ChicagoStyleCheesePizza()
	{
		name = "Chicago Style Deep Dish Cheese Pizza";
		dough = "Extra Thick Crust Dough";
		sauce = "Plum Tomato Sauce";

		toppings.push_back("Shredded Mozzarella Cheese");
	}
	void cut()
	{
		cout << "Cutting the pizza into square slices" << endl;
	}
};

class PizzaStore
{
public:
	Pizza* orderPizza(string type)
	{
		Pizza* pizza;
		pizza = createPizza(type);

		if (pizza != NULL)
		{
			pizza->prepare();
			pizza->bake();
			pizza->cut();
			pizza->box();
		}
		else
		{
			cout << "can't order pizza " << type << endl;
		}
		return pizza;
	}
protected:
	virtual Pizza* createPizza(string type) = 0;
};

class NYPizzaStore : public PizzaStore
{
protected:
	Pizza* createPizza(string item)
	{
		if (item == "cheese")
			return new NYStyleCheesePizza();
		else
			return NULL;
	}
};

class ChicagoPizzaStore : public PizzaStore
{
protected:
	Pizza* createPizza(string item)
	{
		if (item == "cheese")
			return new ChicagoStyleCheesePizza();
		else
			return NULL;
	}
};

int main()
{
	PizzaStore* nyStore = new NYPizzaStore();
	PizzaStore* chicagoStore = new ChicagoPizzaStore();

	Pizza* pizza = nyStore->orderPizza("cheese");
	cout << "Ethan ordered a " << pizza->getName() << endl;

	delete pizza;
	pizza = chicagoStore->orderPizza("cheese");
	cout << "Joel ordered a " << pizza->getName() << endl;
	
	delete pizza;
	delete nyStore;
	delete chicagoStore;
	
	system("pause");
	return 0;
}