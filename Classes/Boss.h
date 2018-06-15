#ifndef __BOSS__H__
#define __BOSS__H__

#include "cocos2d.h"
#include "Hero.h"

USING_NS_CC;
class Boss :public Sprite
{
private:
	Size size;
	int speed;
public:
	int barrier[18][34];
	int blood;
	double xMove;
	double yMove;
	double BeforeDistance;
	double AfterDistance;
	virtual bool init();
	void Boss::bossRightMove();
	void Boss::bossLeftMove();
	virtual void update(float dt);
	void getBarreir(int a[][34], int length);
	void myupdate(float dt);
	Hero * hero;
	void addHero(Hero* hero);
	CREATE_FUNC(Boss);
};


#endif // __BOSS__H__