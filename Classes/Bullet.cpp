#include "Bullet.h"


bool Bullet::init()
{
	speed = 10;
	size = Director::getInstance()->getVisibleSize();
	Sprite::initWithFile("yellow.png");
	scheduleUpdate();
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
	if (getPosition().x > size.width || getPosition().y > size.height || getPosition().x < 0 || getPosition().y < 0) {
		setVisible(false);
	}
}

void Bullet::addHero(Hero * hero)
{
	this->hero = hero;
}

void Bullet::setDirection(float x, float y)
{
	this->x = x / sqrt(x * x + y * y);
	this->y = y / sqrt(x * x + y * y);
}

