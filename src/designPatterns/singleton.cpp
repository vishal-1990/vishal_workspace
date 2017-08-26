#include <iostream>


class Singleton {
private:
	static Singleton* _obj;
	int var;
protected:
	Singleton() = default;
	Singleton(const Singleton &obj) = default;
	Singleton* operator=(const Singleton &obj) {};
	~Singleton()
	{
		 //Wrong statement will go into recursion.Destuctor is called when the object is deleted.
		//delete(_obj);
		std::cout << "memory destroyed" << std::endl;
	}
public:
	static Singleton* getObj();
	static Singleton* deleteObj();
	int getValues();

};

Singleton* Singleton::_obj = nullptr;

Singleton* Singleton::getObj()
{
	if (_obj == nullptr)
	{
		_obj = new Singleton; 
		_obj->var = 10; //Lazy initialization.Values will be assigned only during first initialization.
	}
	return _obj;
}

Singleton* Singleton::deleteObj()
{
 if(_obj != nullptr)
 {
	 delete _obj;
 }
}
int Singleton::getValues()
{
	return var;
}




int main()
{

	std::cout << "value: " << Singleton::getObj()->getValues() << std::endl;
	Singleton::deleteObj();
	return 0;
}