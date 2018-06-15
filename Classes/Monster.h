#ifndef __MONSTER__H__
#define __MONSTER__H__

#include "cocos2d.h"
#include "Hero.h"

USING_NS_CC;
class Monster :public Sprite
{
public:
	int barrier[18][34];
	Hero * hero;
	int bloodM;
	float distance;
	virtual bool init();
	void myupdate(float dt);
	void addHero(Hero* hero);
	void getBarreir(int a[][34], int length);
	CREATE_FUNC(Monster);
private:
	int xMove;
	int yMove;
};

#endif // __MONSTER__H__
