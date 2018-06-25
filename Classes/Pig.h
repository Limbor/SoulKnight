#pragma once

#include "cocos2d.h"
#include "Hero.h"

USING_NS_CC;
class Pig :public Sprite
{
public:
	Hero * hero;
	int bloodM;
	float distance;
	int barrier[18][34];
	virtual bool init();
	void myupdate(float dt);
	void addHero(Hero* hero);
	void getBarreir(int a[][34], int length);
	CREATE_FUNC(Pig);
	void PigRight();
	void PigLeft();
private:
	int xMove;
	int yMove;

};


