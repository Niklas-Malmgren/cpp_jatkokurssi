#pragma once
#include <iostream>
#include <chrono>
#include "ReferenceCounting.h"

template <class T>
class Log_Ptr
{
public:
	Log_Ptr(T* i);
	~Log_Ptr();
	Log_Ptr(const Log_Ptr<T>& log_ptr);
	Log_Ptr<T>& operator = (const Log_Ptr<T>& log_ptr);
	T* operator-> ();
	T& operator* ();

private:
	T* _i;
	ReferenceCounting* rc;
};

template<class T>
inline Log_Ptr<T>::Log_Ptr(T* i)
{
	rc = new ReferenceCounting();
	rc->addRef();

	_i = i;
	std::cout << std::format("{:%T}", std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now())) << "\tOmistajuus sirretty: " << &_i << "\n";
}

template<class T>
inline Log_Ptr<T>::~Log_Ptr()
{
	rc->removeRef();

	if (rc->getRefCount() <= 0)
	{
		delete _i;
		delete rc;
		std::cout << std::format("{:%T}", std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now())) << "\tOlio tuhottu: " << &_i << "\n";
	}
}


template<class T>
inline Log_Ptr<T>::Log_Ptr(const Log_Ptr<T>& log_ptr) : _i(log_ptr._i), rc(log_ptr.rc)
{
	rc->addRef();
	std::cout << std::format("{:%T}", std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now())) << "\tOlio Kopioitu: " << &_i << "\n";
}

template<class T>
inline Log_Ptr<T>& Log_Ptr<T>::operator=(const Log_Ptr<T>& log_ptr)
{
	if (this != &log_ptr)
	{
		rc->removeRef();

		if (rc->getRefCount() == 0)
		{
			delete _i;
			delete rc;
		}

		_i = log_ptr._i;
		rc = log_ptr.rc;
		rc->addRef();
	}

	std::cout << std::format("{:%T}", std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now())) << "\tOperator= " << &_i << "\n";
	return *this;
}


template<class T>
inline T* Log_Ptr<T>::operator->()
{
	std::cout << std::format("{:%T}", std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now())) << "\tOperator-> " << &_i << "\n";
	return _i;
}

template<class T>
inline T& Log_Ptr<T>::operator*()
{
	std::cout << std::format("{:%T}", std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now())) << "\tOperator* " << &_i << "\n";
	return *_i;
}

