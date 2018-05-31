#pragma once
#include "cocos2d.h"
#include "Hero.h"

USING_NS_CC;
class Monster:public Sprite
{
public:
	virtual bool init();
	void update(float dt);
	void myupdate(float dt);
	int bloodM;
	float distance;
	Hero * hero;
	void addHero(Hero* hero);
	CREATE_FUNC(Monster);
};

