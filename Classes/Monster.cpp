#include "Monster.h"
#include "cocos2d.h"


USING_NS_CC;


bool Monster::init()
{
	Sprite::initWithFile("monster gun r.png");
	setPhysicsBody(PhysicsBody::createBox(Size(getContentSize().width, getContentSize().height)));
	getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	bloodM = 8;
	speed = 5;
	schedule(schedule_selector(Monster::myupdate), 1.0f);
	scheduleUpdate();
	return true;
}

void Monster::getBarreir(int a[][34], int length)
{
	int i, j;
	for (i = 0; i < 18; i++) {
		for (j = 0; j < 34; j++) {
			barrier[i][j] = a[i][j];
		}
	}
}

void Monster::addHero(Hero*hero)
{
	this->hero = hero;
}

void Monster::myupdate(float dt)
{

	if (bloodM > 0)
	{
		xMove = CCRANDOM_0_1() * 2 - 1;
		yMove = CCRANDOM_0_1() * 2 - 1;
		if (xMove > 0.1)
			xMove = 1;
		if (xMove < -0.1)
			xMove = -1;
		if (xMove >=-0.1 && xMove<=0.1)
			xMove = 0;
		if (yMove > 0.1)
			yMove = 1;
		if (yMove >=-0.1&&yMove<=0.1)
			yMove = 1;
		if (yMove < -0.1)
			yMove = -1;
		if (xMove < 0)
		{
			Texture2D* monsterL;
			Sprite* Lmonster = Sprite::create(String::createWithFormat("monster2 1.png",1)->getCString());
			monsterL = Lmonster->getTexture();
			setTexture(monsterL);
			stopAllActions();
			monsterLeft();
		}
		else
		{
			Texture2D* monsterR;
			Sprite* Rmonster = Sprite::create(String::createWithFormat("monster1 1.png", 1)->getCString());
			monsterR = Rmonster->getTexture();
			setTexture(monsterR);
			stopAllActions();
			monsterRight();
		}
	
	}
}

void Monster::update(float dt)
{
	if (getPosition().x - getContentSize().width / 2 + xMove * speed < 56 && xMove < 0) {
		xMove = -xMove;
	}
	else if (getPosition().x + getContentSize().width / 2 + xMove * speed > 1990 && xMove > 0) {
		xMove = -xMove;
	}
	else if (getPosition().y - getContentSize().height / 2 + yMove * speed< 84 && yMove < 0) {
		yMove = -yMove;
	}
	else if (getPosition().y + getContentSize().height / 2 + yMove * speed> 1070 && yMove > 0) {
		yMove = -yMove;
	}
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 34; j++) {
			if (barrier[17 - i][j] == 1) {
				if ((getPosition().x + getContentSize().width / 2 + xMove * speed) >(33 + 60 * j - 10) && (getPosition().x - getContentSize().width / 2 + xMove * speed) < (33 + 60 * j + 10)) {
					if ((getPosition().y + getContentSize().height / 2 + yMove * speed) > (35 + 60 * i - 90) && (getPosition().y - getContentSize().height / 2 + yMove * speed) < (35 + 60 * i - 10)) {
						yMove = 0;
						xMove = 0;
					}
				}
			}
		}
	}
	setPosition(getPositionX() + xMove * speed, getPositionY() + yMove * speed);
}

void Monster::monsterRight()
{
	Vector<SpriteFrame*> action;
	action.reserve(2);
	action.pushBack(SpriteFrame::create(String::createWithFormat("monster1 1.png", 1)->getCString(), Rect(0, 0, 100, 100)));
	action.pushBack(SpriteFrame::create(String::createWithFormat("monster4 1.png", 1)->getCString(), Rect(0, 0, 100, 100)));
	Animation* animation = Animation::createWithSpriteFrames(action, 0.3f);
	Animate* animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}

void Monster::monsterLeft()
{
	Vector<SpriteFrame*> action;
	action.reserve(2);
	action.pushBack(SpriteFrame::create(String::createWithFormat("monster2 1.png", 1)->getCString(), Rect(0, 0, 100, 100)));
	action.pushBack(SpriteFrame::create(String::createWithFormat("monster3 1.png", 1)->getCString(), Rect(0, 0, 100, 100)));
	Animation* animation = Animation::createWithSpriteFrames(action, 0.3f);
	Animate* animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}
