#include "ReferenceCounting.h"

ReferenceCounting::ReferenceCounting()
{
	reference_count = 0;
}

ReferenceCounting::~ReferenceCounting()
{
	std::cout << std::format("{:%T}", std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now())) << "\tRC Destruktori\n";
}

void ReferenceCounting::addRef()
{
	reference_count++;
}

void ReferenceCounting::removeRef()
{
	reference_count--;
}

int ReferenceCounting::getRefCount()
{
	return reference_count;
}
