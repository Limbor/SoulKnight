#pragma once
#ifndef __SELECT_MODE_H__
#define __SELECT_MODE_H__

#include "cocos2d.h"

using namespace std;

class SelectMode : public cocos2d::Scene
{
public:
	//
	string mode;
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuSingleMode(cocos2d::Ref* pSender);
	void menuOnlineMode(cocos2d::Ref* pSender);


	//不知道干啥的
	// implement the "static create()" method manually
	CREATE_FUNC(SelectMode);
};

#endif // __SELECT_MODE_H__

