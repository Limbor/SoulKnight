#pragma once
#ifndef __SELECT_MODE_H__
#define __SELECT_MODE_H__

#include "cocos2d.h"
#include <string>

using namespace std;

class ShowMessage : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void tohero(cocos2d::Ref* pSender);
	
	CREATE_FUNC(ShowMessage);
};

#endif // __SELECT_MODE_H__

