#include "DXUT.h"
#include "Entity.h"

Entity::Entity() : 
parent(nullptr),
pos(0, 0),
rotateion(0),
rotateionCenter(0, 0),
scale(1, 1),
scaleCenter(0, 0),
rect(0, 0, 0, 0),
visibleRect(0, 0, 0, 0),
visible(true),
renderChild(true),
removing(false)
{
}

Entity::~Entity()
{
	for (auto& iter : children)
		SAFE_DELETE(iter);
}

void Entity::update(float dt)
{
	for (auto& iter : children)
		iter->update(dt);

	for_iter(iter, children)
	{
		if ((*iter)->removing)
		{
			SAFE_DELETE(*iter);
			iter = children.erase(iter);
			if (iter == children.end())
				break;
		}
	}
}

void Entity::render()
{
	if (!visible) return;

	D3DXMatrixTransformation2D(&matrix, &scaleCenter, 0, &scale, &rotateionCenter, rotateion, &pos);

	if (parent)
		matrix *= parent->matrix;
	if (!renderChild) return;
	for (auto& iter : children)
		iter->render();
}

void Entity::addChild(Entity *e)
{
	children.push_back(e);
	e->parent = this;
}

void Entity::removeChild(Entity *e)
{
	e->removing = true;
}

void Entity::setCenter(Vec2 p)
{
	pos = p - rect.center();
}

Vec2 Entity::center()
{
	return pos + rect.center();
}

Rect Entity::rectWidthPos()
{
	return rect.offset(pos);
}