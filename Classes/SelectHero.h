#pragma once
#ifndef __SELECT_HERO_H__
#define __SELECT_HERO_H__

#include "cocos2d.h"
#include "GameScene.h"
using namespace std;

class SelectHero : public cocos2d::Scene
{
public:
	string hero ;
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuHeroOne(cocos2d::Ref* pSender);
	void menuHeroTwo(cocos2d::Ref* pSender);
	void menuStartGame(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(SelectHero);
};

#endif //__SELECT_HERO_H__

