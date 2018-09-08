#include "DXUT.h"
#include "UI.h"
#include "GameScene.h"
#include "World.h"
#include "GameManager.h"


UI::UI() : cnt(0), timer(1), isStageTextFadeIn(true), lapCnt(1), goToShop(false), goToEnd(false)
{
	if (gameManager.stage == 1)
		addChild(new Sprite("image/ui/0.png"));
	else 
		addChild(new Sprite("image/ui/1.png"));

	addChild(fightBarBack = new Sprite("image/effect/fight/back.png"));
	fightBarBack->visible = false;
	addChild(fightBar = new Sprite("image/effect/fight/front.png"));
	fightBar->visible = false;
	addChild(fightAni = new Animation("image/effect/fight", 1, 100, true, true));
	fightAni->visible = false;
	addChild(fightEffect = new Sprite("image/effect/fight/line.png"));
	fightEffect->color.a = 0;

	addChild(dashEffect = new Sprite("image/effect/dash/dash.png"));
	dashEffect->color.a = 0;

	addChild(staminaBar = new Sprite("image/ui/stamina.png"));
	staminaBar->pos = Vec2(28, 288);

	addChild(result = new Sprite("image/outgame/result.png"));
	result->visible = false;

	for (int i = 0; i < 3; i++)
	{
		addChild(itemBig[i] = new Sprite("image/ui/item/big/" + to_string(i) + ".png"));
		addChild(itemSmall[i] = new Sprite("image/ui/item/small/" + to_string(i) + ".png"));
		itemBig[i]->pos = Vec2(26, 151);
		itemSmall[i]->pos = Vec2(125, 151);
		itemBig[i]->visible = false;
		itemSmall[i]->visible = false;
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			addChild(speedText[i][j] = new Sprite("image/ui/speedNum/" + to_string(j) + ".png"));
			speedText[i][j]->pos = Vec2(1103 + i * 38, 647);
		}
	}
	for (int i = 0; i < 6; i++)
	for (int j = 0; j < 10; j++)
	{
		addChild(scoreText[i][j] = new Sprite("image/ui/scoreNum/" + to_string(j) + ".png"));
		if (gameManager.stage == 1)
			scoreText[i][j]->pos = Vec2(1147 + i * 17, 140);
		else
			scoreText[i][j]->pos = Vec2(1151 + i * 17, 22);
	}
	for (int i = 0; i < 4; i++)
	for (int j = 0; j < 10; j++)
	{
		addChild(distanceText[i][j] = new Sprite("image/ui/scoreNum/" + to_string(j) + ".png"));
		if (gameManager.stage == 1)
			distanceText[i][j]->pos = Vec2(1181 + i * 17, 170);
		else
			distanceText[i][j]->pos = Vec2(1185 + i * 17, 50);
	}

	for (int i = 0; i < 8; i++)
	for (int j = 0; j < 10; j++)
	{
		addChild(resultMoneyText[i][j] = new Sprite("image/ui/moneyNum/" + to_string(j) + ".png"));
		resultMoneyText[i][j]->pos = Vec2(366 + i * 17, 522);
		resultMoneyText[i][j]->visible = false;
	}

	for (int i = 0; i < 8; i++)
	for (int j = 0; j < 10; j++)
	{
		addChild(resultPrizeText[i][j] = new Sprite("image/ui/moneyNum/" + to_string(j) + ".png"));
		resultPrizeText[i][j]->pos = Vec2(784 + i * 17, 522);
		resultPrizeText[i][j]->visible = false;
	}

	for (int i = 0; i < 6; i++)
	for (int j = 0; j < 10; j++)
	{
		addChild(resultScoreText[i][j] = new Sprite("image/ui/scoreNum/" + to_string(j) + ".png"));
		resultScoreText[i][j]->pos = Vec2(588 + i * 17, 385);
		resultScoreText[i][j]->visible = false;
	}

	for (int i = 0; i < 4; i++)
	{
		addChild(rankText[i] = new Sprite("image/ui/rank/" + to_string(i) + ".png"));
		rankText[i]->pos = Vec2(20, 21);
	}
	
	for (int i = 0; i < 4; i++)
	{
		addChild(resultRankText[i] = new Sprite("image/ui/rank/" + to_string(i) + ".png"));
		resultRankText[i]->pos = Vec2(564, 197);
		resultRankText[i]->visible = false;
	}

	for (int i = 0; i < 10; i++)
	{
		addChild(lapText[i] = new Sprite("image/ui/scoreNum/" + to_string(i) + ".png"));
		lapText[i]->pos = Vec2(75, 669);
		lapText[i]->visible = false;
	}

	if(gameManager.stage == 1) addChild(stageText = new Sprite("image/ui/text/1stage.png"));
	else                       addChild(stageText = new Sprite("image/ui/text/2stage.png"));
	stageText->color.a = 0;
	stageText->setCenter(Vec2(1280, 720) / 2);
}

UI::~UI()
{
}

