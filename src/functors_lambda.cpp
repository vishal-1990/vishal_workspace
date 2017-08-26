#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

/*
Topics to be covered
1>functors
2>lambda
3>function wrappers
4>std::bind

Refer one note document
*/

void functor_demo();
void lambda_demo();

class functor_demo_isEqual{
private:
	   int x;
public:
	functor_demo_isEqual(int var) :x{ var } { std::cout << "Initializing functor_demo object" << std::endl; }
	bool operator()(int val)
	{
		return (x == val);
	}
};

//Will try to use as unary predicate
class functor_isOdd {
public:
	bool operator()(int val)
	{
		return (val % 2);
	}
};

int main()
{
	functor_demo();
	lambda_demo();
	return 0;
}


/*
A functor is pretty much just a class which defines the operator(). That lets you create objects which "look like" a function
*/
void functor_demo()
{
	std::cout << "Inside functor_demo" << std::endl;
	//Start Demo 1
	functor_demo_isEqual isEqual(10); // Initializes functor_demo obj . Initializea member x
	if (isEqual(20))
	{
		std::cout << "Both values are equal" << std::endl;
	}
	else
	{
		std::cout << "Both values are not equal" << std::endl;
	}
	//End Demo 1

	//Start Demo2
	std::vector <int>v{ 1,2,3,4,5,6,7 };

	//Way 1
	auto count = std::count_if(v.begin(), v.end(), functor_isOdd()); //functor_odd() works bcoz it is treated like trmp obj creation
	std::cout << "1>Total number of odd numbers: " << count << std::endl;
	//Way 2
	functor_isOdd isOdd;
	count = std::count_if(v.begin(), v.end(), isOdd);// isOdd() doesnt work.It should be isOdd.It acts as unary predicate.
	std::cout << "2>Total number of odd numbers: " << count << std::endl;
	//Way 3

	std::function<bool(int)> fn = isOdd;
	if (fn(11))
	{
		std::cout << "Value is odd" << std::endl;
	}
	else
	{
		std::cout << "Value is even" << std::endl;
	}
	//End Demo2
}


/*
A lambda expression creates an nameless functor
[ capture clause ] (parameters) -> return-type
{
definition of method
}
Syntax used for capturing variables :
      [&] : capture all external variable by reference
	  [=] : capture all external variable by value
      [a, &b] : capture a by value and b by reference

C++ 14 additions
1>Init and capture mechanism was added

2>Generic lambda.
Can use auto type in parameter list.Also in c+=14 only


*/
void lambda_demo()
{
	//Way 1:Assigning lambda to function obj
	std::cout << "Inside lambda_demo" << std::endl;
	std::function<bool(int)> isOdd = [](int val) {return (val % 2); };
	if (isOdd(11))
	{
		std::cout << "Value is odd" << std::endl;
	}
	else
	{
		std::cout << "Value is even" << std::endl;
	}

	//Way 2:Capturing outisde variables by value
	int param = 10;
	std::function<bool(int)> isEqual = [param](int val) {return (param == val); }; // Explicit capture of variable param by value
	if (isEqual(10))
	{
		std::cout << "Both values are equal" << std::endl;
	}
	else
	{
		std::cout << "Both values are not equal" << std::endl;
	}

	//Way 3:Capturing variables by reference
	std::function<void(int)> increment = [&param](int val) {param += val;}; // Explicit capture of variable param by reference
	increment(10);
	std::cout << "Param: " << param << std::endl;

	//Way 4:Using lambda as unary predicate

	std::vector<int> v{ 1,2,3,4,5,6,7,8 };

	auto count = std::count_if(v.begin(), v.end(), [](int val) {return (val % 2); });

	std::cout << "Count of odd: " << count << std::endl;
	
	//Way 5:Init and capture c++14
	int param2 = 5;
	std::function<void()> initCap = [&newParam = param2]() {std::cout << "Init: " << newParam << std::endl; }; // init and capture
	initCap();

	std::function<void(int)> print = [](int val) {std::cout << "Value: " << val << std::endl; }; // print func

	std::function<void()> traverse = [newVector = std::move(v),&print](){std::for_each(newVector.begin(), newVector.end(), print); }; //Demonstrating move operation

	traverse();

	//Way6 :Generic lambda
	/*
	auto genericprint = [](auto val) {std::cout << "Value: " << val << std::endl; }; // print func
	genericprint(5);
	genericprint(5.5);
	*/

}