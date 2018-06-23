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

<<<<<<< HEAD
	bool fire = false;
=======
>>>>>>> 12e29afed09e1b4aa9ca294b61c26c9194c6cd6d
	bool hemophagia = false;
	bool musth = false;

	Sprite * gun;
<<<<<<< HEAD
	Sprite * magic;
=======
>>>>>>> 12e29afed09e1b4aa9ca294b61c26c9194c6cd6d
	int barrier[18][34];
	int blood;
	int shield;
	int blue;
<<<<<<< HEAD
	int magicNumber = 0;
=======
>>>>>>> 12e29afed09e1b4aa9ca294b61c26c9194c6cd6d
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
<<<<<<< HEAD
	void myupdate(float dt);
	void myupdate2(float dt);
	void setspeed();
	void resetspeed();

=======
>>>>>>> 12e29afed09e1b4aa9ca294b61c26c9194c6cd6d
};

#endif // __HERO__H__