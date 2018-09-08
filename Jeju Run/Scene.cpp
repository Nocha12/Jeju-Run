#include "DXUT.h"
#include "Scene.h"

Scene::Scene() : target(nullptr)
{
}

Scene::~Scene()
{
}

void Scene::follow(Entity *t)
{
	target = t;
}

void Scene::shake(float d, int c, float range)
{
	timer.reset(d, c);
	timer.onTick = [=](){
		pos += Vec2(random(-range, range), random(-range, range));
	};
}

void Scene::update(float dt)
{
	Entity::update(dt);

	if (target)
	{
		scaleCenter = target->center();
		pos += (-target->center() + Vec2(1280, 720) / 2 - pos) * 0.15;
	}
}
