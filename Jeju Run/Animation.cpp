#include "DXUT.h"
#include "Animation.h"
#include "Asset.h"

Animation::Animation(string p, int frameNum, float fps, bool loop, bool isPng) : fps(fps), currentFrame(0), loop(loop), isFin(false), stop(false)
{
	for (int i = 0; i <= frameNum; i++)
	{
		if (isPng)
			textures.push_back(asset.getTexture(p + "/" + to_string(i) + ".png"));
		else
			textures.push_back(asset.getTexture(p + "/" + to_string(i) + ".dds"));
	}

	texture = textures[0];
	rect = visibleRect = Rect(0, 0, texture->info.Width, texture->info.Height);
}

Animation::~Animation()
{
}

void Animation::update(float dt)
{
	if (stop) return;
	Sprite::update(dt);

	currentFrame += fps * dt;

	if (currentFrame >= textures.size())
	{
		if (loop) currentFrame = 0;
		else { currentFrame = textures.size() - 1; isFin = true; }
	}

	texture = textures[(int)currentFrame];
}