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
private:
	FlyBehavior* flyBehavior;
	QuackBehavior* quackBehavior;
public:
	Duck()
	{
		flyBehavior = NULL;
		quackBehavior = NULL;
	}
	~Duck()
	{
		delete flyBehavior;
		delete quackBehavior;
	}
	void performFly()
	{
		if (flyBehavior != NULL)
			flyBehavior->fly();
		else
			cout << "fly behavior is null" << endl;
	}
	void performQuack()
	{
		if (quackBehavior != NULL)
			quackBehavior->quack();
		else
			cout << "quack behavior is null" << endl;
	}
	virtual void display() = 0;
	void swim()
	{
		cout << "All ducks float, even decoys" << endl;
	}
	void setFlyBehavior(FlyBehavior* fb)
	{
		delete flyBehavior;
		flyBehavior = fb;
	}
	void setQuackBehavior(QuackBehavior* qb)
	{
		delete quackBehavior;
		quackBehavior = qb;
	}
};
class MallardDuck :public Duck
{
public:
	MallardDuck()
	{
		setFlyBehavior(new FlyWithWings());
		setQuackBehavior(new Quack());
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
	mallard->setFlyBehavior(new FlyNoWay());
	mallard->performFly();
	system("pause");
	return 0;
}