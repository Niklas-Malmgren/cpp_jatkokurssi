#pragma once
#include "Game_Task.h"
#include <iostream>

class AI : public Game_Task
{
public: 
	void perform() override;
};

