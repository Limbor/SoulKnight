#pragma once
#ifndef __SELECT_HERO_H__
#define __SELECT_HERO_H__

#include "cocos2d.h"
<<<<<<< HEAD
#include "Hero.h"

=======
>>>>>>> origin/master
using namespace std;

class SelectHero : public cocos2d::Scene
{
public:
	int heronum;
	static cocos2d::Scene* createScene();
	virtual bool init();

	void menuHeroOne(cocos2d::Ref* pSender);
	void menuHeroTwo(cocos2d::Ref* pSender);
	void StartGame(cocos2d::Ref* pSender);

	CREATE_FUNC(SelectHero);
};


#endif //__SELECT_HERO_H__

