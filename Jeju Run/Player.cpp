#include "DXUT.h"
#include "Player.h"
#include "World.h"
#include "GameScene.h"
#include "GameManager.h"

Player::Player(HorseType type) : Horse(type), stamina(0), maxStamina(100), fightGage(50), staminaDelay(0), distance(0)
{
	isAI = false;
	if (gameManager.item1)
		plusStamina += 2;
	if (gameManager.item2)
		plusSpeed += 10;
	if (gameManager.item3)
		plusMaxSpeed += 80;

	Sprite *spr = new Sprite("image/ui/text/player.png");
	addChild(spr);
	spr->pos = Vec2(213, 106);
}

Player::~Player()
{
}

void Player::update(float dt)
{
	GameScene *scene = (GameScene*)world.currentScene;
	Horse::update(dt);

	distance += speed / 800;
	gameManager.score += speed / 50;
	
	staminaDelay = staminaDelay - dt < 0 ? 0 : staminaDelay - dt;
	if (staminaDelay == 0 && !ready && !isFin)
		stamina = stamina + dt * (10 + plusStamina) > maxStamina ? maxStamina : stamina + dt * (10 + plusStamina);
	scene->ui->staminaBar->visibleRect.top = scene->ui->staminaBar->rect.bottom - scene->ui->staminaBar->rect.bottom * stamina / maxStamina;
	scene->ui->staminaBar->pos.y = 288 + scene->ui->staminaBar->rect.bottom - scene->ui->staminaBar->rect.bottom * stamina / maxStamina;

	scene->ui->dashEffect->color.a = (speed - 1000) / 500;

	if (world.getKeyState(VK_RETURN) == 1 && !isFin)
	{
		UseItem(BARRIER);
		UseItem(BOOSTER);
		UseItem(OBSTACLE);
	}

	if (fighting)
	{
		world.timeScale = 0.1;
		if (scene->scale.x < 2)
			scene->scale += Vec2(dt * 3, dt * 3);
		if (scene->ui->fightEffect->color.a < 1)
			scene->ui->fightEffect->color.a += dt * 10;

		scene->ui->fightBar->visibleRect.right = scene->ui->fightBar->rect.right * fightGage / 100;
		scene->ui->fightBar->visible = true;
		scene->ui->fightBarBack->visible = true;
		scene->ui->fightAni->visible = true;

		fightGage -= target->power * dt * 30;

		if (world.getKeyState(VK_LEFT) == 1 || world.getKeyState(VK_RIGHT) == 1)
		{
			fightGage += power * dt * 400;
			scene->shake(0.001, 5, 10);
		}
		if (fightGage >= 100)
		{
			fighting = false;
			scene->ui->fightBar->visible = false;
			scene->ui->fightBarBack->visible = false;
			scene->ui->fightAni->visible = false;
			if(!target->barrier)
				target->isStun = true;
		}
		else if (fightGage <= 0)
		{
			fighting = false;
			scene->ui->fightBar->visible = false;
			scene->ui->fightBarBack->visible = false;
			scene->ui->fightAni->visible = false; 
			if (!barrier)
				isStun = true;
		}
	}
	else if (!ready && !isFin)
	{
		world.timeScale = 1;
		if (scene->scale.x > 1)
			scene->scale -= Vec2(dt, dt);
		if (scene->ui->fightEffect->color.a > 0)
			scene->ui->fightEffect->color.a -= dt * 2;
		if (world.getKeyState(VK_UP) == 2 && stamina > 0 && staminaDelay == 0)
		{
			stamina = stamina - dt * 25 < 0 ? 0 : stamina - dt * 25;
			if (stamina == 0)
				staminaDelay = 3;
			dash = true;
		}
		else dash = false;

		if (world.getKeyState(VK_DOWN) == 2)
		{
			speed = speed - dt * 500 < 0 ? 0 : speed - dt * 500;
			dash = true;
		}

		if (world.getKeyState(VK_LEFT) == 2)
			turnLeft = true;
		else
			turnLeft = false;

		if (world.getKeyState(VK_RIGHT) == 2)
			turnRight = true;
		else
			turnRight = false;
		if (gameManager.stage == 2 && !isJump && !isStun && !isFall)
		if (world.getKeyState(VK_SPACE) == 1)
		{
			gravity = -300;
			isJump = true;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		scene->ui->itemBig[i]->visible = false;
		scene->ui->itemSmall[i]->visible = false;
	}
	if (items.size() > 0)
	{
		scene->ui->itemBig[items.front()]->visible = true;
		if (items.size() > 1)
			scene->ui->itemSmall[items.back()]->visible = true;
		
		if (items.size() > 1)
		if (world.getKeyState(VK_SHIFT) == 1)
		{
			ItemType type = items.front();
			items.pop_front();
			items.push_back(type);
		}

		if (world.getKeyState(VK_CONTROL) == 1)
		{
			UseItem(items.front());
			items.pop_front();
		}
	}
}