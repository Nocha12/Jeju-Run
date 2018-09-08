#pragma once
#include "Entity.h"
#include "Sprite.h"

class Object :
	public Entity
{
public:
	Object();
	~Object();

	float moveRotateion;
	Vec2 GetCollisionPos();
	void SetCollisionPos(Vec2 p);
	Vec2 colPos;
	Sprite *minimapImg;
};

