#pragma once
#include "Sprite.h"

class Animation :
	public Sprite
{
public:
	Animation(string p, int frameNum, float fps, bool loop = true, bool isPng = false);
	~Animation();

	void update(float dt);
	float fps;
	float currentFrame;
	bool loop;
	bool isFin;
	bool stop;

	vector<Texture*> textures;
};

