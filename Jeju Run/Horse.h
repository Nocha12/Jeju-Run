#pragma once
#include "Obejct.h"
#include "Animation.h"
#include "Timer.h"

class Horse :
	public Object
{
public:
	Horse(HorseType horseType);
	~Horse();

	void update(float dt);

	HorseType type;
	
	float lineDis;
	Vec2 linePos;

	bool init; 
	bool isRightTurn;

	float speed;
	float maxSpeed;
	int dir;

	bool turnRight;
	bool turnLeft;
	bool dash;
	bool booster;
	bool barrier;
	bool barrierFadeIn;

	float barrierTimer;
	float boosterTimer;

	bool isAI;
	float aiTimer;
	float aiItemTimer;
	float aiItemDelay;
	float aiTurnDelay;
	float aiDashDelay;
	float aiPattern;

	int plusSpeed;
	int plusMaxSpeed;
	int plusStamina;
	int	power;

	bool crash;

	int colRange; 
	float fightDelay;
	bool fighting;

	bool isStun;
	bool isFall;
	bool isJump;
	
	bool ready;

	list<ItemType> items;
	Timer redTimer;

	float gravity;
	float jump;

	map<AnimaionType, Sprite*> animation;

	Sprite *barrierEffect;
	Sprite *dashEffect;
	Animation *boosterEffect;

	void GetRed();
	void UseItem(ItemType type);
	void ChangeAni(AnimaionType type, bool reset = false);

	list<WayPoint>::iterator nextPoint;
	float wpCnt;
	int rank;
	
	bool isFin;

	float dustTimer;
};

