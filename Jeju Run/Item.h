#pragma once
#include "Entity.h"
#include "Animation.h"

class Item :
	public Entity
{
public:
	Item();
	~Item();

	Animation *ani;

	void update(float dt);
	
	Sprite *minimapImg;
	float timer;
	bool init;
};

