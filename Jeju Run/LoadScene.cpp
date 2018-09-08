#include "DXUT.h"
#include "LoadScene.h"
#include "Asset.h"
#include "World.h"
#include "MainScene.h"

LoadScene::LoadScene()
{
	addChild(new Sprite("image/outgame/load/0.png"));
	addChild(bar = new Sprite("image/outgame/load/bar.png"));
	bar->pos = Vec2(309, 457);
	addChild(ani = new Animation("image/outgame/load/ani", 12, 12, true, true));
	ani->pos = Vec2(262, 360);
	addChild(op = new Animation("image/op", 45, 10, false, true));
	op->visible = false;
	op->stop = true;
	asset.ready("image");
}

LoadScene::~LoadScene()
{
}

void LoadScene::update(float dt)
{
	Scene::update(dt);

	if (asset.loaded == asset.toLoad)
	{
		op->visible = true;
		if (world.getKeyState(VK_RETURN) == 1)
			op->stop = false;

		if (op->isFin)
		{
			world.changeScene(new MainScene());
			return;
		}
	}

	bar->visibleRect.right = bar->rect.right * asset.loaded / asset.toLoad; 
	ani->pos.x = 262 + bar->visibleRect.right;

	for (int i = 0; i < 15; i++)
	if (asset.loaded < asset.toLoad)
		asset.loadNext();
}