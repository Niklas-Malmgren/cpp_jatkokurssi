#include "TestClass.h"

TestClass::TestClass()
{
	std::cout << std::format("{:%T}", std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now())) << "\tTestClass Konstruktori\n";
}

TestClass::~TestClass()
{
	std::cout << std::format("{:%T}", std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now())) << "\tTestClass Destruktori\n";
}
