/*
Insertion sort
Only one main pass
elements to left are assumed sorted
compare element to all the elements in the left and place it in appropriate position
*/

#include<iostream>
#include<vector>


int main()
{
    int numberOfElements,element,tmp;
    int sortedIndex = 0,index = 0;
    std::vector<int> v;
    std::cout << "Enter number of elements" << std::endl;
    std::cin >> numberOfElements;

    while(numberOfElements > 0)
    {
        std::cout << "Enter element " << std::endl;
        std::cin >> element ;
        v.push_back(element) ;
        numberOfElements--;
    }

    //Sorting algorithm

    while(sortedIndex < v.size())
    {
       //Compare the index in question with all elements in left side
       for(int i = sortedIndex;i>0;--i)
       {
        if(v[i] < v[i-1])
        {
            tmp = v[i];
            v[i] = v[i-1];
            v[i-1] = tmp;          
        }
        else
        {
            //This step is added cause, all the elements in the left
            //are sorted.So if the given element is greater than or equal to
            //previous element then it is at correct slot
            break;
        }
       }
       ++sortedIndex;
    }
    std::cout<<"Sorted elements" << std::endl;
    for(int i = 0;i<v.size();i++)
    {
        std::cout<<v[i] << ",";
    }
    std::cout<< std::endl;
    return 0;
}


    