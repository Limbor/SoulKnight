#include "Pig.h"
#include "cocos2d.h"


USING_NS_CC;


bool Pig::init()
{
	Sprite::initWithFile("Pig4 1.png");
	setPhysicsBody(PhysicsBody::createBox(Size(getContentSize().width , getContentSize().height)));
	getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	bloodM = 10;
	schedule(schedule_selector(Pig::myupdate), 0.5f);
	scheduleUpdate();
	return true;
}

void Pig::getBarreir(int a[][34], int length)
{
	int i, j;
	for (i = 0; i < 18; i++) {
		for (j = 0; j < 34; j++) {
			barrier[i][j] = a[i][j];
		}
	}
}


void Pig::addHero(Hero*hero)
{
	this->hero = hero;
}


void Pig::myupdate(float dt)
{
	if (bloodM > 0)
	{
		xMove = CCRANDOM_0_1() * 500 - 250;
		yMove = CCRANDOM_0_1() * 500 - 250;
		if (getPosition().x - getContentSize().width / 2 + xMove < 56 && xMove < 0) {
			xMove = -xMove;
		}
		else if (getPosition().x + getContentSize().width / 2 + xMove > 1990 && xMove > 0) {
			xMove = -xMove;
		}
		else if (getPosition().y - getContentSize().height / 2 + yMove < 84 && yMove < 0) {
			yMove = -yMove;
		}
		else if (getPosition().y + getContentSize().height / 2 + yMove > 1070 && yMove > 0) {
			yMove = -yMove;
		}
		for (int i = 0; i < 18; i++) {
			for (int j = 0; j < 34; j++) {
				if (barrier[17 - i][j] == 1) {

					if ((getPosition().x + getContentSize().width / 2 + xMove) >(20 + 60 * j) && (getPosition().x - getContentSize().width / 2 + xMove) < (50 + 60 * j)) {
						if ((getPosition().y + getContentSize().height / 2 + yMove) > (35 + 60 * i - 90) && (getPosition().y - getContentSize().height / 2 + yMove) < (35 + 60 * i - 10)) {
							yMove = 0;
							xMove = 0;
						}
					}
				}
			}
		}
		if (xMove < 0)
		{
			Texture2D* monsterL;
			Sprite* Lmonster = Sprite::create("Pig1 1.png");
			monsterL = Lmonster->getTexture();
			setTexture(monsterL);
			stopAllActions();
			PigLeft();
		}
		else
		{
			Texture2D* monsterR;
			Sprite* Rmonster = Sprite::create("Pig4 1.png");
			monsterR = Rmonster->getTexture();
			setTexture(monsterR);
			stopAllActions();
			PigRight();
		}
		runAction(MoveBy::create(0.5, Vec2(xMove, yMove)));
	}
}


void Pig::PigRight()
{
	Vector<SpriteFrame*> action;
	action.reserve(2);
	action.pushBack(SpriteFrame::create("Pig4 1.png", Rect(0, 0, 92, 66)));
	action.pushBack(SpriteFrame::create("Pig3 1.png", Rect(0, 0, 92, 66)));
	Animation* animation = Animation::createWithSpriteFrames(action, 0.3f);
	Animate* animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}

void Pig::PigLeft()
{
	Vector<SpriteFrame*> action;
	action.reserve(2);
	action.pushBack(SpriteFrame::create("Pig2 1.png", Rect(0, 0, 92, 66)));
	action.pushBack(SpriteFrame::create("Pig1 1.png", Rect(0, 0, 92, 66)));
	Animation* animation = Animation::createWithSpriteFrames(action, 0.3f);
	Animate* animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}