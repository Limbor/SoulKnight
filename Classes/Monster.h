#ifndef __MONSTER__H__
#define __MONSTER__H__

#include "cocos2d.h"
#include "Hero.h"

USING_NS_CC;
class Monster :public Sprite
{
public:
	Hero * hero;
	int bloodM;
	int speed;
	float distance;
	int barrier[18][34];
	virtual bool init();
	void myupdate(float dt);
	void update(float dt);
	void addHero(Hero* hero);
	void getBarreir(int a[][34], int length);
	CREATE_FUNC(Monster);
	void monsterRight();
	void monsterLeft();
private:
	float xMove;
	float yMove;

};

#endif // __MONSTER__H__
