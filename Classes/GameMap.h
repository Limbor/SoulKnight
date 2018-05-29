#ifndef __GAMEMAP_H__
#define __GAMEMAP_H__

#include "cocos2d.h"
#include "GameScene.h"

class GameMap : public cocos2d::Layer
{
public:
    static cocos2d::Layer* createLayer();
    virtual bool init();
	void addBarrier(GameScene* scene);
    CREATE_FUNC(GameMap);
};

#endif // __GAMEMAP_H__
