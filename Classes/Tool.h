#pragma once
#include "cocos2d.h"
#include "Hero.h"

USING_NS_CC;

class Tool :public Sprite
{
private:
	Size size;
public:
	int toolNumber;
	Hero * hero;
	virtual bool init();
	static Tool * createtool(int toolNumber);
	void enemyInit(int toolNumber);

	CREATE_FUNC(Tool);
};

