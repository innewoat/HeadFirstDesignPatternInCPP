#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PizzaIngredientFactory
{
public:
	virtual string createDough() = 0;
	virtual string createSauce() = 0;
	virtual string createCheese() = 0;
	virtual string createVeggies() = 0;
	virtual string createPepperoni() = 0;
	virtual string createClam() = 0;
};
class NYPizzaIngredientFactory : public PizzaIngredientFactory
{
public:
	string createDough() { return "ThinCrustDough"; }
	string createSauce() { return "MarinaraSauce"; }
	string createCheese() { return "ReggianoCheese"; }
	string createVeggies() { return "Garlic Onion Mushroom RedPepper"; }
	string createPepperoni() { return "SlicedPepperoni"; }
	string createClam() { return "FreshClams"; }
};
class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory
{
public:
	string createDough() { return "ThinCrustDough"; }
	string createSauce() { return "PlumTomatoSauce"; }
	string createCheese() { return "MozzarellaCheese"; }
	string createVeggies() { return "BlackOlives Spinach EggPlant"; }
	string createPepperoni() { return "SlicedPepperoni"; }
	string createClam() { return "FrozenClams"; }
};

class Pizza
{
protected:
	string name;
	string dough;
	string sauce;
	string veggies;
	string cheese;
	string pepperoni;
	string clam;
	PizzaIngredientFactory* ingredientFactory;
public:
	virtual void prepare() = 0;
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
	void setName(string name)
	{
		this->name = name;
	}
};
class CheesePizza : public Pizza
{
public:
	CheesePizza(PizzaIngredientFactory* ingredientFactory)
	{
		this->ingredientFactory = ingredientFactory;
	}
	void prepare()
	{
		cout << "Preparing " << name << endl;
		dough = ingredientFactory->createDough();
		sauce = ingredientFactory->createSauce();
		cheese = ingredientFactory->createCheese();
	}
};
class ClamPizza :public Pizza
{
public:
	ClamPizza(PizzaIngredientFactory* ingredientFactory)
	{
		this->ingredientFactory = ingredientFactory;
	}
	void prepare()
	{
		cout << "Preparing " << name << endl;
		dough = ingredientFactory->createDough();
		sauce = ingredientFactory->createSauce();
		cheese = ingredientFactory->createCheese();
		clam = ingredientFactory->createClam();
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
	void setIngredientFactory(PizzaIngredientFactory* ingredientFactory)
	{
		this->ingredientFactory = ingredientFactory;
	}
protected:
	virtual Pizza* createPizza(string type) = 0;
	PizzaIngredientFactory* ingredientFactory;
};
class NYPizzaStore : public PizzaStore
{
public:
	NYPizzaStore(PizzaIngredientFactory* ingredientFactory)
	{
		setIngredientFactory(ingredientFactory);
	}
protected:
	Pizza* createPizza(string item)
	{
		Pizza* pizza = NULL;
		if (item == "cheese")
		{
			pizza = new CheesePizza(ingredientFactory);
			pizza->setName("New York Style Cheese Pizza");
		}
		else if (item == "clam")
		{
			pizza = new ClamPizza(ingredientFactory);
			pizza->setName("New York Style Clam Pizza");
		}
		return pizza;
	}
};
class ChicagoPizzaStore : public PizzaStore
{
public:
	ChicagoPizzaStore(PizzaIngredientFactory* ingredientFactory)
	{
		setIngredientFactory(ingredientFactory);
	}
protected:
	Pizza* createPizza(string item)
	{
		Pizza* pizza = NULL;
		if (item == "cheese")
		{
			pizza = new CheesePizza(ingredientFactory);
			pizza->setName("Chicago Style Cheese Pizza");
		}
		else if (item == "clam")
		{
			pizza = new ClamPizza(ingredientFactory);
			pizza->setName("Chicago Style Clam Pizza");
		}
		return pizza;
	}
};

int main()
{
	PizzaIngredientFactory* nyIngredientFactory = new NYPizzaIngredientFactory();
	PizzaIngredientFactory* chicagoIngredientFactory = new ChicagoPizzaIngredientFactory();

	PizzaStore* nyStore = new NYPizzaStore(nyIngredientFactory);
	PizzaStore* chicagoStore = new ChicagoPizzaStore(chicagoIngredientFactory);

	Pizza* pizza = nyStore->orderPizza("cheese");
	cout << "Ethan ordered a " << pizza->getName() << endl;

	delete pizza;
	pizza = chicagoStore->orderPizza("clam");
	cout << "Joel ordered a " << pizza->getName() << endl;
	
	delete pizza;
	delete nyStore;
	delete chicagoStore;
	delete nyIngredientFactory;
	delete chicagoIngredientFactory;

	system("pause");
	return 0;
}