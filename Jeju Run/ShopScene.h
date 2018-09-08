#pragma once
#include "Scene.h"
#include "Sprite.h"

class ShopScene :
	public Scene
{
public:
	ShopScene();
	~ShopScene();

	Sprite *btn1;
	Sprite *btn2;
	Sprite *btn3;

	Sprite *moneyText[8][10];

	void update(float dt);
};

