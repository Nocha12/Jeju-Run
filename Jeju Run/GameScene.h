#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Player.h"
#include "UI.h"
#include "Item.h"
#include "Particle.h"
#include "Obstacle.h"

class GameScene :
	public Scene
{
public:
	GameScene();
	~GameScene();
	
	void update(float dt);
	void render();

	Vec2 turnPos[2];

	Player *player;
	Sprite *map;
	Sprite *stage[24];
	Sprite *front[24];
	Sprite *wave[24];
	Sprite *waveBack[24];
	Sprite *up;
	Sprite *down;

	UI *ui;

	list<Horse*> horseList;
	list<Item*> itemList;
	list<Particle*> particleList;
	list<Sprite*> ringList;
	list<Sprite*> dustList;
	list<Sprite*> textEffectList;
	list<Obstacle*> obstacleList;
	list<WayPoint> wayPoints;

	float cnt;
};

