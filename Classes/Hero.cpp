#include "Hero.h"

bool Hero::init()
{
	Sprite::initWithFile("r1.png");
	size = Director::getInstance()->getVisibleSize();
	heroRight = true;
	speed = 5;
	xMove = 0;
	yMove = 0;
	blood = 6;
	shield = 5;
	blue = 200;
	setPosition(size.width / 2, size.height / 2);
	heroRightStatic();
	scheduleUpdate();
	return true;
}

void Hero::update(float dt)
{
	setPosition(getPositionX() + xMove * speed, getPositionY() + yMove * speed);
}

void Hero::frameChange()
{
	if (heroRight) {
		Texture2D* heroL;
		Sprite* lHero = CCSprite::create("l1.png");
		heroL = lHero->getTexture();
		setTexture(heroL);
	}
	else if(!heroRight) {
		Texture2D* heroR;
		Sprite* rHero = CCSprite::create("r1.png");
		heroR= rHero->getTexture();
		setTexture(heroR);
	}
}

void Hero::heroRightStatic()
{
	Vector<SpriteFrame*> action;
	action.reserve(3);
	action.pushBack(SpriteFrame::create("r1.png", Rect(0, 0, 99, 99)));
	action.pushBack(SpriteFrame::create("r2.png", Rect(0, 0, 99, 99)));
	action.pushBack(SpriteFrame::create("r3.png", Rect(0, 0, 99, 99)));
	Animation* animation = Animation::createWithSpriteFrames(action, 0.2f);
	Animate* animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}
void Hero::heroRightMove()
{
	Vector<SpriteFrame*> action;
	action.reserve(3);
	action.pushBack(SpriteFrame::create("r1.png", Rect(0, 0, 99, 99)));
	action.pushBack(SpriteFrame::create("r4.png", Rect(0, 0, 99, 99)));
	action.pushBack(SpriteFrame::create("r3.png", Rect(0, 0, 99, 99)));
	Animation* animation = Animation::createWithSpriteFrames(action, 0.2f);
	Animate* animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}
void Hero::heroLeftStatic()
{
	Vector<SpriteFrame*> action;
	action.reserve(3);
	action.pushBack(SpriteFrame::create("l1.png", Rect(0, 0, 99, 99)));
	action.pushBack(SpriteFrame::create("l2.png", Rect(0, 0, 99, 99)));
	action.pushBack(SpriteFrame::create("l3.png", Rect(0, 0, 99, 99)));
	Animation* animation = Animation::createWithSpriteFrames(action, 0.2f);
	Animate* animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}
void Hero::heroLeftMove()
{
	Vector<SpriteFrame*> action;
	action.reserve(3);
	action.pushBack(SpriteFrame::create("l1.png", Rect(0, 0, 99, 99)));
	action.pushBack(SpriteFrame::create("l4.png", Rect(0, 0, 99, 99)));
	action.pushBack(SpriteFrame::create("l3.png", Rect(0, 0, 99, 99)));
	Animation* animation = Animation::createWithSpriteFrames(action, 0.2f);
	Animate* animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}

void Hero::setSpeedx(int x)
{
	xMove = x;
}
void Hero::setSpeedy(int y)
{
	yMove = y;
}


