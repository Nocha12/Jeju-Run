#pragma once
#include "Scene.h"
#include "Sprite.h"

class SelectScene :
	public Scene
{
public:
	SelectScene();
	~SelectScene();

	Sprite *frame;
	Sprite *back1;
	Sprite *back2;

	void update(float dt);
};

