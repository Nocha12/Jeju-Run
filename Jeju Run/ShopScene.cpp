#include "DXUT.h"
#include "ShopScene.h"
#include "World.h"
#include "GameScene.h"
#include "GameManager.h"

ShopScene::ShopScene()
{
	addChild(new Sprite("image/outgame/shop/shop.png"));
	addChild(btn1 = new Sprite("image/outgame/shop/button.png"));
	addChild(btn2 = new Sprite("image/outgame/shop/button.png"));
	addChild(btn3 = new Sprite("image/outgame/shop/button.png"));

	btn1->scaleCenter = btn1->rect.center();
	btn2->scaleCenter = btn2->rect.center();
	btn3->scaleCenter = btn3->rect.center();

	btn1->pos = Vec2(134, 587);
	btn2->pos = Vec2(526, 587);
	btn3->pos = Vec2(922, 587);

	for (int i = 0; i < 8; i++)
	for (int j = 0; j < 10; j++)
	{
		addChild(moneyText[i][j] = new Sprite("image/ui/moneyNum/" + to_string(j) + ".png"));
		moneyText[i][j]->pos = Vec2(1069 + i * 17, 104);
	}
}

ShopScene::~ShopScene()
{
}

void ShopScene::update(float dt)
{
	Scene::update(dt);

	if (gameManager.money < 1000000)
	{
		btn1->color = D3DXCOLOR(0.5, 0.5, 0.5, 1);
		btn2->color = D3DXCOLOR(0.5, 0.5, 0.5, 1);
		btn3->color = D3DXCOLOR(0.5, 0.5, 0.5, 1);
	}

	if (btn1->rectWidthPos().intersetcs(world.getMousePos()) && btn1->color.r == 1)
	{
		btn1->scale = Vec2(1.2, 1.2);
		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			gameManager.item1 = true;
			gameManager.money -= 1000000;
			btn1->color = D3DXCOLOR(0.5, 0.5, 0.5, 1);
		}
	}
	else
		btn1->scale = Vec2(1, 1);

	if (btn2->rectWidthPos().intersetcs(world.getMousePos()) && btn2->color.r == 1)
	{
		btn2->scale = Vec2(1.2, 1.2);
		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			gameManager.item2 = true;
			gameManager.money -= 1000000;
			btn2->color = D3DXCOLOR(0.5, 0.5, 0.5, 1);
		}
	}
	else
		btn2->scale = Vec2(1, 1);

	if (btn3->rectWidthPos().intersetcs(world.getMousePos()) && btn3->color.r == 1)
	{
		btn3->scale = Vec2(1.2, 1.2);
		if (world.getKeyState(VK_LBUTTON) == 1)
		{
			gameManager.item3 = true;
			gameManager.money -= 1000000;
			btn3->color = D3DXCOLOR(0.5, 0.5, 0.5, 1);
		}
	}
	else
		btn3->scale = Vec2(1, 1);

	int moneyT = gameManager.money;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 10; j++)
			moneyText[7 - i][j]->visible = false;
		moneyText[7 - i][moneyT % 10]->visible = true;
		moneyT /= 10;
	}

	if (world.getKeyState(VK_RETURN) == 1){
		gameManager.stage = 2;
		world.changeScene(new GameScene);
		return;
	}
}