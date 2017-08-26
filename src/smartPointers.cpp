/*
Smart Pointers
=============================================================================================================================================
In modern C++ programming, the Standard Library includes smart pointers, 
which are used to help ensure that programs are free of memory and resource leaks and are exception-safe.
=============================================================================================================================================
Smart pointers are defined in the std namespace in the <memory> header file. They are crucial to the RAII or Resource Acquisition Is Initialialization programming idiom. The main goal of this idiom is to ensure that resource acquisition occurs at the same time that the object is initialized, so that all resources for the object are created and made ready in one line of code.
================================================================================================================================================
The example demonstrates the following essential steps for using smart pointers.

1:)Declare the smart pointer as an automatic (local) variable. (Do not use the new or malloc expression on the smart pointer itself.)
2:)In the type parameter, specify the pointed-to type of the encapsulated pointer.
3:)Pass a raw pointer to a new-ed object in the smart pointer constructor. (Some utility functions or smart pointer constructors do this for you.)
4:)Use the overloaded -> and * operators to access the object.
5:)Let the smart pointer delete the object.
====================================================================================================================================================
Types of smart pointers
1>unique_ptr:It takes ownership of a raw pointer.
A unique_ptr does not share its pointer. It cannot be copied to another unique_ptr, passed by value to a function, or used in any Standard Template Library (STL) algorithm that requires copies to be made. A unique_ptr can only be moved.
unique_ptr objects automatically delete the object they manage (using a deleter) as soon as they themselves are destroyed, or as soon as their value changes either by an assignment operation or by an explicit call to unique_ptr::reset.

https://msdn.microsoft.com/en-us/library/hh279676.aspx

Functions available for unique_ptr
       1>get():Returns the stored pointer.
       2>reset():Destroys the object currently managed by the unique_ptr (if any) and takes ownership of p.
       3>release():Releases ownership of its stored pointer, by returning its value and replacing it with a null pointer.

2>shared_ptr:
Manages the storage of a pointer, providing a limited garbage-collection facility, possibly sharing that management with other objects.
Objects of shared_ptr types have the ability of taking ownership of a pointer and share that ownership: once they take ownership, the group of owners of a pointer become responsible for its deletion when the last one of them releases that ownership.

shared_ptr objects release ownership on the object they co-own as soon as they themselves are destroyed, or as soon as their value changes either by an assignment operation or by an explicit call to shared_ptr::reset. Once all shared_ptr objects that share ownership over a pointer have released this ownership, the managed object is deleted (normally by calling ::delete, but a different deleter may be specified on construction).

Whenever possible, use the make_shared function to create a shared_ptr when the memory resource is created for the first time. make_shared is exception-safe. It uses the same call to allocate the memory for the control block and the resource, and thereby reduces the construction overhead. If you do not use make_shared, then you have to use an explicit new expression to create the object before you pass it to the shared_ptr constructor. 
Some of the useful apis

    1>swap
    2>reset
    3>get
    4>use_count
    5>unique

3>weak_ptr:
http://www.learncpp.com/cpp-tutorial/15-7-circular-dependency-issues-with-stdshared_ptr-and-stdweak_ptr/

std::weak_ptr is a smart pointer that holds a non-owning ("weak") reference to an object that is managed by std::shared_ptr. It must be converted to std::shared_ptr in order to access the referenced object.
std::weak_ptr models temporary ownership: when an object needs to be accessed only if it exists, and it may be deleted at any time by someone else, std::weak_ptr is used to track the object, and it is converted to std::shared_ptr to assume temporary ownership. If the original std::shared_ptr is destroyed at this time, the object's lifetime is extended until the temporary std::shared_ptr is destroyed as well.
In addition, std::weak_ptr is used to break circular references of std::shared_ptr.
Circular reference:

In the above example, we dynamically allocate two Persons, “Lucy” and “Ricky” using make_shared() (to ensure lucy and ricky are destroyed at the end of main()). Then we partner them up. This sets the std::shared_ptr inside “Lucy” to point at “Ricky”, and the std::shared_ptr inside “Ricky” to point at “Lucy”. Shared pointers are meant to be shared, so it’s fine that both the lucy shared pointer and Rick’s m_partner shared pointer both point at “Lucy” (and vice-versa).

However, this program doesn’t execute as expected:

Lucy created
Ricky created
Lucy is now partnered with Ricky
And that’s it. No deallocations took place. Ut. Oh. What happened?

After partnerUp() is called, the ricky shared pointer goes out of scope. When that happens, ricky checks if there are any other shared pointers co-own the Person “Ricky”. There are (the shared pointer inside Person “Lucy”). Because of this, it doesn’t deallocate “Ricky” (if it did, then “Lucy” would end up with a hanging pointer). Next lucy goes out of scope, and the same thing happens. The shared pointer lucy checks if there are any other shared pointers co-owning the Person “Lucy”. There are (the shared pointer inside Person “Ricky”). So it doesn’t deallocate Lucy.

Then the program ends -- and neither Person “Lucy” or “Ricky” have been deallocated! Essentially, “Lucy” ends up keeping “Ricky” from being destroyed, and “Ricky” ends up keeping “Lucy” from being destroyed.

It turns out that this can happen any time shared pointers form a circular reference.

Sometimes an object must store a way to access the underlying object of a shared_ptr without causing the reference count to be incremented. Typically, this situation occurs when you have cyclic references between shared_ptr instances.
The best design is to avoid shared ownership of pointers whenever you can. However, if you must have shared ownership of shared_ptr instances, avoid cyclic references between them. When cyclic references are unavoidable, or even preferable for some reason, use weak_ptr to give one or more of the owners a weak reference to another shared_ptr. By using a weak_ptr, you can create a shared_ptr that joins to an existing set of related instances, but only if the underlying memory resource is still valid. A weak_ptr itself does not participate in the reference counting, and therefore, it cannot prevent the reference count from going to zero.

*/
#include<iostream>
#include<memory>

