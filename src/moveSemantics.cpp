/*
In order to understand move semantics, first we need to look at lvalue and rvalues.
=============================================================================================================================================
lvalue:
An lvalue is an expression whose address can be taken, a locator value--essentially, an lvalue provides a (semi)permanent piece of memory. 
You can make assignments to lvalues.

For example:
int a;
a = 1; // here, a is an lvalue

You can also have lvalues that aren't variables:
nt x;
int& getRef () 
{
        return x;
}
 getRef() = 4;
Here, getRef returns a reference to a global variable, so it's returning a value that is stored in a permanent location
============================================================================================================================================
rvalue:
Rvalues are--well, rvalues are not lvalues. An expression is an rvalue if it results in a temporary object. For example:
int x;
int getVal ()
{
    return x;
}
getVal();

==========================================================================================================================================================
Prior to C++11, if you had a temporary object, you could use a "regular" or "lvalue reference" to bind it, but only if it was const:

1)const string& name = getName(); // ok
2)string& name = getName(); // NOT ok

In C++11, however, there's a new kind of reference, an "rvalue reference", that will let you bind a mutable reference to an rvalue, but not an lvalue. 
In other words, rvalue references are perfect for detecting if a value is temporary object or not. 
Rvalue references use the && syntax instead of just &, and can be const and non-const, just like lvalue references, 
although you'll rarely see a const rvalue reference (as we'll see, mutable references are kind of the point):

1)const string&& name = getName(); // ok
2)string&& name = getName(); // also ok - praise be!
==============================================================================================================================================================
Rvalue is used for 2 major operations.
1)Move Semantics
  Move semantics is the idea of moving the contents from source object to destination instead of carrying out deep copy,from copy constructor.
2)Perfect forwarding
  Perfect forwarding is the concept of passing the argument in the same format as original
*/
#include <iostream>
class MoveSemantics
{
        int size;
        int *ptr;
        
        public:
        MoveSemantics(int); // Normal constructor
        MoveSemantics(const MoveSemantics& obj); //Copy Constructor
        MoveSemantics& operator=(const MoveSemantics& obj); //Copy assignment operator.

        //&& is the syntax used to represt rvalue reference
        MoveSemantics(MoveSemantics&& obj); //Move Constructor
        MoveSemantics& operator=(MoveSemantics&& obj); //Move Assignment operator

        ~MoveSemantics(); //Destructor
};

//Normal Constructor
MoveSemantics::MoveSemantics(int s):size{s}
{
        ptr = new int[size];
        for(auto i=0;i<size;i++)
        {
                ptr[i] = i;
        }
        std::cout << "==================================================" << std::endl;
        std::cout << "Inside Normal Constructor" << std::endl;
}

//Copy Constructor
MoveSemantics::MoveSemantics(const MoveSemantics& obj)
{
        //Performs deep copy
        this->size = obj.size;
        this->ptr = new int[this->size];

        //This is an expensive operation to copy in case of large data movement.
        for(auto i=0;i<this->size;i++)
        {
                this->ptr[i] = i;
        }
        std::cout << "==================================================" << std::endl;
        std::cout << "Inside Copy Constructor" << std::endl;
}

//Copy assignment operator
MoveSemantics& MoveSemantics::operator=(const MoveSemantics& obj)
{
        //Performs deep copy
        this->size = obj.size;
        this->ptr = new int[this->size];

        //This is an expensive operation to copy in case of large data movement.
        for(auto i=0;i<this->size;i++)
        {
                this->ptr[i] = i;
        }
        std::cout << "==================================================" << std::endl;
        std::cout << "Inside Copy assignment operator" << std::endl;

}

//Move Constructor
MoveSemantics::MoveSemantics(MoveSemantics&& obj)
{
        this->size = obj.size;
        this->ptr = obj.ptr;

        obj.ptr = nullptr;
        obj.size = 0;
  
        std::cout << "==================================================" << std::endl;
        std::cout << "Inside Move Constructor" << std::endl;
}

//Move Assignment operator
MoveSemantics& MoveSemantics::operator=(MoveSemantics&& obj)
{
        this->size = obj.size;
        this->ptr = obj.ptr;

        obj.ptr = nullptr;
        obj.size = 0;
  
        std::cout << "==================================================" << std::endl;
        std::cout << "Inside Move assignment operator" << std::endl;
}

MoveSemantics::~MoveSemantics()
{
        this->size = 0;
        delete []this->ptr;
        std::cout << "==================================================" << std::endl;
        std::cout << "Inside Destructor" << std::endl;
}

//this function is an rvalue
MoveSemantics returnObjByValue()
{
    MoveSemantics obj{1} ; //Will call constructor
    return obj;
    //Destructor will be called.Compiler will copy the value into temporary object
}

/*If we define the below function, we cannot define
void foo(MoveSemantics&& ) or
void foo(MoveSemantics& )
since the compiler gets confused on call foo(obj3) 
*/
void foo(MoveSemantics obj)
{
        std::cout << "==================================================" << std::endl;
        std::cout << "Inside function foo" << std::endl;
    
}

void foo1(MoveSemantics&& obj)
{
        std::cout << "==================================================" << std::endl;
        std::cout << "Inside function foo1 rvalue" << std::endl;
}

void foo1(MoveSemantics& obj)
{
        std::cout << "==================================================" << std::endl;
        std::cout << "Inside function foo1 lvalue" << std::endl;
}
int main()
{
        MoveSemantics obj{10}; // Calls normal constructor

        MoveSemantics obj1{obj}; // Calls copy constructor

        MoveSemantics obj2 = obj1; //Calls copy constructor
 
        MoveSemantics obj3{3}; //Will call normal constructor

        obj3 = obj; //Calls copy assignment operator

        MoveSemantics obj4 = returnObjByValue(); 

        //std::move(obj) casts the object to an rvalue reference/
        //Hence in the below case the move constructor will be called.
        //Beware according to definition of move constructor we have moved contents from obj to obj5 and
        //we have nullified values of obj.So obj must not be used henceforth.
        //MoveConstructor should be used when their would not be use of source object further.
        MoveSemantics obj5{std::move(obj)}; // Calls move constructor.

        foo(obj3); // This should call the copy constructor

        foo(returnObjByValue()); // this called normal constructor only.Surprised  

        
        std::cout << "*********************************************************" << std::endl;
        std::cout << "Checkpoint" << std::endl;
        foo(std::move(obj2)); // Should call move constructor.And yes it does.:)

        obj4 = std::move(obj3); //Should call move assignment operator 

        std::cout << "*********************************************************" << std::endl;
        std::cout << "Checkpoint2" << std::endl;
        foo1(obj4); //Should not call any constructor. foo1 lvalue must be called.No Destructor
        foo1(returnObjByValue()); //Will call  normal construtor inside returnObjByValue. foo1 rvalue must be called.Destructor called.

        std::cout << "*********************************************************" << std::endl;
        std::cout << "Checkpoint3" << std::endl;
        MoveSemantics obj6{5};// Normal constructor

        foo1(std::move(obj6));//Calls foo1 rvalue.No Destructor

        std::cout << "*********************************************************" << std::endl;
        std::cout << "Checkpoint4" << std::endl;
        //MoveSemantics& objref = returnObjByValue(); //Should not work
        const MoveSemantics& objref1 = returnObjByValue(); //this is allwd .One can assign rvalue to regular or lvalue reference only if it is const.
        MoveSemantics&& objref = returnObjByValue();//Allowd.This is new


        std::cout << "==================================================" << std::endl;
        std::cout << "This is before end" << std::endl;
        return 0;
}