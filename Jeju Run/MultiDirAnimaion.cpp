#include "DXUT.h"
#include "MultiDirAnimaion.h"

MultiDirAnimaion::MultiDirAnimaion(Object *target, string p, int frameNum, float fps, bool loop, bool isPng) : target(target), isFin(false), fps(fps)
{
	for (int i = 0; i < 16; i++)
	{
		ani[i] = new Animation(p + "/" + to_string(i), frameNum, fps, loop, isPng);
		ani[i]->parent = this;
		ani[i]->visible = false;
	}
	rect = visibleRect = ani[0]->rect;
}

MultiDirAnimaion::~MultiDirAnimaion()
{
	for (int i = 0; i < 16; i++)
	{
		SAFE_DELETE(ani[i]);
	}
}

void MultiDirAnimaion::update(float dt)
{
	Sprite::update(dt);

	for (int i = 0; i < 16; i++)
	{
		ani[i]->fps = fps;
		ani[i]->update(dt);
		ani[i]->visible = false;
	}

	float angle = D3DXToDegree(target->moveRotateion) - 180 - 22;
	while (angle < 0) angle += 360;
	int dir = angle / 22.5f;

	ani[dir]->visible = true;
	texture = ani[dir]->texture;
	isFin = ani[dir]->isFin;
}