#include"fix.h"

int Add(int x, int y)
{
	cout << x << "+" << y << "=" << x + y << endl;
	return x + y;
}
int Minus(int x, int y)
{
	cout << x << "-" << y << "=" << x - y << endl;
	return x - y;
}
int main()
{
	Manager<string,int,decltype(Add), int, int>m;
	string name = "Add";
	m.Manage(name,Add, 1, 2);

	auto res = m.GetFunc(name);
	auto x = res();

	string name1 = "Minus";
	m.Manage(name1, Minus, 1, 2);
	auto res1 = m.GetFunc(name1);
	auto z = res1();
	
}
