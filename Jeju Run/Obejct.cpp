#include "DXUT.h"
#include "Obejct.h"

Object::Object() : colPos(0, 0), moveRotateion(0)
{
}

Object::~Object()
{
}

Vec2 Object::GetCollisionPos()
{
	return pos + colPos;
}

void Object::SetCollisionPos(Vec2 p)
{
	pos = p - colPos;
}