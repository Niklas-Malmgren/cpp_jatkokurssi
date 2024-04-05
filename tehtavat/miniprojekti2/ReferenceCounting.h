#pragma once
#include <iostream>
#include <chrono>

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
};

