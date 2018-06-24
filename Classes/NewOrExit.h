
#ifndef __ROOM__H__
#define __ROOM__H__

#include "cocos2d.h"
using namespace std;

class NewOrExit : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene(int win);
	virtual bool init();

	void newgame(cocos2d::Ref* pSender);
	void exitgame(cocos2d::Ref* pSender);

	CREATE_FUNC(NewOrExit);
};

class temp {
    public:  int WIN;
};
#endif // __Room_H__

