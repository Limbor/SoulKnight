#include "Monster.h"
#include "cocos2d.h"


USING_NS_CC;

bool Monster::init()
{
	Sprite::initWithFile("monster gun r.png");
	bloodM = 100;
	scheduleUpdate();
	return true;
}


void Monster::update(float dt)
{
	//distance=(getPositionX()-hero->getPositionX())*
	if (bloodM > 0)
	{
		runAction(MoveBy::create(CCRANDOM_0_1() + 3, Vec2(CCRANDOM_0_1() * 20 - 10, CCRANDOM_0_1() * 20 - 10)));
	}
	else
	{
		setRotation(-90.0f);
	}
	
}
