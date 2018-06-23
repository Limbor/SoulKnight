#include "Hero.h"

Hero * Hero::createhero(int heroNumber)
{
	Hero* enemy = new Hero();
	if (enemy && enemy->init())
	{
		enemy->autorelease();
		enemy->enemyInit(heroNumber);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool Hero::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void Hero::enemyInit(int heroNumber)
{
	this->heroNumber = heroNumber;
	Sprite::initWithFile(String::createWithFormat("r1 %d.png", heroNumber)->getCString());
	if (heroNumber == 1) {
		BLOOD = blood = 6;
		SHIELD = shield = 5;
		BLUE = blue = 200;
	}
	else if (heroNumber == 2) {
		BLOOD = blood = 10;
		SHIELD = shield = 3;
		BLUE = blue = 240;
	}
	gun = Sprite::create("gun r.png");
	gun->setPosition(getPosition().x + 60, getPosition().y + 25);
	addChild(gun);
	size = Director::getInstance()->getVisibleSize();
	heroRight = true;
	gunRight = true;
	speed = 8;
	xMove = 0;
	yMove = 0;
	setPosition(size.width / 2, size.height / 2);
	setPhysicsBody(PhysicsBody::createBox(Size(getContentSize().width - 30, getContentSize().height)));
	getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	heroRightStatic();
	scheduleUpdate();
	setTag(0);
}

void Hero::update(float dt)
{
	if (gunRight != heroRight) {
		gunRight = heroRight;
		gunDirection();
		gun->setRotation(-gun->getRotation());
	}
	float w = getContentSize().width / 2;
	float h = getContentSize().height / 2;
	if (getPosition().x - getContentSize().width / 2 < 56 && xMove == -1) {
		xMove = 0;
	}
	else if (getPosition().x + getContentSize().width / 2 > 1990 && xMove == 1) {
		xMove = 0;
	}
	else if (getPosition().y - getContentSize().height / 2 < 84 && yMove == -1) {
		yMove = 0;
	}
	else if (getPosition().y + getContentSize().height / 2 > 1070 && yMove == 1) {
		yMove = 0;
	}
	int i, j;
	for (i = 0;i < 18;i++) {
		for (j = 0;j < 34;j++) {
			if (barrier[17 - i][j] == 1) {
				if (getPosition().x + xMove * speed + w > (33 + 60 * j - 10) && getPosition().x + xMove * speed - w < (33 + 60 * j + 10)) {
					if (getPosition().y + yMove * speed - h > (35 + 60 * i - 90 ) && getPosition().y + yMove * speed - h < (35 + 60 * i - 10 )) {
						yMove = 0;
						xMove = 0;
					}
				}
			}
<<<<<<< HEAD
			if (barrier[17 - i][j] == 2) {
				if (getPosition().x + xMove * speed + w >(33 + 60 * j - 10) && getPosition().x + xMove * speed - w < (33 + 60 * j + 10)) {
					if (getPosition().y + yMove * speed - h >(35 + 60 * i - 90) && getPosition().y + yMove * speed - h < (35 + 60 * i - 10)) {
						scheduleOnce(schedule_selector(Hero::myupdate), 0.0f);

					}
				}
			}


=======
>>>>>>> 12e29afed09e1b4aa9ca294b61c26c9194c6cd6d
		}
	}
	setPosition(getPositionX() + xMove * speed, getPositionY() + yMove * speed);
}

void Hero::frameChange()
{
	if (heroRight) {
		Texture2D* heroL;
		Sprite* lHero = Sprite::create(String::createWithFormat("l1 %d.png", heroNumber)->getCString());
		heroL = lHero->getTexture();
		setTexture(heroL);
	}
	else if(!heroRight) {
		Texture2D* heroR;
		Sprite* rHero = Sprite::create(String::createWithFormat("r1 %d.png", heroNumber)->getCString());
		heroR= rHero->getTexture();
		setTexture(heroR);
	}
}

void Hero::heroRightStatic()
{
	Vector<SpriteFrame*> action;
	action.reserve(3);
	action.pushBack(SpriteFrame::create(String::createWithFormat("r1 %d.png", heroNumber)->getCString(), Rect(0, 0, 99, 99)));
	action.pushBack(SpriteFrame::create(String::createWithFormat("r2 %d.png", heroNumber)->getCString(), Rect(0, 0, 99, 99)));
	action.pushBack(SpriteFrame::create(String::createWithFormat("r3 %d.png", heroNumber)->getCString(), Rect(0, 0, 99, 99)));
	Animation* animation = Animation::createWithSpriteFrames(action, 0.2f);
	Animate* animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}
void Hero::heroRightMove()
{
	Vector<SpriteFrame*> action;
	action.reserve(3);
	action.pushBack(SpriteFrame::create(String::createWithFormat("r1 %d.png", heroNumber)->getCString(), Rect(0, 0, 99, 99)));
	action.pushBack(SpriteFrame::create(String::createWithFormat("r4 %d.png", heroNumber)->getCString(), Rect(0, 0, 99, 99)));
	action.pushBack(SpriteFrame::create(String::createWithFormat("r3 %d.png", heroNumber)->getCString(), Rect(0, 0, 99, 99)));
	Animation* animation = Animation::createWithSpriteFrames(action, 0.2f);
	Animate* animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}
void Hero::heroLeftStatic()
{
	Vector<SpriteFrame*> action;
	action.reserve(3);
	action.pushBack(SpriteFrame::create(String::createWithFormat("l1 %d.png", heroNumber)->getCString(), Rect(0, 0, 99, 99)));
	action.pushBack(SpriteFrame::create(String::createWithFormat("l2 %d.png", heroNumber)->getCString(), Rect(0, 0, 99, 99)));
	action.pushBack(SpriteFrame::create(String::createWithFormat("l3 %d.png", heroNumber)->getCString(), Rect(0, 0, 99, 99)));
	Animation* animation = Animation::createWithSpriteFrames(action, 0.2f);
	Animate* animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}
void Hero::heroLeftMove()
{
	Vector<SpriteFrame*> action;
	action.reserve(3);
	action.pushBack(SpriteFrame::create(String::createWithFormat("l1 %d.png", heroNumber)->getCString(), Rect(0, 0, 99, 99)));
	action.pushBack(SpriteFrame::create(String::createWithFormat("l4 %d.png", heroNumber)->getCString(), Rect(0, 0, 99, 99)));
	action.pushBack(SpriteFrame::create(String::createWithFormat("l3 %d.png", heroNumber)->getCString(), Rect(0, 0, 99, 99)));
	Animation* animation = Animation::createWithSpriteFrames(action, 0.2f);
	Animate* animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}

void Hero::getBarreir(int a[][34], int length)
{
	int i, j;
	for (i = 0;i < 18;i++) {
		for (j = 0;j < 34;j++) {
			barrier[i][j] = a[i][j];
		}
	}
}

void Hero::gunDirection()
{
	if (gunRight) {
		Texture2D* gunR;
		Sprite* rGun = Sprite::create("gun r.png");
		gunR = rGun->getTexture();
		gun->setTexture(gunR);
		gun->setPosition(gun->getPosition().x + 25, gun->getPosition().y);
	}
	else {
		Texture2D* gunL;
		Sprite* lGun = Sprite::create("gun l.png");
		gunL = lGun->getTexture();
		gun->setTexture(gunL);
		gun->setPosition(gun->getPosition().x - 25, gun->getPosition().y);
	}
}

void Hero::showTimeEnded()
{
<<<<<<< HEAD
	if (heroNumber == 1) {
		FiringRate *= 2;
		musth = false;
		hemophagia = false;
	}
	else if (heroNumber == 2) {
		magicNumber = 0;
		magic->removeFromParentAndCleanup(true);
	}
=======
	FiringRate *= 2;
	musth = false;
	hemophagia = false;
>>>>>>> 12e29afed09e1b4aa9ca294b61c26c9194c6cd6d
}

void Hero::showTimeBegan()
{
<<<<<<< HEAD
	if (heroNumber == 1) {
		FiringRate /= 2;
		musth = true;
		hemophagia = true;
	}
	else if (heroNumber == 2) {
		srand(time(0));
		magicNumber = rand() % 3 + 1;
		magic = Sprite::create(String::createWithFormat("magic %d.png", magicNumber)->getCString());
		magic->setPosition(getContentSize().width / 2, getContentSize().height / 2);
		magic->setLocalZOrder(-1);
		addChild(magic);
	}
=======
	FiringRate /= 2;
	musth = true;
	hemophagia = true;
>>>>>>> 12e29afed09e1b4aa9ca294b61c26c9194c6cd6d
}

void Hero::setSpeedx(int x)
{
	xMove = x;
}
void Hero::setSpeedy(int y)
{
	yMove = y;
}
int Hero::getSpeedx()
{
	return xMove;
}
int Hero::getSpeedy()
{
	return yMove;
}
<<<<<<< HEAD

void Hero::myupdate(float dt) {
	setspeed();
	scheduleOnce(schedule_selector(Hero::myupdate2), 1.0f);
}
void Hero::myupdate2(float dt) {
	resetspeed();
}
void Hero::setspeed() {
	this->speed = 12;
}
void Hero::resetspeed() {
	this->speed = 8;
}
=======
>>>>>>> 12e29afed09e1b4aa9ca294b61c26c9194c6cd6d


