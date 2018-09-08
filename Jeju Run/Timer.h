#pragma once
#include "Define.h"

class Timer
{
public:
	Timer();
	~Timer();

	void reset(float d, int c);

	function<void()> onTick;
	function<void()> onFin;

	pair<float, float> duration;
	pair<int, int> count;
	bool active;

	void update(float dt);
};

