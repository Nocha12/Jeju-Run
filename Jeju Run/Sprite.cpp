#include "DXUT.h"
#include "Sprite.h"
#include "World.h"
#include "Asset.h"

Sprite::Sprite() : color(1, 1, 1, 1), texture(nullptr)
{
}

Sprite::Sprite(path p) : color(1, 1, 1, 1), texture(nullptr)
{
	setPath(p);
}

Sprite::~Sprite()
{
}

void Sprite::setPath(path p)
{
	texture = asset.getTexture(p);
	rect = visibleRect = Rect(0, 0, texture->info.Width, texture->info.Height);
}

void Sprite::render()
{
	if (!visible || !texture) return;
	Entity::render();
	world.rootSprite->Begin(D3DXSPRITE_ALPHABLEND);
	world.rootSprite->SetTransform(&matrix);
	world.rootSprite->Draw(texture->d3dTexture, &visibleRect, NULL, NULL, color);
	world.rootSprite->End();
}