#include "DXUT.h"
#include "GameManager.h"

GameManager::GameManager() : stage(1), score(0), money(0), type(HORSE_0), item1(false), item2(false), item3(false), win(false)
{
}

GameManager::~GameManager()
{
}

void GameManager::init()
{
	stage = 1; score = 0; money = 0; type = HORSE_0;
	item1 = (false), item2 = (false), item3 = (false);
	win = false;
}

GameManager gameManager;