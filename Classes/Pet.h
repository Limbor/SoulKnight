#pragma once

#include "cocos2d.h"
#include "Hero.h"

USING_NS_CC;

class Pet :public Sprite
{
public:
	Hero * hero;
	int barrier[18][34];
	virtual bool init();
	void getBarreir(int a[][34], int length);
	void update(float dt);
	void myupdate(float dt);
	void addHero(Hero* hero);
	void PetRight();
	void PetLeft();
	CREATE_FUNC(Pet);


private:
	int xMove;
	int yMove;
	int speed;
};
