#pragma once
#include "Enum.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	
	int stage;
	int score;
	int money;

	bool item1;
	bool item2;
	bool item3;

	bool win;

	HorseType type;

	void init();
};

extern GameManager gameManager;

