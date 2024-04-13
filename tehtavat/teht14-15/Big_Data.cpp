#include "Big_Data.h"

Big_Data::Big_Data(int buf_size)
{
	_buf_size = buf_size;
	_buffer = (int*) malloc(_buf_size);
}

Big_Data::~Big_Data()
{
	free(_buffer);
}

Big_Data::Big_Data(const Big_Data& big_data)
{
	_buf_size = big_data._buf_size;
	_buffer = (int*)malloc(_buf_size);
	std::memcpy(_buffer, big_data._buffer, _buf_size);
}

Big_Data& Big_Data::operator=(const Big_Data& big_data)
{
	_buf_size = big_data._buf_size;
	std::memcpy(_buffer, big_data._buffer, _buf_size);
	return *this;
}

Big_Data::Big_Data(Big_Data&& big_data)
{
	_buf_size = big_data._buf_size;
	_buffer = big_data._buffer;

	big_data._buffer = nullptr;
	big_data._buf_size = 0;
}

Big_Data& Big_Data::operator=(Big_Data&& big_data)
{
	_buf_size = big_data._buf_size;
	_buffer = big_data._buffer;

	big_data._buffer = nullptr;
	big_data._buf_size = 0;

	return *this;
}
