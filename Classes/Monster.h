#pragma once
#include "cocos2d.h"
#include "Hero.h"

USING_NS_CC;
class Monster:public Sprite
{
public:
	virtual bool init();
	void update(float dt);
	int bloodM;
	int distance;
	CREATE_FUNC(Monster);
};

