#include "DXUT.h"
#include "GameScene.h"
#include "World.h"
#include "GameManager.h"
#include "ShopScene.h"
#include "EndScene.h"

GameScene::GameScene() : cnt(0)
{
	ui = new UI;

	bool types[5] = { false, };

	if (gameManager.stage == 1)
	{
		addChild(map = new Sprite("image/map/1/0.png"));
		addChild(down = new Sprite("image/map/1/down.png"));
		addChild(up = new Sprite("image/map/1/up.png"));
		up->pos = Vec2(660, 1163);

		turnPos[0] = Vec2(1068, 1700);
		turnPos[1] = Vec2(5732, 1700);

		addChild(player = new Player(gameManager.type));
		types[gameManager.type] = true;

		player->SetCollisionPos(Vec2(3200, 2265 + 132 * 3));
		player->lineDis = 560 + 132 * 3;
		follow(player);
		horseList.push_back(player);
		for (int i = 0; i < 3; i++)
		{
			int r = random(0, 4);
			while (types[r])
				r = random(0, 4);
			types[r] = true;
			Horse *h = new Horse(HorseType(r));
			addChild(h);
			h->SetCollisionPos(Vec2(3200, 2265 + 132 * i));
			h->lineDis = 560 + 132 * i;
			horseList.push_back(h);
		}

		for (int i = 0; i < 8; i++)
		{
			Item *item = new Item();
			addChild(item);
			itemList.push_back(item);
			if (i < 4)
				item->setCenter(Vec2(2000, 746 + 132 * i));
			else
				item->setCenter(Vec2(5000, 2245 + 132 * (i - 4)));
		}

		wayPoints.push_back(WayPoint(Vec2(3435, 2155), Vec2(3435, 2797)));
		wayPoints.push_back(WayPoint(Vec2(5683, 2155), Vec2(5683, 2797)));
		wayPoints.push_back(WayPoint(Vec2(6146, 1701), Vec2(6759, 2797)));
		wayPoints.push_back(WayPoint(Vec2(5683, 653), Vec2(5683, 1234)));
		wayPoints.push_back(WayPoint(Vec2(5683, 653), Vec2(5683, 1234)));
		wayPoints.push_back(WayPoint(Vec2(1113, 653), Vec2(1113, 1234)));
		wayPoints.push_back(WayPoint(Vec2(48, 1701), Vec2(667, 2797)));
		wayPoints.push_back(WayPoint(Vec2(1113, 2155), Vec2(1113, 2797)));
	}
	else
	{
		addChild(stage[0] = new Sprite("image/map/2/stage/0.png"));
		for (int i = 1; i < 23; i++)
		{
			if (random(0, 5) == 0)
				addChild(stage[i] = new Sprite("image/map/2/stage/1.png"));
			else
				addChild(stage[i] = new Sprite("image/map/2/stage/2.png"));
			stage[i]->pos = Vec2(i * 2000, 0);
		}
		addChild(stage[23] = new Sprite("image/map/2/stage/3.png"));
		stage[23]->pos = Vec2(23 * 2000, 0);

		for (int i = 0; i < 24; i++)
		{
			addChild(front[i] = new Sprite("image/map/2/front/" + to_string(i % 4) + ".png"));
			front[i]->pos = Vec2(i * 2000, 0); 
		}

		for (int i = 0; i < 24; i++)
		{
			addChild(front[i] = new Sprite("image/map/2/front/" + to_string(i % 4) + ".png"));
			front[i]->pos = Vec2(i * 2000, 0);
		}

		for (int i = 0; i < 24; i++)
		{
			addChild(wave[i] = new Sprite("image/map/2/wave/0.png"));
			wave[i]->pos = Vec2(i * 2000, 2570);
			addChild(waveBack[i] = new Sprite("image/map/2/wave/1.png"));
			waveBack[i]->pos = Vec2(i * 2000, 2570);
		}

		for (int i = 0; i < 24; i++)
			wayPoints.push_back(WayPoint(Vec2(1426 + i * 2000, 1901), Vec2(1426 + i * 2000, 2507)));

		turnPos[0] = Vec2(-10000, 0);
		turnPos[1] = Vec2(100000, 0);
		types[gameManager.type] = true;
		addChild(player = new Player(gameManager.type));
		player->SetCollisionPos(Vec2(285, 2015 + 126 * 3));
		player->lineDis = 2015 + 126 * 3;
		follow(player);
		horseList.push_back(player);
		for (int i = 0; i < 3; i++)
		{
			int r = random(0, 4);
			while (types[r])
				r = random(0, 4);
			types[r] = true;
			Horse *h = new Horse(HorseType(r));
			addChild(h);
			h->SetCollisionPos(Vec2(285, 2015 + 126 * i));
			h->lineDis = 2015 + 126 * i;
			horseList.push_back(h);
		}

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Item *item = new Item();
				addChild(item);
				itemList.push_back(item);
				item->setCenter(Vec2(1000 + 6000 * i, 1965 + 126 * j));
			}

			for (int j = 0; j < 4; j++)
			{
				Obstacle *o = new Obstacle(false);
				addChild(o);
				obstacleList.push_back(o);
				o->setCenter(Vec2(random(1000, 5000) + 6000 * i, 2005 + 126 * j));
			}
		}
	}

	renderChild = false;
}

