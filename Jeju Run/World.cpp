#include "DXUT.h"
#include "World.h"
#include "Asset.h"
#include "GameScene.h"
#include "LoadScene.h"

World::World() : currentScene(nullptr), timeScale(1)
{
}

World::~World()
{
}

void World::init()
{
	asset.init();
	D3DXCreateSprite(DXUTGetD3D9Device(), &rootSprite);
	changeScene(new LoadScene());
	ZeroMemory(currentKey, 256);
	ZeroMemory(lastKey, 256);
}

void World::dispose()
{
	asset.dispose();
	SAFE_RELEASE(rootSprite);
	SAFE_DELETE(currentScene);
}

void World::update(float dt)
{
	dt *= timeScale;
	if (currentScene) currentScene->update(dt);
	
	for (int i = 0; i < 256; i++)
	{
		lastKey[i] = currentKey[i];
		currentKey[i] = GetAsyncKeyState(i) & 0x8000;
	}

	GetCursorPos(&mouseP);
	ScreenToClient(DXUTGetHWND(),&mouseP);

	for (auto& iter : timers)
		iter->update(dt);
}

void World::render()
{
	if (currentScene) currentScene->render();
}

int World::getKeyState(int vk)
{
	if (currentKey[vk] && lastKey[vk]) return 2;
	if (currentKey[vk] && !lastKey[vk]) return 1;
	if (!currentKey[vk] && lastKey[vk]) return -1;
	return -2;
}

void World::changeScene(Scene *scene)
{
	if (currentScene) SAFE_DELETE(currentScene);
	currentScene = scene;
}

Vec2 World::getMousePos()
{
	return Vec2(mouseP.x, mouseP.y);
}

World world;
