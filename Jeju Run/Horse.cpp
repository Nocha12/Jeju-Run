#include "DXUT.h"
#include "Horse.h"
#include "World.h"
#include "GameScene.h"
#include "MultiDirAnimaion.h"
#include "Player.h"
#include "GameManager.h"

Horse::Horse(HorseType horseType) : type(horseType), init(false), lineDis(0), isRightTurn(false), speed(0), maxSpeed(1000), dir(0),
turnRight(false), turnLeft(false), dash(false), booster(false), barrier(false), barrierTimer(0), boosterTimer(0), isFin(false), dustTimer(0),
isAI(true), aiTimer(false), aiTurnDelay(0), aiDashDelay(0), plusSpeed(0), plusStamina(0), power(3), aiPattern(0), aiItemDelay(random(3, 10)), aiItemTimer(0), plusMaxSpeed(0),
fightDelay(0), colRange(0), fighting(false), isStun(false), isFall(false), ready(true), barrierFadeIn(true), jump(0), isJump(false), gravity(300), rank(1), wpCnt(0)
{
	addChild(animation[IDLE] = new MultiDirAnimaion(this, "image/player/" + to_string(type) + "/stop", 0, 0)); 
	rect = animation[IDLE]->rect;
	addChild(animation[WALK] = new MultiDirAnimaion(this, "image/player/" + to_string(type) + "/walk", 11, 16));
	animation[WALK]->visible = false;
	addChild(animation[RUN] = new MultiDirAnimaion(this, "image/player/" + to_string(type) + "/run", 11, 16));
	animation[RUN]->visible = false;
	addChild(animation[STUN] = new MultiDirAnimaion(this, "image/player/" + to_string(type) + "/holol", 15, 16, false));
	animation[STUN]->visible = false;
	addChild(animation[FALL] = new MultiDirAnimaion(this, "image/player/" + to_string(type) + "/fall", 10, 12, false));
	animation[FALL]->visible = false;
	addChild(animation[JUMP] = new MultiDirAnimaion(this, "image/player/" + to_string(type) + "/jump", 20, 20, false));
	animation[JUMP]->visible = false;

	colPos = Vec2(260, 322);
	colRange = 45;

	addChild(dashEffect = new Sprite("image/effect/dash/0.png"));
	addChild(boosterEffect = new Animation("image/effect/booster", 2, 15, true, true));
	addChild(barrierEffect = new Sprite("image/effect/berrier.png"));
	dashEffect->rotateionCenter = dashEffect->rect.center();
	boosterEffect->rotateionCenter = boosterEffect->rect.center();
	barrierEffect->rotateionCenter = barrierEffect->rect.center();
	dashEffect->setCenter(rect.center());
	boosterEffect->setCenter(rect.center());
	barrierEffect->setCenter(rect.center());
	dashEffect->color.a = 0;
	boosterEffect->color.a = 0;
	barrierEffect->color.a = 0;

	if (type == HORSE_0)
	{
		plusSpeed = 0;
		plusMaxSpeed = 0;
		power = 3;
		plusStamina = 0;
	}
	if (type == HORSE_1)
	{
		plusSpeed = -10;
		plusMaxSpeed = -40;
		power = 4;
		plusStamina = 2;
	}
	if (type == HORSE_2)
	{
		plusSpeed = 0;
		plusMaxSpeed = 0;
		power = 4;
		plusStamina = 2;
	}
	if (type == HORSE_3)
	{
		plusSpeed = 10;
		plusMaxSpeed = 40;
		power = 1;
		plusStamina = 0;
	}
	if (type == HORSE_4)
	{
		plusSpeed = -5;
		plusMaxSpeed = -20;
		power = 5;
		plusStamina = 1;
	}
}

Horse::~Horse()
{
}

