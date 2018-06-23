#include "Monster.h"
#include "cocos2d.h"


USING_NS_CC;

bool Monster::init()
{
	Sprite::initWithFile("monster gun r.png");
	setPhysicsBody(PhysicsBody::createBox(Size(getContentSize().width - 10, getContentSize().height)));
	getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	bloodM = 8;
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

	if (bloodM > 0)
	{
		xMove = CCRANDOM_0_1() * 200 - 100;
		yMove = CCRANDOM_0_1() * 200 - 100;
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
				if (barrier[17-i][j] == 1) {
					if (getPosition().x + getContentSize().width / 2 + xMove >(33 + 60 * j - 10) && getPosition().x - getContentSize().width / 2 + xMove < (33 + 60 * j + 10)) {
						if (getPosition().y - getContentSize().height / 2 + yMove >(35 + 60 * i - 90) && getPosition().y - getContentSize().height / 2 + yMove < (35 + 60 * i - 10)) {
							yMove = -yMove;
							xMove = -xMove;
						}
					}
				}
			}
		}
		runAction(MoveBy::create(1, Vec2(xMove, yMove)));
	}
}

void Monster::getBarreir(int a[][34], int length)
{
	int i, j;
	for (i = 0;i < 18;i++) {
		for (j = 0;j < 34;j++) {
			barrier[i][j] = a[i][j];
		}
	}
}

