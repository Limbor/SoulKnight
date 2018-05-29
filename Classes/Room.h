#pragma once
#ifndef __Room_H__
#define __Room_H__

#include "cocos2d.h"
using namespace std;

class Room : public cocos2d::Scene
{
public:
	string room;
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuFormRoom(cocos2d::Ref* pSender);
	void menuIntoRoom(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Room);
};


#endif // __Room_H__