class SmartPointer {
    int a1;
    std::shared_ptr<SmartPointer> shPtr ;
    std::weak_ptr<SmartPointer> wkPtr ;
    public:
    int a;
    SmartPointer(); // Default constructor
    SmartPointer(int arg1); // Default constructor
    ~SmartPointer();//Destructor
    SmartPointer(const SmartPointer& obj);//Copy constructor
    SmartPointer(SmartPointer&& obj);//Move Construtor

    void makeCyclicReference(std::shared_ptr<SmartPointer> p);
    void weakPointerSample(std::shared_ptr<SmartPointer> p);
    void accessWeakPtr();
};

SmartPointer::SmartPointer()
{
    std::cout << "Inside Default constructor" << std::endl;
}

SmartPointer::SmartPointer(int arg1):a{arg1}
{
    std::cout << "Inside Ordinary constructor: " << a << std::endl;
}

SmartPointer::SmartPointer(const SmartPointer& obj)
{
    std::cout << "Inside Copy constructor" << std::endl;
}

SmartPointer::SmartPointer(SmartPointer&& obj)
{
    std::cout << "Inside Move constructor" << std::endl;
}

SmartPointer::~SmartPointer()
{
    std::cout << "Inside Destrutor :" << this->a << std::endl;
}

void SmartPointer::makeCyclicReference(std::shared_ptr<SmartPointer> p)
{
    shPtr = p ;    
}

void SmartPointer::weakPointerSample(std::shared_ptr<SmartPointer> p)
{
    wkPtr = p ;    
}

void SmartPointer::accessWeakPtr()
{
    /*
    Lock and restore weak_ptr
    Returns a shared_ptr with the information preserved by the weak_ptr object if it is not expired.

    If the weak_ptr object has expired (including if it is empty), the function returns an empty shared_ptr (as if default-constructed).

    Because shared_ptr objects count as an owner, this function locks the owned pointer, 
    preventing it from being released (for at least as long as the returned object does not releases it).
    */

    if(!wkPtr.expired())
    {
        std::cout << "Weak Pointer Values: " << wkPtr.lock()->a << std::endl ;
    }
}

void uniquePtr() ;
void sharedPtr() ;
void weakPtr() ;

int main(){
    uniquePtr() ; // practice unique_ptr
    sharedPtr(); // practice shared_ptr
    weakPtr(); // practice shared_ptr
    std::cout << "Before end main" << std::endl;
    return 0;
}

