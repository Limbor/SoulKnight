#ifndef __BULLET__H__
#define __BULLET__H__

#include "cocos2d.h"
#include "Hero.h"
#include "Monster.h"

USING_NS_CC;
class Bullet :public Sprite
{
private:
	Size size;
	int speed;
	float x;
	float y;
	Hero * hero;
	Monster * monster;
public:
	int sort;
	static Bullet* createbullet(Hero* hero);
	static Bullet* createbulletM(Monster* monster);
	void bullet(Hero* hero);
	void bulletM(Monster* monster);
	bool init();
	CREATE_FUNC(Bullet);
	virtual void update(float dt);
	void setDirection(float x, float y);
};



#endif // __BULLET__H__
