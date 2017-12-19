/*
Selection sort
Traverse through the array and find the smallest element.
Swap the smallest element to the unsorted index.
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
        v.push_back(element); 
        numberOfElements--;
    }

    while(sortedIndex != v.size())
    {
        int smallestIndex = sortedIndex;
        for(int i=sortedIndex;i<v.size();i++)
        {
            if(v[i] < v[smallestIndex])
            {
                smallestIndex = i;
            }
        }
        tmp = v[sortedIndex];        
        v[sortedIndex] = v[smallestIndex];
        v[smallestIndex] = tmp;
        sortedIndex++;
    }

    std::cout<<"Sorted elements" << std::endl;
    for(int i = 0;i<v.size();i++)
    {
        std::cout<<v[i] << ",";
    }
    std::cout<< std::endl;
    return 0;
}