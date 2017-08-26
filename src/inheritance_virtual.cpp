/*
Syntax for inheriting a class.

1>class X:public Y{};
2>class X:public Y,public Z{}
3>class X:virtual public Y{}

1>Virtual Functions:Virtual function help in run time polymorphism.
http://www.geeksforgeeks.org/virtual-functions-and-runtime-polymorphism-in-c-set-1-introduction/

If function is declared as virtual, then call of function depends upond the underlying pointer to which the pointer is pointing.
In case of non-virtual function the call will be based on type of pointer which is calling the function.
How does compiler do this magic of late resolution?
Compiler maintains two things to this magic:
vtable: A table of function pointers. It is maintained per class.
vptr: A pointer to vtable. It is maintained per object (See this for an example).

Compiler adds additional code at two places to maintain and use vptr.
1) Code in every constructor. This code sets vptr of the object being created. This code sets vptr to point to vtable of the class.
2) Code with polymorphic function call (e.g. bp->show() in above code). Wherever a polymorphic call is made, compiler inserts code to first look for vptr using base class pointer or reference (In the above example, since pointed or referred object is of derived type, vptr of derived class is accessed). Once vptr is fetched, vtable of derived class can be accessed. Using vtable, address of derived derived class function show() is accessed and called.

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

//SYntax for passing values to base clas  constructor.
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