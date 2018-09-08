#include "DXUT.h"
#include "Timer.h"
#include "World.h"

Timer::Timer() : active(false)
{
	world.timers.push_back(this);
	onTick = [](){};
	onFin = [](){};
}

Timer::~Timer()
{
	world.timers.remove(this);
}

void Timer::reset(float d, int c)
{
	duration = pair<float, float>(0, d);
	count = pair<int, int>(0, c);
	active = true;
}

void Timer::update(float dt)
{
	if (!active) return;

	duration.first += dt;

	if (duration.first > duration.second)
	{
		onTick();
		duration.first = 0;

		if (++count.first > count.second)
		{
			onFin();
			active = false;
		}
	}
}