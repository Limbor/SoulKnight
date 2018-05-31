#pragma once
#ifndef __SELECT_HERO_H__
#define __SELECT_HERO_H__

#include "cocos2d.h"
using namespace std;

class SelectHero : public cocos2d::Scene
{
public:
	string hero;
	static cocos2d::Scene* createScene(string str);

	virtual bool init();

	// 
	void menuHeroOne(cocos2d::Ref* pSender);
	void menuHeroTwo(cocos2d::Ref* pSender);

	// 
	CREATE_FUNC(SelectHero);
};

class htemp { public: string st; };

#endif //__SELECT_HERO_H__

