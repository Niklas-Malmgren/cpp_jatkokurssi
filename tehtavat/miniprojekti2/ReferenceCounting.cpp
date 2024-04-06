#include "ReferenceCounting.h"

ReferenceCounting::ReferenceCounting()
{
	reference_count = 0;
}

ReferenceCounting::~ReferenceCounting()
{
	std::lock_guard<std::mutex> guard(mutex);
	std::cout << std::format("{:%T}", std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now())) << "\tRC Destruktori\n";
}

void ReferenceCounting::addRef()
{
	std::lock_guard<std::mutex> guard(mutex);
	reference_count++;
}

void ReferenceCounting::removeRef()
{
	std::lock_guard<std::mutex> guard(mutex);
	reference_count--;
}

int ReferenceCounting::getRefCount()
{
	std::lock_guard<std::mutex> guard(mutex);
	return reference_count;
}