void UI::update(float dt)
{
	GameScene *scene = (GameScene*)world.currentScene;
	Entity::update(dt);

	fightBar->pos = scene->player->pos + scene->pos + Vec2(112, 314);
	fightBarBack->pos = scene->player->pos + scene->pos + Vec2(110, 312);
	fightAni->pos = Vec2(188, 334) + scene->player->pos + scene->pos;

	if (isStageTextFadeIn)
		stageText->color.a += dt;
	if (isStageTextFadeIn && stageText->color.a >= 1)
		isStageTextFadeIn = false;
	if (!isStageTextFadeIn)
		stageText->color.a -= dt;

	if (stageText->color.a <= 0 && !isStageTextFadeIn)
	{
		timer += dt;
		if (cnt < 4 && timer > 1.3f)
		{
			timer = 0;
			Sprite *spr = new Sprite("image/ui/text/count/" + to_string(cnt) + ".png");
			addChild(spr);
			spr->setCenter(Vec2(-500, 720 / 2));
			imgEffectList.push_back(spr);
			cnt++;
			if (cnt == 4)
			{
				for (auto& iter : scene->horseList)
					iter->ready = false;
			}
		}
	}

	for (auto iter = imgEffectList.begin(); iter != imgEffectList.end();)
	{
		float speed = abs(1280 / 2 - (*iter)->center().x);
		speed = speed < 400 ? 400 : speed;
		
		(*iter)->pos.x += dt * speed * 2;
		
		if (pos.x > 1280){
			removeChild(*iter);
			iter = imgEffectList.erase(iter);
		}
		else
			iter++;
	}

	int speedT = scene->player->speed / 20;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
			speedText[1 - i][j]->visible = false;
		speedText[1 - i][speedT % 10]->visible = true;
		speedT /= 10;
	}
	int disT = scene->player->distance;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
			distanceText[3 - i][j]->visible = false;
		distanceText[3 - i][disT % 10]->visible = true;
		disT /= 10;
	}
	int scoreT = gameManager.score;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 10; j++)
			scoreText[5 - i][j]->visible = false;
		scoreText[5 - i][scoreT % 10]->visible = true;
		scoreT /= 10;
	}

	if (!scene->player->isFin)
	{
		for (int i = 0; i < 4; i++)
			rankText[i]->visible = false;
		rankText[scene->player->rank - 1]->visible = true;
	}

	if (gameManager.stage == 1 && lapCnt == (scene->player->wpCnt - 1) / 8 && lapCnt < 5)
	{
		Sprite *spr = new Sprite("image/ui/text/lap/" + to_string(lapCnt - 1) + ".png");
		addChild(spr);
		spr->setCenter(Vec2(-500, 720 / 2));
		imgEffectList.push_back(spr);
		lapCnt++;
	}

	if (gameManager.stage == 1)
	{
		for (int i = 0; i < 10; i++)
			lapText[i]->visible = false;
		int t = (int)(scene->player->wpCnt - 1) / 8 + 1 > 5 ? 5 : (int)(scene->player->wpCnt - 1) / 8 + 1;
		lapText[t]->visible = true;
	}

	if (scene->player->isFin && scene->player->speed == 0)
	{
		result->visible = true;
		for (int i = 0; i < 4; i++)
			resultRankText[i]->visible = rankText[i]->visible;

		int moneyT = gameManager.money;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 10; j++)
				resultMoneyText[7 - i][j]->visible = false;
			resultMoneyText[7 - i][moneyT % 10]->visible = true;
			moneyT /= 10;
		}

		int scoreT = gameManager.score;
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 10; j++)
				resultScoreText[5 - i][j]->visible = false;
			resultScoreText[5 - i][scoreT % 10]->visible = true;
			scoreT /= 10;
		}

		int plusMoneyT = 0, p = 0;
		if (resultRankText[0]->visible)
			p = plusMoneyT = 1000000;
		else if (resultRankText[1]->visible)
			p = plusMoneyT = 500000;
		else if (resultRankText[2]->visible)
			p = plusMoneyT = 100000;

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 10; j++)
				resultPrizeText[7 - i][j]->visible = false;
			resultPrizeText[7 - i][plusMoneyT % 10]->visible = true;
			plusMoneyT /= 10;
		}

		if (world.getKeyState(VK_RETURN) == 1)
		{
			if (gameManager.stage == 1)
			{
				if (resultRankText[0]->visible)
				{
					gameManager.money += p;
					goToShop = true;
				}
				else
				{
					gameManager.win = false;
					goToEnd = true;
				}
			}
			else
			{
				if (resultRankText[0]->visible)
				{
					gameManager.win = true;
					goToEnd = true;
				}
				else 
				{
					gameManager.win = false;
					goToEnd = true;
				}
			}
		}
	}
}

void UI::render()
{
	Entity::render();
	fightEffect->render();
	dashEffect->render();
	result->render();
	for (int i = 0; i < 4; i++)
		resultRankText[i]->render();	
	for (int i = 0; i < 6; i++)
	for (int j = 0; j < 10; j++)
		resultScoreText[i][j]->render();
	for (int i = 0; i < 8; i++)
	for (int j = 0; j < 10; j++)
		resultMoneyText[i][j]->render();
	for (int i = 0; i < 8; i++)
	for (int j = 0; j < 10; j++)
		resultPrizeText[i][j]->render();
}