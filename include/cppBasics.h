#ifndef _CPP_BASICS_H
#define _CPP_BASICS_H

#include <iostream>
#include <initializer_list>

class BaseClass {
    private:
    int *x ;
    int var1;
    mutable int var2;

    //A static variable will have only one copy across all objects.
    //A static variable is initilized to 0 when the first object is created.
    static int staticMember;

    public:
    //Default constructor
    BaseClass();

     /*
     The rules are:
     • If either a default constructor or an initializer-list constructor could be invoked, prefer the
       default constructor.
     • If both an initializer-list constructor and an ‘‘ordinary constructor’’ could be invoked, prefer
       the initializer-list constructor.
     */

    //Constructor with initializer list
    BaseClass(std::initializer_list<int> arg) ;
    // Ordinary Constructor
    BaseClass(int a,int b);

    //Copy constructor
    BaseClass(const BaseClass &obj);

    //Destructor
    ~BaseClass();

    //Operator overloading

    void operator=(const BaseClass &obj);

    void inlineCheck(){std::cout << "checking for inline func" << std::endl;} // this acts as an inline function

    //This represents a constant member function.
    //This function can not alter the values of the members.
    void printValues() const ;   

    //Static member function.Can be called without the object ref.
    //eg:: BaseClass::staticFunc();

    static int staticFunc();

};

//imp to declare static member outside.
int BaseClass::staticMember;


class NewClass {
    int var1 ;
    int var2 ;
    int var3 ;
    
    public:
    NewClass() ; //Default
 
    //Ordinary constructor to demonstrate member initialization.Check definition
    NewClass(int a,int b);
};


#endif