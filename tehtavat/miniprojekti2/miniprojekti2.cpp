#include <iostream>

#include "TestClass.h"
#include "Log_Ptr.h"

std::shared_ptr<TestClass> foo(std::shared_ptr<TestClass> ptr)
{
    return ptr;
}

int main()
{
    TestClass* testClass = new TestClass;
    Log_Ptr<TestClass> log_ptr(testClass);

    TestClass* testClass2 = new TestClass;
    Log_Ptr<TestClass> log_ptr2(testClass2);

    TestClass* testClass3 = new TestClass;
    Log_Ptr<TestClass> log_ptr3(testClass3);

    log_ptr = log_ptr2;

    Log_Ptr<TestClass> log_ptr4 = log_ptr2;

    log_ptr = log_ptr3;
    log_ptr2 = log_ptr3;
    log_ptr4 = log_ptr3;
}

