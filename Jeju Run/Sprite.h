#pragma once
#include "Entity.h"
#include "Texture.h"

class Sprite :
	public Entity
{
public:
	Sprite();
	Sprite(path p);

	~Sprite();

	void setPath(path p);
	void render();
	
	D3DXCOLOR color;
	Texture *texture;
};

