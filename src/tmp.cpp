#include <iostream>
#include<memory>

int main()
{
	std::shared_ptr<int> ptr{ new int };
	return 0;
}