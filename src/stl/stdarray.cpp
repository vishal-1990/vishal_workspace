/*
*standard array implementation.
*std::array<int,5> arr = {};  // creates an array of int of size 5 and initilizes all elements to 0
*
*Features are same as c style arrays.
*Additional features added which provide the features of standard library.
*
*standard array is an aggregrate.
*Aggregrate means
An aggregate is an array or a class (clause 9) with no user-declared constructors (12.1), 
*no private or protected non-static data members (clause 11), 
*no base classes (clause 10), and no virtual functions (10.3).
*Hence it can be initialized with initializer list. and not round brackets
*std::array<type,size> arr = {}; //Initializes all elements with 0.
*If {} is not provided ,then values of the elements will be random and not 0.
*{5} means first element is 5 rest is zero.

**Additional sub functions
.front() = first elem
.back() = last elem
.empty() = if array is empty....faster than size() == 0
.max_size() = This function returns the maximum number of elements that the std::array can hold
fill() function fills all the elements of the std::array with the same specified value.
c1.swap(c2) = This function swaps the contents i.e. it exchanges the value of one std::array with that of another.

*/

#include <iostream>
#include <array>
#include <iterator>


int main()
{
    //Creation
    std::array<int,5> arr = {1,2,3,4,5} ;

    //Types of access
    //1>Direct access
    for(int i=0;i<arr.size();i++)
    {
        std::cout<<"Element : "  << arr[i] << std::endl; 
        //at() provides range checking.If wrong values is passed it will throw exception.
        std::cout<<"Element_at : "  << arr.at(i) << std::endl;   

    }

    //2>Using iterators
    std::array<int,5>::iterator it = arr.begin();
    while(it != arr.end()) // end() is a position past the final element.1,2,3,4,5,end
    {
        std::cout<<"Element : "  << *it << std::endl;
        ++it; 
    }

    //3>const iterators
    std::array<int,5>::const_iterator cit = arr.cbegin(); //Can also use auto cit = 
    while(cit != arr.cend()) // end() is a position past the final element.1,2,3,4,5,end
    {
        std::cout<<"Element : "  << *cit << std::endl;
        ++cit; 
    }

    //4>Reverse iterators
    std::array<int,5>::reverse_iterator rit = arr.rbegin();
    while(rit != arr.rend()) // end() is a position past the final element.1,2,3,4,5,end
    {
        std::cout<<"Element : "  << *rit << std::endl;
        ++rit; 
    }
    return 0;
}