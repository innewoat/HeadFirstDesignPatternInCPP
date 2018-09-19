#include <iostream>

using std::cout;
using std::endl;

class FlyBehavior
{
public:
	virtual void fly() = 0;
};

class FlyWithWings :public FlyBehavior
{
public:
	void fly()
	{
		cout << "I'm flying" << endl;
	}
};

class FlyNoWay :public FlyBehavior
{
public:
	void fly()
	{
		cout << "I can't fly" << endl;
	}
};

class QuackBehavior
{
public:
	virtual void quack() = 0;
};

class Quack :public QuackBehavior
{
public:
	void quack()
	{
		cout << "Quack" << endl;
	}
};

class MuteQuack :public QuackBehavior
{
public:
	void quack()
	{
		cout << "<< Silence >>" << endl;
	}
};

class Squeak :public QuackBehavior
{
public:
	void quack()
	{
		cout << "Squeak" << endl;
	}
};

class Duck
{
public:
	FlyBehavior* flyBehavior;
	QuackBehavior* quackBehavior;
public:
	void performFly()
	{
		flyBehavior->fly();
	}
	void performQuack()
	{
		quackBehavior->quack();
	}
	virtual void display() = 0;
	void swim()
	{
		cout << "All ducks float, even decoys" << endl;
	}
};
class MallardDuck :public Duck
{
public:
	MallardDuck()
	{
		flyBehavior = new FlyWithWings();
		quackBehavior = new Quack();
	}
	void display()
	{
		cout << "I am a real Mallard duck" << endl;
	}
};
int main()
{
	Duck* mallard = new MallardDuck();
	mallard->display();
	mallard->performFly();
	mallard->performQuack();
	system("pause");
	return 0;
}