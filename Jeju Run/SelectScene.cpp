#include "DXUT.h"
#include "SelectScene.h"
#include "GameManager.h"
#include "World.h"
#include "GameScene.h"

SelectScene::SelectScene()
{
	addChild(back1 = new Sprite("image/outgame/select/0.png"));
	addChild(back2 = new Sprite("image/outgame/select/1.png"));
	back2->visible = false;

	addChild(frame = new Sprite("image/outgame/select/frame.png"));
	frame->pos = Vec2(149, 137);
}

SelectScene::~SelectScene()
{
}

void SelectScene::update(float dt)
{
	Scene::update(dt);

	if (world.getKeyState(VK_LEFT) == 1)
	{
		if (back1->visible)
		{
			if (frame->pos.x > 149)
				frame->pos.x -= 337;
		}
		else
		{
			if (frame->pos.x == 316)
			{
				back2->visible = false;
				back1->visible = true;
				frame->pos.x = 823;
				return;
			}

			if (frame->pos.x > 316)
				frame->pos.x = 316;
		}
	}
	if (world.getKeyState(VK_RIGHT) == 1)
	{
		if (back2->visible)
		{
			if (frame->pos.x < 653)
				frame->pos.x = 653;
		}
		else
		{
			if (frame->pos.x == 823)
			{
				back1->visible = false;
				back2->visible = true;
				frame->pos.x = 316;
				return;
			}

			if (frame->pos.x < 653)
				frame->pos.x += 337;
		}
	}

	if (world.getKeyState(VK_RETURN) == 1)
	{
		if (back1->visible)
		{
			if (frame->pos.x == 149)
				gameManager.type = HORSE_0;
			if (frame->pos.x == 486)
				gameManager.type = HORSE_1;
			if (frame->pos.x == 823)
				gameManager.type = HORSE_2;
		}
		else
		{
			if (frame->pos.x == 316)
				gameManager.type = HORSE_3;
			if (frame->pos.x == 653)
				gameManager.type = HORSE_4;
		}
		
		world.changeScene(new GameScene);
		return;
	}
}