void Horse::update(float dt)
{
	Object::update(dt);
	GameScene *scene = (GameScene*)world.currentScene;

	if (!init)
	{
		init = true;
		if (gameManager.stage == 1)
			linePos = Vec2(GetCollisionPos().x, 1700);
		else
			linePos = Vec2(GetCollisionPos().x, 0);
		if (isAI)
			scene->ui->addChild(minimapImg = new Sprite("image/ui/minimap/enemy.png"));
		else
			scene->ui->addChild(minimapImg = new Sprite("image/ui/minimap/player.png"));
		minimapImg->rotateionCenter = minimapImg->rect.center();

		nextPoint = scene->wayPoints.begin();
	}

	if (gameManager.stage == 1)
		minimapImg->setCenter(Vec2(1030, 20) + center() / 30);
	else
		minimapImg->setCenter(Vec2(161 + center().x / 52, 646 + (center().y - 1825) / 20));

	minimapImg->rotateion = moveRotateion + D3DXToRadian(180);

	if (nextPoint->Distance(GetCollisionPos()) < 50)
	{
		wpCnt++;
		nextPoint++;
		if (nextPoint == scene->wayPoints.end())
			nextPoint = scene->wayPoints.begin();
	}

	if (((gameManager.stage == 1 && wpCnt >= 41) || (gameManager.stage == 2 && wpCnt >= 24)) && !isFin)
	{
		speed = maxSpeed = 1000;
		isFin = true;
	}

	for (auto& iter : scene->horseList)
	{
		if (pita(iter->GetCollisionPos(), GetCollisionPos()) < colRange + iter->colRange && !isStun && !isFall && !isJump && !isFin)
		{
			if (iter == this) continue;

			if (!isAI && !fighting && fightDelay > 2 && (dir != 0 || iter->dir != 0))
			{
				fightDelay = 0;
				fighting = true;
				((Player*)this)->target = iter;
				((Player*)this)->fightGage = 50;
			}

			float dir = angle(iter->GetCollisionPos(), GetCollisionPos());
			pos += Vec2(cos(dir), sin(dir)) * speed * dt;
			lineDis = pita(GetCollisionPos(), linePos);
			crash = true;
		}
		else
			crash = false;
	}

	if (gameManager.stage == 1)
	{
		if (lineDis <= 522) { lineDis = 522; }
		if (lineDis >= 946) { lineDis = 946; }
	}
	else
	{
		if (lineDis <= 1985) { lineDis = 1985; }
		if (lineDis >= 2413) { lineDis = 2413; }
	}

	if (!fighting)
		fightDelay += dt;

	dashEffect->rotateion = moveRotateion;
	boosterEffect->rotateion = moveRotateion;
	barrierEffect->rotateion = moveRotateion;

	if (GetCollisionPos().x > scene->turnPos[0].x && GetCollisionPos().x < scene->turnPos[1].x)
	{
		if (!isRightTurn)
		{
			linePos.x += speed * dt;
			SetCollisionPos(linePos + Vec2(0, lineDis + jump));
			moveRotateion = D3DXToRadian(22.5 * dir);
		}
		else
		{
			linePos.x -= speed * dt;
			SetCollisionPos(linePos - Vec2(0, lineDis + jump));
			moveRotateion = D3DXToRadian(22.5 * dir) + D3DXToRadian(180);
		}
	}
	else if (GetCollisionPos().x >= scene->turnPos[1].x)
	{
		isRightTurn = true;
		float rot = angle(scene->turnPos[1], GetCollisionPos()) - D3DXToRadian((360 * speed * dt) / (lineDis * 2 * D3DX_PI));
		SetCollisionPos(scene->turnPos[1] + Vec2(cos(rot), sin(rot)) * lineDis);
		moveRotateion = rot + D3DXToRadian(22.5 * dir) - D3DXToRadian(90);
	}
	else if (GetCollisionPos().x <= scene->turnPos[0].x)
	{
		isRightTurn = false;
		float rot = angle(scene->turnPos[0], GetCollisionPos()) - D3DXToRadian((360 * speed * dt) / (lineDis * 2 * D3DX_PI));
		SetCollisionPos(scene->turnPos[0] + Vec2(cos(rot), sin(rot)) * lineDis);
		moveRotateion = rot + D3DXToRadian(22.5 * dir) - D3DXToRadian(90);
	}

	if (!isStun && !isFall && !isJump)
	{
		if (speed == 0)
			ChangeAni(IDLE);
		else if (speed < 250)
			ChangeAni(WALK);
		else
			ChangeAni(RUN);

		if (!ready && !isFin)
		{
			speed += dt * (100 + plusSpeed);
			if (speed > maxSpeed + plusMaxSpeed)
				speed -= dt * 1000;
		}
	}

	if (isFin)
	{
		turnLeft = false;
		turnRight = false;
		dash = false;
		booster = false;
		speed = speed - 1500 * dt < 0 ? 0 : speed - 1500 * dt;
	}

	if (turnLeft)
	{
		lineDis -= dt * 150;
		dir = -1;
	}
	else if (turnRight)
	{
		lineDis += dt * 150;
		dir = 1;
	}
	else dir = 0;

	if (dash)
	{
		speed += dt * 150;
		dashEffect->color.a += dt;
		maxSpeed = 1250 + plusMaxSpeed;
	}
	else if (booster)
	{
		boosterTimer += dt;
		boosterEffect->color.a += dt;
		if (boosterTimer > 1.5)
		{
			booster = false;
			boosterTimer = 0;
		}
		speed += dt * 200;
		maxSpeed = 1500 + plusMaxSpeed;
	}
	else
		maxSpeed = 1000 + plusMaxSpeed;

	if (!dash)
		dashEffect->color.a = dashEffect->color.a - dt * 2 < 0 ? 0 : dashEffect->color.a - dt * 2;
	if (!booster)
		boosterEffect->color.a = boosterEffect->color.a - dt * 2 < 0 ? 0 : boosterEffect->color.a - dt * 2;

	if (barrier)
	{
		barrierTimer += dt;
		if (barrierFadeIn)
			barrierEffect->color.a += dt;
		if (barrierFadeIn && barrierEffect->color.a >= 1)
			barrierFadeIn = false;
		if (!barrierFadeIn)
			barrierEffect->color.a -= dt;
		if (!barrierFadeIn && barrierEffect->color.a <= 0.6f)
			barrierFadeIn = true;

		if (barrierTimer > 5)
		{
			barrier = false;
			barrierTimer = 0;
		}
	}
	else
	{
		barrierFadeIn = true;
		barrierEffect->color.a = barrierEffect->color.a - dt * 3 < 0 ? 0 : barrierEffect->color.a - dt * 3;
	}

	if (isStun)
	{
		speed = 0;
		ChangeAni(STUN);
		if (((MultiDirAnimaion*)animation[STUN])->isFin)
		{
			ChangeAni(WALK);
			isStun = false;
		}
	}
	if (isFall)
	{
		speed = speed - 1500 * dt < 0 ? 0 : speed - 1500 * dt;
		ChangeAni(FALL);
		if (((MultiDirAnimaion*)animation[FALL])->isFin)
		{
			ChangeAni(WALK);
			isFall = false;
		}
	}
	if (isJump)
	{
		ChangeAni(JUMP);

		if (gravity < 300)
		{
			jump += dt * gravity;
			gravity += 9.8f * 1.2f;
		}
		else
		{
			jump = 0;
			isJump = false;
		}
	}

	if (isAI && !ready && !isFin)
	{
		aiTimer += dt;

		if (!items.empty())
		{
			aiItemTimer += dt;
			if (aiItemTimer > aiItemDelay)
			{
				aiItemDelay = random(3, 10);
				aiItemTimer = 0;
				UseItem(items.front());
				items.pop_front();
			}
		}

		if (aiTimer > random(1.5f, 3.0f) && aiPattern == 0)
		{
			aiTimer = 0;
			aiPattern = 1;
			aiTurnDelay = random(0.5f, 2.0f);
			if (random(0, 1) == 0)
				turnLeft = true;
			else
				turnRight = true;
		}
		else if ((aiTimer > aiTurnDelay && aiPattern == 1) || crash)
		{
			aiTimer = 0;
			aiPattern = 2;
			aiDashDelay = random(3 + plusStamina, 6 + plusStamina);
			turnLeft = false;
			turnRight = false;
			dash = true;
		}
		else if (aiTimer > aiDashDelay && aiPattern == 2)
		{
			aiTimer = 0;
			aiPattern = 0;
			dash = false;
		}
	}

	dustTimer += dt;
	if (dustTimer > 60 / speed)
	{
		dustTimer = 0;
		Sprite *dust = new Sprite("image/effect/dust/" + to_string(type) + ".png");
		scene->addChild(dust);
		dust->rotateionCenter = dust->rect.center();
		dust->scaleCenter = dust->rect.center();
		dust->setCenter(GetCollisionPos() + Vec2(random(-colRange + 10, colRange - 10), random(-colRange + 10, colRange - 10)));
		scene->dustList.push_back(dust);
	}

	((MultiDirAnimaion*)animation[RUN])->fps = speed / 55;
}

