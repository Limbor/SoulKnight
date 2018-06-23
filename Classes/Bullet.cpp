#include "Bullet.h"

Bullet * Bullet::createbullet(Hero * hero)
{
	Bullet* enemy = new Bullet();
	if (enemy && enemy->init()) {
		enemy->bullet(hero);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

Bullet * Bullet::createbullet(Monster * monster)
{
	Bullet* enemy = new Bullet();
	if (enemy && enemy->init()) {
		enemy->bullet(monster);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

Bullet * Bullet::createbullet(Boss * boss)
{
	Bullet* enemy = new Bullet();
	if (enemy && enemy->init()) {
		enemy->bullet(boss);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

void Bullet::bullet(Hero * hero)
{
	this->hero = hero;
	speed = 18;
	setTag(2);
	size = Director::getInstance()->getVisibleSize();
	Sprite::initWithFile("yellow.png");
	scheduleUpdate();
}

void Bullet::bullet(Monster * monster)
{
	this->monster = monster;
	speed = 10;
	setTag(3);
	size = Director::getInstance()->getVisibleSize();
	Sprite::initWithFile("purple.png");
	scheduleUpdate();
}

void Bullet::bullet(Boss * boss)
{
	this->boss = boss;
	speed = 10;
	setTag(3);
	size = Director::getInstance()->getVisibleSize();
	Sprite::initWithFile("purple.png");
	scheduleUpdate();
}

bool Bullet::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void Bullet::update(float dt)
{
	float w = getContentSize().width / 2;
	float h = getContentSize().height / 2;
	setPosition(getPosition().x + x * speed, getPosition().y + y * speed);
	if (hero) {
		if (getPosition().x - getContentSize().width / 2 + 8 > hero->getPosition().x + hero->getContentSize().width / 2
			|| getPosition().x + getContentSize().width / 2 - 8 < hero->getPosition().x - hero->getContentSize().width / 2) {
			setPhysicsBody(PhysicsBody::createCircle(getContentSize().width / 2 - 5));
			getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
			setVisible(true);
		}
		else if (getPosition().y - getContentSize().height / 2 + 8 > hero->getPosition().y + hero->getContentSize().width / 2
			|| getPosition().y + getContentSize().height / 2 - 8 < hero->getPosition().y - hero->getContentSize().width / 2) {
			setPhysicsBody(PhysicsBody::createCircle(getContentSize().width / 2 - 5));
			getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
			setVisible(true);
		}
	}
	if (boss)
	{
		if (getPosition().x - getContentSize().width / 2 + 8 > boss->getPosition().x + boss->getContentSize().width / 2
			|| getPosition().x + getContentSize().width / 2 - 8 < boss->getPosition().x - boss->getContentSize().width / 2) {
			setPhysicsBody(PhysicsBody::createCircle(getContentSize().width / 2 - 5));
			getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
			setVisible(true);
		}
		else if (getPosition().y - getContentSize().height / 2 + 8 > boss->getPosition().y + boss->getContentSize().width / 2
			|| getPosition().y + getContentSize().height / 2 - 8 < boss->getPosition().y - boss->getContentSize().width / 2) {
			setPhysicsBody(PhysicsBody::createCircle(getContentSize().width / 2 - 5));
			getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
			setVisible(true);
		}
	}
	if (monster)
	{
		if (getPosition().x - getContentSize().width / 2 + 8 > monster->getPosition().x + monster->getContentSize().width / 2
			|| getPosition().x + getContentSize().width / 2 - 8 < monster->getPosition().x - monster->getContentSize().width / 2) {
			setPhysicsBody(PhysicsBody::createCircle(getContentSize().width / 2 - 5));
			getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
			setVisible(true);
		}
		else if (getPosition().y - getContentSize().height / 2 + 8 > monster->getPosition().y + monster->getContentSize().width / 2
			|| getPosition().y + getContentSize().height / 2 - 8 < monster->getPosition().y - monster->getContentSize().width / 2) {
			setPhysicsBody(PhysicsBody::createCircle(getContentSize().width / 2 - 5));
			getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
			setVisible(true);
		}
	}
	int i, j;
	for (i = 0;i < 18;i++) {
		for (j = 0;j < 34;j++) {
			if (barrier[17 - i][j] == 1) {
				if (getPosition().x + x * speed + w >(33 + 60 * j) && getPosition().x + x * speed - w < (33 + 60 * j)) {
					if (getPosition().y + y * speed + h >(35 + 60 * i - 10) && getPosition().y + y * speed - h < (35 + 60 * i)) {
						removeFromParentAndCleanup(true);
					}
				}
			}
		}
	}
	if (getPosition().x - getContentSize().width / 2 < 56 || getPosition().x + getContentSize().width / 2 > 1990 ||
		getPosition().y - getContentSize().height / 2 < 95 || getPosition().y + getContentSize().height / 2 > 1020) {
		removeFromParentAndCleanup(true);
	}
}

void Bullet::setDirection(float x, float y)
{
	this->x = x / sqrt(x * x + y * y);
	this->y = y / sqrt(x * x + y * y);
}

void Bullet::getBarreir(int a[][34], int length)
{
	int i, j;
	for (i = 0;i < 18;i++) {
		for (j = 0;j < 34;j++) {
			barrier[i][j] = a[i][j];
		}
	}
}