void uniquePtr(){

    std::cout << "*********************************************************************************************************************" << std::endl;
    std::cout << "Unique Pointer" << std::endl;
    SmartPointer* rawPtr = new SmartPointer(100);

    //std::unique_ptr<SmartPointer> ptr = new SmartPointer(10); wrong syntax since unique+ptr cannot be copied.
    std::unique_ptr<SmartPointer> ptr{new SmartPointer(10)};
    std::unique_ptr<SmartPointer> ptr1{new SmartPointer(20)};

    //For array Initialialization
    //std::unique_ptr<SmartPointer[]> ptrArr{new SmartPointer[5]{1,2,3,4,5}};

    //make_unique:It creates and returns a unique_ptr.
    //This feature is available since c++14

    //std::unique_ptr<SmartPointer> mkUniq = std::make_unique<SmartPointer>(11);

    //members can be initialized normally via -> and *. These operators are overloaded.
    //In built functions can be called using dot operator.
    std::cout << "Constructor : " << ptr->a << std::endl;

    std::cout << "=====================================================================" << std::endl;
    std::cout << "Checkpoint1 : " << std::endl;
    //unique_ptr cannot be copied but it can be moved.ptr1 is moved to new ptr

    //Curly brace define a scope.So when the newptr goes out of scope object is deleted immediately.
    {
        //Below statement is wrong
        //std::unique_ptr<SmartPointer> newptr1{ptr1} ;
        std::unique_ptr<SmartPointer> newptr{std::move(ptr1)} ;
        if(ptr1 == nullptr)
        {
            std::cout << "=====================================================================" << std::endl;
            std::cout << "Checkpoint2 newPtr: " << newptr->a << std::endl;
        }
    }

    //Releases ownership of its stored pointer, by returning its value and replacing it with a null pointer.

    std::cout << "=====================================================================" << std::endl;
    std::cout << "Checkpoint3 : " <<  std::endl;
    delete rawPtr;
    rawPtr = ptr.release();

    if(!ptr)
    {
        std::cout << "ptr is nullptr now" << std::endl;
    }
    //rawPtr is of raw type.So delete will have to be called explicitly
    delete rawPtr ;
    //==============================================================================================================================================================


    std::unique_ptr<SmartPointer> ptr2{new SmartPointer(30)};

    //reset():Destroys the object currently managed by unique_ptr.
    //It will become empty if no params are passed or will take ownership of new object.
    //get():Returns the stored ptr
    ptr2.reset(new SmartPointer(40));
    ptr2.reset();
    std::cout << "Before end unique ptr" << std::endl;
}



void sharedPtr(){
    std::cout << "*********************************************************************************************************************" << std::endl;
    std::cout << "Shared Pointer" << std::endl;

    //Types of way to create a shared ptr 

    std::shared_ptr<SmartPointer> ptr1 = std::make_shared<SmartPointer>(1000) ; // Preferred way.

    std::cout << "Ptr values 1:" << ptr1->a << std::endl;
    std::shared_ptr<SmartPointer> ptr2(new SmartPointer(2000))  ; // Less preferred.
    std::cout << "Ptr values 2:" << ptr2->a << std::endl;

    std::shared_ptr<SmartPointer> ptr3(nullptr)  ; 

    ptr3 = ptr2 ;
    std::cout << "Ptr values 3:Ptr2:" << ptr2->a << "Ptr3:" << ptr3->a << std::endl;

    //Check number of owners for a pointer.

    std::cout << "User Count Ptr1: "<< ptr1.use_count() <<" User Count Ptr2: " << ptr2.use_count() << " Ptr3 Count: " << ptr3.use_count() << std::endl;


    //Swap contents of each object.
    ptr3.swap(ptr1) ;

    std::cout << "User Count Ptr1: "<< ptr1.use_count() <<" User Count Ptr2: " << ptr2.use_count() << " Ptr3 Count: " << ptr3.use_count() << std::endl;
    std::cout << "Before end shared ptr" << std::endl;
}

void weakPtr(){
    std::cout << "*********************************************************************************************************************" << std::endl;
    std::cout << "Weak Pointer" << std::endl;

    //First we will see an example of cyclic reference. 

    std::shared_ptr<SmartPointer> ptr1 = std::make_shared<SmartPointer>(1000) ; 
    std::shared_ptr<SmartPointer> ptr2 = std::make_shared<SmartPointer>(2000) ; 

    //On execution of below statements a cyclic reference is created between both the objects.
    //Due to this the destructor is not called which causes memory leak.

    std::cout << "Cyclic reference" << std::endl;
    ptr1->makeCyclicReference(ptr2);
    ptr2->makeCyclicReference(ptr1);

    //To avoid this we use a weak pointer
    std::cout << "Weak Pointer Sample" << std::endl;
    std::shared_ptr<SmartPointer> ptr3 = std::make_shared<SmartPointer>(3000) ; 
    std::shared_ptr<SmartPointer> ptr4 = std::make_shared<SmartPointer>(4000) ; 
    ptr3->weakPointerSample(ptr4);
    ptr4->weakPointerSample(ptr3);

    ptr4->accessWeakPtr();

    std::cout << "Before end weak ptr" << std::endl;
}