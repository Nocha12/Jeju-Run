#pragma once
#include "Timer.h"
#include "Entity.h"

class Scene :
	public Entity
{
public:
	Scene();
	~Scene();

	void update(float dt);

	void follow(Entity *t);
	void shake(float d, int c, float range);

	Timer timer;
	Entity *target;
};