void Horse::ChangeAni(AnimaionType type, bool reset)
{
	for (auto& iter : animation)
	{
		if (iter.first != type || reset)
		{
			iter.second->visible = false;
			for (int i = 0; i < 16; i++)
			{
				((MultiDirAnimaion*)iter.second)->ani[i]->currentFrame = 0;
				((MultiDirAnimaion*)iter.second)->ani[i]->isFin = false;
			}
		}
	}
	
	animation[type]->visible = true;
}

void Horse::GetRed()
{
	redTimer.reset(0.01f, 25);
	for (auto& iter : animation)
		iter.second->color = D3DXCOLOR(1, 0, 0, 1);
	redTimer.onTick = [=](){
		for (auto& iter : animation){
			iter.second->color.g += 0.04;
			iter.second->color.b += 0.04;
		}
	};
}

void Horse::UseItem(ItemType type)
{
	GameScene *scene = (GameScene*)world.currentScene;

	if (type == BOOSTER)
	{
		booster = true;
		speed += 800;
	}
	if (type == BARRIER)
	{
		barrier = true;
	}
	if (type == OBSTACLE)
	{
		Obstacle *o = new Obstacle(true);
		scene->addChild(o);
		o->SetCollisionPos(GetCollisionPos() - Vec2(cos(moveRotateion), sin(moveRotateion)) * 130);
		o->moveRotateion = moveRotateion;
		scene->obstacleList.push_back(o);
	}
}