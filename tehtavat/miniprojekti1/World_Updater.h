#pragma once
#include "Game_Task.h"
#include <iostream>

class World_Updater : public Game_Task
{
public:
	void perform() override;
};