#pragma once
#pragma warning(disable:4244 4800)

#include "DXUT.h"
#include "Enum.h"

#if defined(DEBUG) | defined(_DEBUG)
#define NEWDEBUG new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new NEWDEBUG
#endif

#define for_iter(iter, col) for(auto iter = col.begin(); iter != col.end(); iter++)

#define Vec2(x, y) D3DXVECTOR2((x),(y))
typedef D3DXVECTOR2 Vec2;

using namespace std;
using namespace std::tr2::sys;

class Rect : public RECT
{
public:
	Rect()
	{
		left = right = top = bottom = 0;
	}
	Rect(int l, int t, int r, int b)
	{
		left = l; right = r; top = t; bottom = b;
	}
	bool intersetcs(Vec2 p)
	{
		return left < p.x && right > p.x && top < p.y && bottom > p.y;
	}
	int width()
	{
		return right - left;
	}
	int height()
	{
		return bottom- top;
	}
	Vec2 center()
	{
		return Vec2(width(), height()) / 2;
	}
	Rect offset(Vec2 p)
	{
		Rect t = *this;
		t.left += p.x;
		t.right += p.x;
		t.top += p.y;
		t.bottom += p.y;
		return t;
	}
};

inline float angle(Vec2 p1, Vec2 p2)
{
	return atan2(p2.y - p1.y, p2.x - p1.x);
}

inline int random(int f, int t)
{
	static default_random_engine random(timeGetTime());
	uniform_int_distribution<int> d(f, t);
	return d(random);
}

inline float random(float f, float t)
{
	static default_random_engine random(timeGetTime());
	uniform_real_distribution<float> d(f, t);
	return d(random);
}

inline float pita(Vec2 p1, Vec2 p2)
{
	return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

class WayPoint 
{
	Vec2 p1, p2;
public:
	WayPoint(Vec2 po1, Vec2 po2){
		p1 = po1, p2 = po2;
	}

	float Distance(Vec2 p)
	{
		if (p1.x == p2.x)
		{
			if (p.y >= p1.y && p.y <= p2.y)
				return abs(p1.x - p.x);
			else
				return min(pita(p1, p), pita(p2, p));
		}
		else
		{
			if (p.x >= p1.x && p.x <= p2.x)
				return abs(p1.y - p.y);
			else
				return min(pita(p1, p), pita(p2, p));
		}
	}
};