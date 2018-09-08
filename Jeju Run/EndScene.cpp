#include "DXUT.h"
#include "EndScene.h"
#include "GameManager.h"
#include "World.h"
#include "MainScene.h"

EndScene::EndScene()
{
	if (gameManager.win)
	{
		addChild(ed = new Animation("image/edWin/" + to_string(gameManager.type), 15, 8, false, true));
		addChild(spr = new Sprite("image/ui/text/ed/win.png"));
		spr->pos = Vec2(179, 328);
	}
	else
	{
		addChild(ed = new Animation("image/edLose/" + to_string(gameManager.type), 10, 8, false, true));
		addChild(spr = new Sprite("image/ui/text/ed/lose.png"));
		spr->pos = Vec2(644, 335);
	}
	ed->stop = true;
	spr->color.a = 0;
}

EndScene::~EndScene()
{
}

void EndScene::update(float dt)
{
	Scene::update(dt);
	
	if (world.getKeyState(VK_RETURN) == 1)
	{
		ed->stop = false;
		if (spr->color.a >= 1)
		{
			world.changeScene(new MainScene);
			return;
		}
	}

	if (ed->isFin)
	{
		spr->color.a += dt;
	}
}