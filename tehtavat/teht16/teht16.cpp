#include <iostream>

int main()
{
	long long i;
	try
	{

		for (i = 0; i < 1000000000000000; i++)
		{
			int* x = new int;
		}
	}
	catch(const std::exception& e)
	{
		std::cout << "Memory used: " << i * sizeof(int) << "\n";
		std::cout << e.what();
	}

	// Microsoft C++ exception: std::bad_alloc at memory location 0x000000B1020FF5B0.

}
