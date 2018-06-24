#include "Boss.h"
#include "Bullet.h"
#include "cocos2d.h"
#include "GameMap.h"

USING_NS_CC;

Boss * Boss::createboss(int bossNumber)
{
	Boss* enemy = new Boss();
	if (enemy && enemy->init())
	{
		enemy->autorelease();
		enemy->enemyInit(bossNumber);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool Boss::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void Boss::enemyInit(int bossNumber)
{
	this->bossNumber = bossNumber;
	Sprite::initWithFile(String::createWithFormat("bossr1 %d.png", bossNumber)->getCString());
	if (bossNumber == 1){
		blood = 100;
		BLOOD = blood;
		speed = 5;
	}else  if (bossNumber == 2) {
		blood = 80;
		BLOOD = blood;
		speed = 8;
	}else  if (bossNumber == 3) {
		blood = 60;
		BLOOD = blood;
		speed = 12;
	}
	xMove = 0;
	yMove = 0;
	setPhysicsBody(PhysicsBody::createBox(Size(getContentSize().width, getContentSize().height)));
	getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	//计时器，每0.6秒改变一次移动方向
	schedule(schedule_selector(Boss::myupdate), 0.6f);
	//每帧改变位置
	bossRightMove();
	scheduleUpdate();
	setTag(1);
}

void Boss::addHero(Hero*hero)
{
	this->hero = hero;
}

void Boss::myupdate(float dt)
{
	xMove = CCRANDOM_0_1() * 2 - 1;
	yMove = CCRANDOM_0_1() * 2 - 1;
		if (xMove < 0) {
			Texture2D* BossL;
			Sprite* lBoss = Sprite::create(String::createWithFormat("bossl1 %d.png", bossNumber)->getCString());
			BossL = lBoss->getTexture();
			setTexture(BossL);
			stopAllActions();
			bossLeftMove();
		}else  if (xMove >= 0) {
			Texture2D* BossR;
			Sprite* RBoss = Sprite::create(String::createWithFormat("bossr1 %d.png", bossNumber)->getCString());
			BossR = RBoss->getTexture();
			setTexture(BossR);
			stopAllActions();
			bossRightMove();
		}
}

void Boss::update(float dt)
{   
	if (blood > 0) {
		float w = getContentSize().width / 2;
		float h = getContentSize().height / 2;
		if (getPosition().x - getContentSize().width / 2 < 56 && xMove < 0) {
			xMove = 0;
		}
		else if (getPosition().x + getContentSize().width / 2 > 1990 && xMove > 0) {
			xMove = 0;
		}
		else if (getPosition().y - getContentSize().height / 2 < 86 && yMove < 0) {
			yMove = 0;
		}
		else if (getPosition().y + getContentSize().height / 2 > 1070 && yMove > 0) {
			yMove = 0;
		}
		int i, j;
		for (i = 0;i < 18;i++) {
			for (j = 0;j < 34;j++) {
				if (barrier[17 - i][j] == 1) {
					if (getPosition().x + xMove * speed + w > (33 + 60 * j - 50) && getPosition().x + xMove * speed - w < (33 + 60 * j + 50)) {
						if (getPosition().y + yMove * speed + h > (35 + 60 * i + 10) && getPosition().y + yMove * speed - h < (35 + 60 * i - 10)) {
							yMove = 0;
							xMove = 0;
						}
					}
				}
			}
		}
		//判断距离是否拉近或者远离
		BeforeDistance = (getPositionX() - hero->getPosition().x)*(getPositionX() - hero->getPosition().x)
			+ (getPositionY() - hero->getPosition().y)*(getPositionY() - hero->getPosition().y);
		AfterDistance = (getPositionX() + xMove * speed - hero->getPosition().x)*(getPositionX() + xMove * speed - hero->getPosition().x)
			+ (getPositionY() + yMove * speed - hero->getPosition().y)*(getPositionY() + yMove * speed - hero->getPosition().y);
		//技能“如影随形”，可以追踪英雄与Boss之间的距离，并缩短距离
		if ((AfterDistance - BeforeDistance) < 0 && AfterDistance > 10000) {
			setPosition(getPositionX() + xMove * speed, getPositionY() + yMove * speed);
		}
		else {
			setPosition(getPositionX(), getPositionY());
		}
	}
}  

void Boss::getBarreir(int a[][34], int length)
{
	int i, j;
	for (i = 0;i < 18;i++) {
		for (j = 0;j < 34;j++) {
			barrier[i][j] = a[i][j];
		}
	}
}

void Boss::bossRightMove()
{
	Vector<SpriteFrame*> action;
	action.reserve(2);
	action.pushBack(SpriteFrame::create(String::createWithFormat("bossr1 %d.png",bossNumber)->getCString(), Rect(0, 0, 100, 100)));
	action.pushBack(SpriteFrame::create(String::createWithFormat("bossr2 %d.png", bossNumber)->getCString(), Rect(0, 0, 100, 100)));
	Animation* animation = Animation::createWithSpriteFrames(action, 0.3f);
	Animate* animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}

void Boss::bossLeftMove()
{
	Vector<SpriteFrame*> action;
	action.reserve(2);
	action.pushBack(SpriteFrame::create(String::createWithFormat("bossl1 %d.png", bossNumber)->getCString(), Rect(0, 0, 100, 100)));
	action.pushBack(SpriteFrame::create(String::createWithFormat("bossl2 %d.png", bossNumber)->getCString(), Rect(0, 0, 100, 100)));
	Animation* animation = Animation::createWithSpriteFrames(action, 0.3f);
	Animate* animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}

