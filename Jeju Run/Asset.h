#pragma once
#include "Texture.h"
#include "Define.h"

class Asset
{
public:
	Asset();
	~Asset();

	void init();
	void dispose();
	void ready(path p);
	void loadNext();
	Texture *getTexture(path p);
	CSound *getSound(wpath p);
	CSoundManager _s;

	map<path, Texture*> textures;
	map<wpath, CSound*> sounds;
	
	list<path> paths;
	list<path>::iterator pathIter;

	int loaded, toLoad;
};

extern Asset asset;