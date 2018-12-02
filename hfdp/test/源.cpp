#include <iostream>
#include <string>

using namespace std;

class base
{
public:
	base()
	{
		cout << "base cons" << endl;
	}
	~base()
	{
		cout << "base desc" << endl;
	}
};

class d1 :public base
{
public:
	d1()
	{
		cout << "d1 cons" << endl;
	}
	~d1()
	{
		cout << "d1 desc" << endl;
	}
};
class d2 :public base
{
private:
	base& p;
public:
	d2(base& ptr):p(ptr)
	{
		cout << "d2 cons" << endl;
	}
	~d2()
	{
		cout << "d2 desc" << endl;
	}
};
int main()
{
	auto_ptr<base> p(new d1());
	p = auto_ptr<base>(new d2(*p));
	system("pause");
	return 0;
}