#include "DXUT.h"
#include "Item.h"
#include "World.h"
#include "GameScene.h"
#include "GameManager.h"
#include "Particle.h"

Item::Item() : timer(0), init(false)
{
	addChild(ani = new Animation("image/map/item", 10, 10, true, true));
	rect = ani->rect;
}

Item::~Item()
{
}

void Item::update(float dt)
{
	GameScene *scene = (GameScene*)world.currentScene;
	Entity::update(dt);
	
	if (!init)
	{
		init = true;
		scene->ui->addChild(minimapImg = new Sprite("image/ui/minimap/item.png"));
	}
	if (gameManager.stage == 1)
		minimapImg->setCenter(Vec2(1030, 20) + center() / 30); 
	else
		minimapImg->setCenter(Vec2(161 + center().x / 52, 646 + (center().y - 1825) / 20));

	for (auto& iter : scene->horseList)
	{
		if (pita(iter->GetCollisionPos(), center()) < 30 + iter->colRange && visible)
		{
			minimapImg->visible = false;
			visible = false;
			if (iter->items.size() < 2)
				iter->items.push_back((ItemType)random(0, 2));
			for (int i = 0; i < 10; i++)
			{
				Particle *p = new Particle();
				iter->addChild(p);
				p->setCenter(iter->rect.center());
				scene->particleList.push_back(p);
			}
			Sprite *ring = new Sprite("image/effect/item/ring.png");
			iter->addChild(ring);
			ring->setCenter(iter->rect.center());
			scene->ringList.push_back(ring);
			ring->scaleCenter = ring->rect.center();

			if (!iter->isAI){
				int t = random(0, 3);
				Sprite *moneyT = new Sprite("image/ui/money/" + to_string(t) + ".png");
				iter->addChild(moneyT);
				moneyT->setCenter(iter->rect.center());
				scene->textEffectList.push_back(moneyT);
				if (t == 0)
					gameManager.money += 100000;
				if (t == 1)
					gameManager.money += 300000;
				if (t == 2)
					gameManager.money += 500000;
				if (t == 3)
					gameManager.money += 1000000;
			}
		}
	}

	if (!visible)
	{
		timer += dt;
		if (timer > 5)
		{
			timer = 0;
			visible = true;
			minimapImg->visible = true;
		}
	}
}