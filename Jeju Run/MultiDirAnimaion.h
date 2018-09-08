#pragma once
#include "Animation.h"
#include "Obejct.h"

class MultiDirAnimaion :
	public Sprite
{
public:
	MultiDirAnimaion(Object *target, string p, int frameNum, float fps, bool loop = true, bool isPng = false);
	~MultiDirAnimaion();

	void update(float dt);

	float fps;
	Object *target;
	Animation *ani[16];
	bool isFin;
};

