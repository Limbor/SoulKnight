#ifndef __HERO__H__
#define __HERO__H__

#include "cocos2d.h"

USING_NS_CC;
class Hero :public Sprite 
{
private:
	Size size;
	int speed;
	int xMove;
	int yMove;
public:
	int blood;
	int shield;
	int blue;
	bool heroRight;
	virtual bool init();
	CREATE_FUNC(Hero);
	virtual void update(float dt);
	void frameChange();
	void setSpeedx(int x);
	void setSpeedy(int y);
	void heroRightStatic();
	void heroRightMove();
	void heroLeftStatic();
	void heroLeftMove();
};

#endif // __HERO__H__