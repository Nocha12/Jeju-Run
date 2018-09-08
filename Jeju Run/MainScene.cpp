#include "DXUT.h"
#include "MainScene.h"
#include "World.h"
#include "GameManager.h"
#include "SelectScene.h"

MainScene::MainScene() : howToCnt(-1)
{
	addChild(new Animation("image/outgame/title/ani", 10, 8, true, true));
	addChild(title = new Sprite("image/outgame/title/title.png"));
	title->pos = Vec2(141, 21);
	addChild(startB = new Sprite("image/outgame/title/start.png"));
	addChild(howToB = new Sprite("image/outgame/title/howtoB.png"));
	addChild(introB = new Sprite("image/outgame/title/introB.png"));
	addChild(exitB = new Sprite("image/outgame/title/exit.png"));
	
	startB->scaleCenter = startB->rect.center();
	howToB->scaleCenter = howToB->rect.center();
	introB->scaleCenter = introB->rect.center();
	exitB ->scaleCenter = exitB ->rect.center();
	startB->pos = Vec2(191, 343);
	howToB->pos = Vec2(184, 432);
	introB->pos = Vec2(205, 523);
	exitB->pos = Vec2(214, 612);

	for (int i = 0; i < 3; i++)
	{
		addChild(howToEx[i] = new Sprite("image/outgame/title/how/" + to_string(i) + ".png"));
		howToEx[i]->visible = false;
	}
	addChild(introEx = new Sprite("image/outgame/title/intro.png"));
	introEx->visible = false;
}

MainScene::~MainScene()
{
}

void MainScene::update(float dt)
{
	Scene::update(dt);

	if (introEx->visible)
	{
		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			introEx->visible = false;
			return;
		}
	}
	else if (howToCnt >= 0){
		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			if (howToCnt < 2)
			{
				howToEx[howToCnt]->visible = false;
				howToCnt++;
				howToEx[howToCnt]->visible = true;
			}
			else
			{
				howToEx[howToCnt]->visible = false;
				howToCnt = -1;
			}
			return;
		}
	}
	else
	{
		if (startB->rectWidthPos().intersetcs(world.getMousePos()))
		{
			startB->scale = Vec2(1.2, 1.2);
			if (world.getKeyState(VK_LBUTTON) == 1)
			{
				gameManager.init();
				world.changeScene(new SelectScene);
				return; 
			}
		}
		else
			startB->scale = Vec2(1, 1);

		if (howToB->rectWidthPos().intersetcs(world.getMousePos()))
		{
			howToB->scale = Vec2(1.2, 1.2);
			if (world.getKeyState(VK_LBUTTON) == 1)
			{
				howToCnt = 0;
				howToEx[0]->visible = true;;
			}
		}
		else
			howToB->scale = Vec2(1, 1);

		if (introB->rectWidthPos().intersetcs(world.getMousePos()))
		{
			introB->scale = Vec2(1.2, 1.2);
			if (world.getKeyState(VK_LBUTTON) == 1)
			{
				introEx->visible = true;
			}
		}
		else
			introB->scale = Vec2(1, 1);

		if (exitB->rectWidthPos().intersetcs(world.getMousePos()))
		{
			exitB->scale = Vec2(1.2, 1.2);
			if (world.getKeyState(VK_LBUTTON) == 1)
			{
				exit(1);
			}
		}
		else
			exitB->scale = Vec2(1, 1);
	}
}
