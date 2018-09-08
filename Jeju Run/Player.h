#pragma once
#include "Horse.h"
class Player : public Horse
{
public:
	Player(HorseType type);
	~Player();

	void update(float dt);

	Horse *target;

	float staminaDelay;

	float fightGage;
	float stamina;
	float maxStamina;
	float distance;
};

