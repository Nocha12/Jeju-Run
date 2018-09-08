#pragma once
#include "Entity.h"
#include "Animation.h"
#include "Sprite.h"

class UI :
	public Entity
{
public:
	UI();
	~UI();

	Sprite *fightBar;
	Sprite *fightAni;
	Sprite *fightBarBack;
	Sprite *fightEffect;
	Sprite *dashEffect;

	Sprite *rankText[4];
	Sprite *speedText[2][10];
	Sprite *scoreText[6][10];
	Sprite *distanceText[4][10];
	Sprite *lapText[10];
	Sprite *staminaBar;

	Sprite *itemBig[3];
	Sprite *itemSmall[3];

	Sprite *stageText;

	list<Sprite*> imgEffectList;

	Sprite *result;
	Sprite *resultRankText[4];
	Sprite *resultScoreText[6][10];
	Sprite *resultMoneyText[8][10];
	Sprite *resultPrizeText[8][10];

	float timer;
	int cnt;
	int lapCnt;

	bool isStageTextFadeIn;

	bool goToShop;
	bool goToEnd;

	void update(float dt);
	void render();
};

