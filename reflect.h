#ifndef _FIX_H
#define _FIX_H
#include<iostream>
#include<unordered_map>
#include<string>
#include<functional>
#include<memory>
using namespace std;

template<typename Name,typename Type>
class Despoit_Datas
{
public:
	Despoit_Datas()
	{
		funcs = new unordered_map<Name, Type>;
	}
	bool Is_in(Name name)
	{
		if (name.size() == 0)
		{
			return false;
		}
		else
		{
			class unordered_map<Name,Type>::iterator iter = funcs->find(name);
			if (funcs->end() == iter)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
	void Insert(Name name, Type &value)
	{
		if (!Is_in(name))
		{
			funcs->emplace(name,value);
		}
		else
		{
			cout << "error" << endl;
			return;
		}
	}
	auto Find(Name name)
	{
		if (Is_in(name))
		{
			Type y = (*funcs)[name];
			return y;
		}
		else
		{
			cout << "dont't have" << endl;
		}
	}
	~Despoit_Datas()
	{
		delete funcs;
	}
private:
	unordered_map<Name, Type> *funcs;
};

template<typename F, typename ...Args>
class PackagedAndInfo
{
public:
	PackagedAndInfo() = default;
	auto operator()(F&& f, Args&& ...args)
	{
		
		function<decltype(f(args...))()> func = bind(std::forward<F>(f), std::forward<Args>(args)...);
		/*function<void()> wrapper_func = [=]()
		{
			func(); 封装成void(void)
 		};*/
		return func;
	}
};

template<typename Name,typename H,typename F, typename ...Args>
class Manager
{
public:
	Manager()
	{
		datas = new Despoit_Datas<Name, function<H(void)>>;
	}
	~Manager()
	{
		delete datas;
	}
	void Manage(Name name,F &&f,Args&&...args)
	{
		auto res = PackagedAndInfo<F,Args...>()(f,move(args)...);
		datas->Insert(name, res);
	}
	auto GetFunc(Name name)
	{
		return datas->Find(name);
	}

private:

	Despoit_Datas<Name,function<H(void)>>* datas;
};
#endif _FIX_H
