#include "Monster.h"
#include "cocos2d.h"


USING_NS_CC;

bool Monster::init()
{
	Sprite::initWithFile("monster gun r.png");
	bloodM = 100;
	schedule(schedule_selector(Monster::myupdate), 3.0f);
	scheduleUpdate();
	return true;
}

void Monster::addHero(Hero*hero)
{
	this->hero = hero;
}

void Monster::myupdate(float dt)
{
	distance = (getPosition().x - hero->getPosition().x)*(getPositionX() - hero->getPosition().x) + (getPosition().y - hero->getPosition().y)*(getPosition().y - hero->getPosition().y);
	if (distance > 180000)
	{
		if (bloodM > 0)
		{
			runAction(MoveBy::create(1, Vec2(CCRANDOM_0_1() * 180 - 90, CCRANDOM_0_1() * 180 - 90)));
		}
		else
		{
			setRotation(-90.0f);
		}
	}
}


void Monster::update(float dt)
{
	distance = (getPosition().x - hero->getPosition().x)*(getPosition().x - hero->getPosition().x) + (getPosition().y - hero->getPosition().y)*(getPosition().y - hero->getPosition().y);
	if(distance <= 180000)
	{
		if (bloodM > 0)
		{
			runAction(MoveBy::create(CCRANDOM_0_1() + 3, Vec2(CCRANDOM_0_1() * 200 - 100, CCRANDOM_0_1() * 200 - 100)));
		}
		else
		{
			setRotation(-90.0f);
		}
	}
}


