#pragma once
#include "Scene.h"
#include "Animation.h"

class EndScene :
	public Scene
{
public:
	EndScene();
	~EndScene();
	
	void update(float dt);

	Animation *ed;
	Sprite *spr;
};

