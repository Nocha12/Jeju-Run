#pragma once
#include "Scene.h"
#include "Animation.h"

class LoadScene :
	public Scene
{
public:
	LoadScene();
	~LoadScene();

	Sprite *bar;
	Animation *ani;
	Animation *op;
	void update(float dt);
};

