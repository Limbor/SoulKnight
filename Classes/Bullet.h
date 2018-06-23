#ifndef __BULLET__H__
#define __BULLET__H__

#include "cocos2d.h"
#include "Hero.h"
#include "Monster.h"
#include "Boss.h"

USING_NS_CC;
class Bullet :public Sprite
{
private:
	int barrier[18][34];
	Size size;
	int speed;
	float x;
	float y;
	Hero * hero;
	Monster * monster;
	Boss * boss;
public:
	static Bullet* createbullet(Hero* hero);
	static Bullet* createbullet(Monster* monster);
	static Bullet* Bullet::createbullet(Boss * boss);
	void bullet(Hero* hero);
	void bullet(Monster* monster);
	void bullet(Boss* boss);
	bool init();
	CREATE_FUNC(Bullet);
	virtual void update(float dt);
	void setDirection(float x, float y);
	void getBarreir(int a[][34], int length);
};



#endif // __BULLET__H__
