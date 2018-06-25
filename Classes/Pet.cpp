#include "cocos2d.h"
#include "Pet.h"

USING_NS_CC;

bool Pet::init()
{
	Sprite::initWithFile("Pet4 1.png");
	setPhysicsBody(PhysicsBody::createBox(Size(getContentSize().width, getContentSize().height)));
	getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	speed = 5;
	scheduleUpdate();
	schedule(schedule_selector(Pet::myupdate), 0.6f);
	return true;
}

void Pet::addHero(Hero*hero)
{
	this->hero = hero;
}

void Pet::update(float dt)
{
	if ((getPosition().x - hero->getPosition().x ) > 100)
		xMove = -1;
	else if ((getPosition().x - hero->getPosition().x)> -100 && (getPosition().x - hero->getPosition().x)<100)
		xMove = 0;
	else if ((getPosition().x - hero->getPosition().x )< -100)
		xMove = 1;
	if ((getPosition().y -hero->getPosition().y ) > 100)
		yMove = -1;
	else if ((getPosition().y - hero->getPosition().y )> -100 && (getPosition().y - hero->getPosition().y)<100== 0)
		yMove = 0;
	else if ((getPosition().y - hero->getPosition().y)< -100)
		yMove = 1;
	float w = getContentSize().width / 2;
	float h = getContentSize().height / 2;
	if (getPosition().x - getContentSize().width / 2 < 56 && xMove <0) {
		xMove = 0;
	}
	else if (getPosition().x + getContentSize().width / 2 > 1990 && xMove >0) {
		xMove = 0;
	}
	else if (getPosition().y - getContentSize().height / 2 < 86 && yMove <0) {
		yMove = 0;
	}
	else if (getPosition().y + getContentSize().height / 2 > 1070 && yMove >0) {
		yMove = 0;
	}
	int i, j;
	for (i = 0; i < 18; i++) {
		for (j = 0; j < 34; j++) {
			if (barrier[17 - i][j] == 1) {
				if (getPosition().x + xMove * speed + w >(60 * j+50) && getPosition().x + xMove * speed - w < ( 60 * j + 70)) {
					if (getPosition().y + yMove * speed + h >(60 * i+50) && getPosition().y + yMove * speed - h < (40 + 60 * i)) {
						yMove = 0;
						xMove = 0;
					}
				}
			}
		}
	}
	setPosition(getPositionX() + xMove * speed, getPositionY() + yMove * speed);
}

void Pet::myupdate(float dt)
{
	if (xMove < 0)
	{
		Texture2D* PetL;
		Sprite* LPet = Sprite::create("Pet1 1.png");
		PetL = LPet->getTexture();
		setTexture(PetL);
		stopAllActions();
		PetLeft();
	}
	else
	{
		Texture2D* PetR;
		Sprite* RPet = Sprite::create("Pet4 1.png");
		PetR = RPet->getTexture();
		setTexture(PetR);
		stopAllActions();
		PetRight();
	}
	if ((getPosition().x - hero->getPosition().x)*(getPosition().x - hero->getPosition().x) + (getPosition().y - hero->getPosition().y)*(getPosition().y - hero->getPosition().y) > 200000)
		setPosition(hero->getPosition().x + 100, hero->getPosition().y);
}



void Pet::getBarreir(int a[][34], int length)
{
	int i, j;
	for (i = 0; i < 18; i++) {
		for (j = 0; j < 34; j++) {
			barrier[i][j] = a[i][j];
		}
	}
}

void Pet::PetRight()
{
	Vector<SpriteFrame*> action;
	action.reserve(3);
	action.pushBack(SpriteFrame::create("Pet4 1.png", Rect(0, 0, 40, 40)));
	action.pushBack(SpriteFrame::create("Pet2 1.png", Rect(0, 0, 40, 40)));
	action.pushBack(SpriteFrame::create("Pet5 1.png", Rect(0, 0, 40, 40)));
	Animation* animation = Animation::createWithSpriteFrames(action, 0.3f);
	Animate* animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}

void Pet::PetLeft()
{
	Vector<SpriteFrame*> action;
	action.reserve(3);
	action.pushBack(SpriteFrame::create("Pet1 1.png", Rect(0, 0, 40, 40)));
	action.pushBack(SpriteFrame::create("Pet3 1.png", Rect(0, 0, 40, 40)));
	action.pushBack(SpriteFrame::create("Pet6 1.png", Rect(0, 0, 40, 40)));
	Animation* animation = Animation::createWithSpriteFrames(action, 0.3f);
	Animate* animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}