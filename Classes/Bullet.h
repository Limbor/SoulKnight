#ifndef __BULLET__H__
#define __BULLET__H__

#include "cocos2d.h"
#include "Hero.h"

USING_NS_CC;
class Bullet :public Sprite
{
private:
	Size size;
	int speed;
	float x;
	float y;
public:
	Hero * hero;
	bool init();
	CREATE_FUNC(Bullet);
	virtual void update(float dt);
	void addHero(Hero* hero);
	void setDirection(float x, float y);
};



#endif // __BULLET__H__
