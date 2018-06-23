#ifndef __HERO__H__
#define __HERO__H__

#include "cocos2d.h"

USING_NS_CC;
class Hero :public Sprite 
{
private:
	Size size;
	int speed;
	int xMove;
	int yMove;
	int heroNumber;
public:
	int BLOOD;
	int SHIELD;
	int BLUE;

	bool fire = false;
	bool hemophagia = false;

	Sprite * gun;
	Sprite * magic;
	int barrier[18][34];
	int blood;
	int shield;
	int blue;
	int magicNumber = 0;
	int damage = 1;
	int blueReduce = 1;
	float FiringRate = 0.2f;
	bool heroRight;
	bool gunRight;

	static Hero* createhero(int heroNumber);
	virtual bool init();
	void enemyInit(int heroNumber);
	CREATE_FUNC(Hero);

	virtual void update(float dt);
	void frameChange();
	void setSpeedx(int x);
	void setSpeedy(int y);
	int getSpeedx();
	int getSpeedy();
	void heroRightStatic();
	void heroRightMove();
	void heroLeftStatic();
	void heroLeftMove();
	void getBarreir(int a[][34], int length);
	void gunDirection();
	void showTimeBegan();
	void showTimeEnded();
	void myupdate(float dt);
	void myupdate2(float dt);
	void setspeed();
	void resetspeed();

};

#endif // __HERO__H__