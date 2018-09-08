#pragma once
#include "Define.h"

class Entity
{
public:
	Entity();
 	virtual ~Entity();

	virtual void update(float dt);
	virtual void render();
	void addChild(Entity *e);
	void removeChild(Entity *e);

	void setCenter(Vec2 p);
	Vec2 center();
	Rect rectWidthPos();

	Entity *parent;
	list<Entity *>children;
	D3DXMATRIX matrix;
	Vec2 pos;
	float rotateion;
	Vec2 rotateionCenter;
	Vec2 scale;
	Vec2 scaleCenter;
	Rect rect;
	Rect visibleRect;
	bool visible;
	bool renderChild;
	bool removing;
};

