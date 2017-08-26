/*
1>Virtual Functions:Virtual function help in run time polymorphism.
If function is declared as virtual, then call of function depends upond the underlying pointer to which the pointer is pointing.
In case of non-virtual function the call will be based on type of pointer which is calling the function.

2>Casting Operators
There are several casting operators specific to the C++ language. These operators are intended to remove some of the ambiguity and danger inherent in old style C language casts. These operators are:
1--> dynamic_cast Used for conversion of polymorphic types.
2--> static_cast Used for conversion of nonpolymorphic types.
3--> const_cast Used to remove the const, volatile, and __unaligned attributes.
4--> reinterpret_cast Used for simple reinterpretation of bits.
5--> safe_cast Used to produce verifiable MSIL.

*/
#include <iostream>
#include <memory>

class BaseClass{
    int var;
	public:
	BaseClass(int) ;
	void printVal1();
	virtual void printVal2();
};

class DerivedClass:public BaseClass {
    int var1;
	public:
	DerivedClass(int,int) ;
	void printVal1();
	void printVal2();
};

BaseClass::BaseClass(int a)
{
    this->var = a;
	std::cout << "Base class Constructor: " << this->var << std::endl;
}

void BaseClass::printVal1()
{
	std::cout << "Base class func Non virtual: " << this->var << std::endl;
}

void BaseClass::printVal2()
{
	std::cout << "Base class func virtual: " << this->var << std::endl;
}

DerivedClass::DerivedClass(int a,int b):BaseClass{a}
{
	this->var1 = b;
	std::cout << "Derived class Constructor: " << this->var1 << std::endl;
}

void DerivedClass::printVal1()
{
	std::cout << "Derived class func Non virtual: " << this->var1 << std::endl;
}

void DerivedClass::printVal2()
{
	std::cout << "Derived class func virtual: " << this->var1 << std::endl;
}

int main(int argc,char *argv[])
{
    BaseClass *b = new BaseClass{10};
	DerivedClass *d = new DerivedClass{20,30};

    //Behaviour of virtual function
	b->printVal1();
	d->printVal1();

	b = d;
	b->printVal1(); // Will call Base class function
	b->printVal2(); // Will call Derived class function


	return 0;
}