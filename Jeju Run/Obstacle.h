#pragma once
#include "Obejct.h"
#include "Sprite.h"
#include "Timer.h"

class Obstacle :
	public Object
{
public:
	Obstacle(bool isDoldam);
	~Obstacle();

	Timer timer;
	Sprite *spr;
	
	bool init;

	void update(float dt);
};

