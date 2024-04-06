#pragma once
#include <iostream>
#include <chrono>
#include <mutex>

class ReferenceCounting
{
public:
	ReferenceCounting();
	~ReferenceCounting();
	void addRef();
	void removeRef();
	int getRefCount();

private:
	int reference_count;
	std::mutex mutex;
};

