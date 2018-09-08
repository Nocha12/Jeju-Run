#pragma once
#include "Scene.h"
#include "Timer.h"
#include "Define.h"

class World
{
public:
	World();
	~World();

	void init();
	void dispose();
	void update(float dt);
	void render();
	
	int getKeyState(int vk);
	void changeScene(Scene *scene);
	Vec2 getMousePos();
	float timeScale;
	bool currentKey[256];
	bool lastKey[256];
	POINT mouseP;
	Scene* currentScene;
	LPD3DXSPRITE rootSprite;

	list<Timer*> timers;
};

extern World world;