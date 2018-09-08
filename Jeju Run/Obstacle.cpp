#include "DXUT.h"
#include "Obstacle.h"
#include "GameScene.h"
#include "World.h"
#include "MultiDirAnimaion.h"
#include "GameManager.h"

Obstacle::Obstacle(bool isDoldam) : init(false)
{
	if (isDoldam)
		addChild(spr = new MultiDirAnimaion(this, "image/map/obstacle/doldam", 0, 0));
	else
		addChild(spr = new Sprite("image/map/obstacle/hurdle.png"));

	rect = spr->rect;
	if (isDoldam)
		colPos = Vec2(146, 163);
	else
		colPos = Vec2(25, 119);
}

Obstacle::~Obstacle()
{
}

void Obstacle::update(float dt)
{
	GameScene *scene = (GameScene*)world.currentScene;
	Object::update(dt);

	if (!init)
	{
		init = true;
		scene->ui->addChild(minimapImg = new Sprite("image/ui/minimap/obstacle.png"));
	}
	if (gameManager.stage == 1)
		minimapImg->setCenter(Vec2(1030, 20) + center() / 30);
	else
		minimapImg->setCenter(Vec2(161 + center().x / 52, 646 + (center().y - 1825) / 20));

	for (auto& iter : scene->horseList)
	{
		if (pita(iter->GetCollisionPos(), GetCollisionPos()) < 30 + iter->colRange && !timer.active && !removing && !iter->isJump)
		{
			if (iter->isAI && random(0, 2) == 0 && gameManager.stage == 2)
			{
				iter->gravity = -300;
				iter->isJump = true;
				continue;
			}

			removeChild(minimapImg);
			timer.reset(0.01, 25);
			spr->color = D3DXCOLOR(1, 0, 0, 1);
			timer.onTick = [=](){
				spr->color.a -= 0.04;
				spr->color.g -= 0.04;
				spr->color.b -= 0.04;
			};
			timer.onFin = [=](){
				scene->obstacleList.remove(this);
				scene->removeChild(this);
			};
			iter->GetCollisionPos();

			if (!iter->barrier){
				iter->isFall = true;
				iter->GetRed();
			}
			if (!iter->isAI)
				scene->shake(0.01, 4, 20);
		}
	}
}
