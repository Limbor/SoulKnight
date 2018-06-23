#include "Boss.h"

bool Boss::init()
{
	Sprite::initWithFile("bossr.png");
	blood = 60;
	speed = 8;
	xMove = 0;
	yMove = 0;
	setPhysicsBody(PhysicsBody::createBox(Size(getContentSize().width - 25, getContentSize().height)));
	getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	//��ʱ����ÿ0.6��ı�һ���ƶ�����
	schedule(schedule_selector(Boss::myupdate), 0.6f);
	//ÿ֡�ı�λ��
	bossRightMove();
	scheduleUpdate();
	return true;
}

void Boss::addHero(Hero*hero)
{
	this->hero = hero;
}

void Boss::myupdate(float dt)
{
	xMove = CCRANDOM_0_1() * 2 - 1;
	yMove = CCRANDOM_0_1() * 2 - 1;

	//�������
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
	AfterDistance = (getPositionX() + xMove * speed - hero->getPosition().x)*(getPositionX() + xMove * speed - hero->getPosition().x)
		+ (getPositionY() + yMove * speed - hero->getPosition().y)*(getPositionY() + yMove * speed - hero->getPosition().y);


	if (xMove < 0) {
		Texture2D* BossL;
		Sprite* lBoss = CCSprite::create("bossl1.png");
		BossL = lBoss->getTexture();
		setTexture(BossL);
		stopAllActions();
		bossLeftMove();
	}
	else  if (xMove >= 0) {
		Texture2D* BossR;
		Sprite* RBoss = CCSprite::create("bossr1.png");
		BossR = RBoss->getTexture();
		setTexture(BossR);
		stopAllActions();
		bossRightMove();
	}

}


void Boss::update(float dt)
{
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
	for (i = 0;i < 18;i++) {
		for (j = 0;j < 34;j++) {
			if (barrier[17 - i][j] == 1) {
				if (getPosition().x + xMove * speed + w >(33 + 60 * j - 30) && getPosition().x + xMove * speed - w < (33 + 60 * j + 30)) {
					if (getPosition().y + yMove * speed + h >(35 + 60 * i + 30) && getPosition().y + yMove * speed - h < (35 + 60 * i - 30)) {
						yMove = 0;
						xMove = 0;
					}
				}
			}
		}
	}

	//�жϾ����Ƿ���������Զ��
	BeforeDistance = (getPositionX() - hero->getPosition().x)*(getPositionX() - hero->getPosition().x)
		+ (getPositionY() - hero->getPosition().y)*(getPositionY() - hero->getPosition().y);
	AfterDistance = (getPositionX() + xMove * speed - hero->getPosition().x)*(getPositionX() + xMove * speed - hero->getPosition().x)
		+ (getPositionY() + yMove * speed - hero->getPosition().y)*(getPositionY() + yMove * speed - hero->getPosition().y);

	//���ܡ���Ӱ���Ρ�������׷��Ӣ����Boss֮��ľ��룬�����̾���
	if ((AfterDistance - BeforeDistance)<0 && AfterDistance>10000) {
		setPosition(getPositionX() + xMove * speed, getPositionY() + yMove * speed);
	}
	else {
		setPosition(getPositionX(), getPositionY());
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
	action.pushBack(SpriteFrame::create("bossr1.png", Rect(0, 0, 100, 100)));
	action.pushBack(SpriteFrame::create("bossr2.png", Rect(0, 0, 100, 100)));
	Animation* animation = Animation::createWithSpriteFrames(action, 0.3f);
	Animate* animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}

void Boss::bossLeftMove()
{
	Vector<SpriteFrame*> action;
	action.reserve(2);
	action.pushBack(SpriteFrame::create("bossl1.png", Rect(0, 0, 100, 100)));
	action.pushBack(SpriteFrame::create("bossl2.png", Rect(0, 0, 100, 100)));
	Animation* animation = Animation::createWithSpriteFrames(action, 0.3f);
	Animate* animate = Animate::create(animation);
	runAction(RepeatForever::create(animate));
}


