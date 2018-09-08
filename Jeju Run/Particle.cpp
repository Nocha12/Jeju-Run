#include "DXUT.h"
#include "Particle.h"
#include "GameScene.h"
#include "World.h"

Particle::Particle()
{
	addChild(spr = new Sprite("image/effect/item/star.png"));
	dir = random(0.0, D3DXToRadian(360));
	speed = random(300, 600);
	rect = spr->rect;
	rotateionCenter = rect.center();
}

Particle::~Particle()
{
}

void Particle::update(float dt)
{
	Entity::update(dt);

	pos += Vec2(cos(dir), sin(dir)) * speed * dt;
	rotateion += dt * 10;
	spr->color.a -= dt * 3;

	if (spr->color.a <= 0)
	{
		removeChild(this);
		((GameScene*)world.currentScene)->particleList.remove(this);
	}
}