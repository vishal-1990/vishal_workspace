/*
Bubble sort
For each pass compare element  with next.
if greater swap it
Continue the loops until number of swaps is not 0
*/

#include<iostream>
#include<vector>


int main()
{
    int numberOfElements,element,tmp;
    int numberOfSwaps = 0;
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
    do 
    {
        numberOfSwaps = 0;
        for(int i=0;i<(v.size() - 1);i++)
        {
            if(v[i] > v[i+1])
            {
                tmp = v[i];
                v[i] = v[i+1];
                v[i+1] = tmp;
                numberOfSwaps++;
            }
        }

        if(numberOfSwaps == 0)
        {
            break;
        }
        
    }while(numberOfSwaps > 0);
    std::cout<<"Sorted elements" << std::endl;
    for(int i = 0;i<v.size();i++)
    {
        std::cout<<v[i] << ",";
    }
    std::cout<< std::endl;
    return 0;
}