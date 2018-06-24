#pragma once
#include "cocos2d.h"
#include "Hero.h"

USING_NS_CC;

class Boss :public Sprite
{
private:
	Size size;
	int speed;
public:
	int bossNumber;
	int barrier[18][34];
	int blood;
	int BLOOD;
	double xMove;
	double yMove;
	double BeforeDistance;
	double AfterDistance;
	virtual bool init();
	static Boss * createboss(int bossNumber);
	void enemyInit(int bossNumber);
	void bossRightMove();
	void bossLeftMove();
	virtual void update(float dt);
	void getBarreir(int a[][34], int length);
	void myupdate(float dt);
	Hero * hero;
	void addHero(Hero* hero);
	CREATE_FUNC(Boss);
};


