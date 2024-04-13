#pragma once
#include <iostream>

class Big_Data
{
public:
	Big_Data(int buf_size);
	~Big_Data();
	Big_Data(const Big_Data& big_data);
	Big_Data& operator = (const Big_Data& big_data);
	Big_Data(Big_Data&& big_data);
	Big_Data& operator=(Big_Data&& other);

private:
	int* _buffer;
	int _buf_size;
};

