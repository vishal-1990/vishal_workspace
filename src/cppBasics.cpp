#include <cppBasics.h>


BaseClass::BaseClass()
{
    this->var1 = 0 ;
    this->var2 = 0 ;
    this->x = new int[1];
    std::cout << "=========================================================================" << std::endl ; 
    std::cout << "Inside Default Constructor" << std::endl ;
}

/*
     The rules are:
     • If either a default constructor or an initializer-list constructor could be invoked, prefer the
       default constructor.
     • If both an initializer-list constructor and an ‘‘ordinary constructor’’ could be invoked, prefer
       the initializer-list constructor.
*/
BaseClass::BaseClass(std::initializer_list<int> arg)
{
    std::cout << "=========================================================================" << std::endl ; 
    std::cout << "Inside Initializer Constructor"<< std::endl;

    this->var1 = arg.begin()[0] ; //Unfortunately, initializer_list doesn’t provide subscripting.
    this->var2 = arg.begin()[1] ;
    this->x = new int[1];
    std::cout << "var1:"<<this->var1 <<" var2:" << this->var2 << std::endl;
}

BaseClass::BaseClass(int a,int b)
{
    this->var1 = a;
    this->var2 = b;

    this->x = new int[var1];

    std::cout << "=========================================================================" << std::endl ; 
    std::cout << "Inside Ordinary Constructor\nvar1:" << this->var1 << "var2:" << this->var2 << "staticMember:" << BaseClass::staticFunc() << std::endl;
}

/*
Destructor
A destructor cannot have arguments and a class can have only one destrutor.
A destructor is invoked implicitly when the object goes out of scope.
*/
BaseClass::~BaseClass()
{
    delete []x;
    std::cout << "Inside Destructor" << std::endl;
}

 /*
       The default copy constructor which is provided by the c++ compiler performs a member wise copy(shallow copy).
       But this is dangerous in case of classes having pointers as members since this can result into invalid access and dangling pointers.
       Hence we should provide our own copy constructor which performs a deep copy.Each object must have its own copy of dynamic memory.  
       Copy constructor is invoked in following cases.
       1. When an object of the class is returned by value.
       2. When an object of the class is passed (to a function) by value as an argument.
       3. When an object is constructed based on another object of the same class.
       4. When compiler generates a temporary object.
*/

/* Special Note
Test t2 = fun();
Compiler Error in line "Test t2 = fun();" 
compiler creates a temporary object which is copied to t2 using copy constructor in the original program 
(The temporary object is passed as an argument to copy constructor). The reason for compiler error is, compiler created temporary objects cannot be bound to non-const references and the original program tries to do that. 
It doesn’t make sense to modify compiler created temporary objects as they can die any moment. 
*/
BaseClass::BaseClass(const BaseClass &obj)
{
     this->var1 = obj.var1 ;
     this->var2 = obj.var2 ;
     this->x = new int[this->var1] ;   
      
     std::cout << "=========================================================================" << std::endl ; 
     std::cout << "Inside Copy Constructor\nvar1:" << this->var1 << "var2:" << this->var2 << std::endl;
}

/*
   Overloading the default assignment operator
*/
void BaseClass::operator=(const BaseClass &obj)
{
     this->var1 = obj.var1 ;
     this->var2 = obj.var2 ;
     this->x = new int[this->var1] ;   

     std::cout << "=========================================================================" << std::endl ; 
     std::cout << "Inside Assignment operator\nvar1:" << this->var1 << "var2:" << this->var2 << std::endl;
}

//constant member function

void BaseClass::printValues() const
{
     //this->var1 += 1 ;          This line will cause error
     this->var2 += 1;             // This line doesnt cause error bcoz var2 is defined as mutable.
                                  //Mutable members can be altered in const member functions or objects. 
     std::cout << "=========================================================================" << std::endl ; 
     std::cout << "Inside Print Values\nvar1:" << this->var1 << "var2:" << this->var2 << std::endl;
}

//Static member function
int BaseClass::staticFunc() 
{
    return ++staticMember ;
}



NewClass::NewClass()
{
    std::cout << "=========================================================================" << std::endl ; 
    std::cout << "Inside Default Constructor" << std::endl ;
}


//Member Initialization
//The member initializer list starts with a colon, and the individual member initializers are separated
//by commas.

NewClass::NewClass(int a,int b):var1{a},var2{b}
{
    std::cout << "=========================================================================" << std::endl ; 
    std::cout << "Inside ordinary Constructor to demonstrate member initilization" << std::endl ;
    std::cout << "var1:" << this->var1 << "var2:" << this->var2 << std::endl;
}

int main(int argc, char *argv[])
{
     
    //Constructor initialization basics
    BaseClass ob;          //Default Constructor is called
    BaseClass ob1{3} ;    //Initializer Constructor is called.()
    BaseClass obj1{5,6} ;    //Initializer Constructor is called.()
    BaseClass obj5(1,2) ;    //Ordinary Constructor is called.()
    BaseClass obj2{3,4} ;
    BaseClass *obj = new BaseClass{6,7} ; // Constructor is called

    BaseClass newobj = obj1 ;  //Copy constructor is invoked

    obj2 = obj1 ; // Overloaded assignment operator is invoked.

    obj1.inlineCheck() ;

    obj1.printValues();

    NewClass c1;
    NewClass c2{3,4}; // Demonstrate member initialization


    return 0;
}