#pragma once
#include "Scene.h"
#include "Animation.h"

class MainScene :
	public Scene
{
public:
	MainScene();
	~MainScene();

	void update(float dt);

	Sprite *title;
	Sprite *startB;
	Sprite *howToB;
	Sprite *introB;
	Sprite *exitB;
	Sprite *howToEx[3];
	Sprite *introEx;

	int howToCnt;
};

