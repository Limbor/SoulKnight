#include "Bullet.h"


Bullet * Bullet::createbullet(Hero * h)
{
	Bullet* enemy = new Bullet();
	if (enemy && enemy->init()) {
		enemy->bullet(h);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

Bullet * Bullet::createbulletM(Monster * monster)
{
	Bullet* enemy = new Bullet();
	if (enemy && enemy->init()) {
		enemy->bulletM(monster);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

void Bullet::bullet(Hero * hero)
{
	this->hero = hero;
	sort = 1;
	speed = 15;
	size = Director::getInstance()->getVisibleSize();
	Sprite::initWithFile("yellow.png");
	setPhysicsBody(PhysicsBody::createCircle(getContentSize().width / 2 - 5, cocos2d::PhysicsMaterial(0, 0, 0)));
	scheduleUpdate();
}

void Bullet::bulletM(Monster * monster)
{
	this->monster = monster;
	sort = 1;
	speed = 15;
	size = Director::getInstance()->getVisibleSize();
	Sprite::initWithFile("purple.png");
	setPhysicsBody(PhysicsBody::createCircle(getContentSize().width / 2 - 5, cocos2d::PhysicsMaterial(0, 0, 0)));
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
	setPosition(getPosition().x + x * speed, getPosition().y + y * speed);
	if (getPosition().x > hero->getPosition().x + hero->getContentSize().width / 2 || getPosition().x < hero->getPosition().x - hero->getContentSize().width / 2) {
		setVisible(true);
	}
	else if (getPosition().y > hero->getPosition().y + hero->getContentSize().width / 2 || getPosition().y < hero->getPosition().y - hero->getContentSize().width / 2) {
		setVisible(true);
	}
	if (getPosition().x - getContentSize().width / 2 < 56 || getPosition().x + getContentSize().width / 2 > 1990 ||
		getPosition().y - getContentSize().height / 2 < 95 || getPosition().y + getContentSize().height / 2 > 1020) {
		setVisible(false);
	}
}

void Bullet::setDirection(float x, float y)
{
	this->x = x / sqrt(x * x + y * y);
	this->y = y / sqrt(x * x + y * y);
}