GameScene::~GameScene()
{
	SAFE_DELETE(ui);
}

void GameScene::update(float dt)
{
	ui->update(dt);
	Scene::update(dt);

	if (world.getKeyState('A') == 1)
	for (auto& iter : horseList)
		iter->ready = false;

	if (gameManager.stage == 1)
	{
		if (pos.x > 0) pos.x = 0;
		if (pos.y > 0) pos.y = 0;
		if (pos.x < -6900 + 1280) pos.x = -6900 + 1280;
		if (pos.y < -3400 + 720) pos.y = -3400 + 720;
	}
	else {
		if (pos.x > 0) pos.x = 0;
		if (pos.x < -48000 + 1280) pos.x = -48000 + 1280;
	}

	for_iter(iter, dustList)
	{
		(*iter)->rotateion += dt * 5;
		(*iter)->scale -= Vec2(dt, dt);
		(*iter)->color.a -= 1.5f * dt;
		if ((*iter)->color.a <= 0)
		{
			removeChild(*iter);
			iter = dustList.erase(iter);
			if (iter == dustList.end())
				break;
		}
	}
	for_iter(iter, ringList)
	{
		(*iter)->rotateion += dt * 2;
		(*iter)->scale += Vec2(dt * 5, dt * 5);
		(*iter)->color.a -= dt * 3;
		if ((*iter)->color.a <= 0)
		{
			removeChild(*iter);
			iter = ringList.erase(iter);
			if (iter == ringList.end())
				break;
		}
	}
	for_iter(iter, textEffectList)
	{
		(*iter)->pos.y -= dt * 100;
		(*iter)->color.a -= dt;
		if ((*iter)->color.a <= 0)
		{
			removeChild(*iter);
			iter = textEffectList.erase(iter);
			if (iter == textEffectList.end())
				break;
		}
	}

	horseList.sort([](Horse *h1, Horse *h2){
		if (h1->wpCnt == h2->wpCnt)
			return h1->nextPoint->Distance(h1->GetCollisionPos()) < h2->nextPoint->Distance(h2->GetCollisionPos());
		else
			return h1->wpCnt > h2->wpCnt;
	});

	int rank = 1;
	for (auto& iter : horseList)
		iter->rank = rank++;

	if (gameManager.stage == 2)
	{
		cnt += dt;
		for (int i = 0; i < 24; i++)
		{
			wave[i]->pos.y = 2570 + sin(cnt) * 40;
			waveBack[i]->pos.y = 2570 + sin(cnt + 5) * 40;
		}
	}

	if (ui->goToShop)
	{
		world.changeScene(new ShopScene());
		return;
	}
	if (ui->goToEnd)
	{
		world.changeScene(new EndScene());
		return;
	}
}
void GameScene::render()
{
	Scene::render();
	if (gameManager.stage == 1)
	{
		map->render();
		down->render();
	}
	else
	for (int i = 0; i < 24; i++)
		stage[i]->render();
	for (auto& iter : dustList)
		iter->render();
	for (auto& iter : itemList)
		iter->render();
	for (auto& iter : obstacleList)
		iter->render();
	horseList.sort([](Object *o1, Object *o2){
		return o1->GetCollisionPos().y < o2->GetCollisionPos().y;
	});
	for (auto& iter : horseList)
		iter->render();
	for (auto& iter : ringList)
		iter->render();
	for (auto& iter : particleList)
		iter->render();
	if (gameManager.stage == 2)
	{
		for (int i = 0; i < 24; i++)
			waveBack[i]->render();
		for (int i = 0; i < 24; i++)
			wave[i]->render();
	}

	if (gameManager.stage == 1)
		up->render();
	else
	for (int i = 0; i < 24; i++)
		front[i]->render();
	ui->render();
}