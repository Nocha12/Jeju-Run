#pragma once
#include "Entity.h"
#include "Sprite.h"

class Particle :
	public Entity
{
public:
	Particle();
	~Particle();

	float dir;
	float speed;
	Sprite *spr; 

	void update(float dt);
};

