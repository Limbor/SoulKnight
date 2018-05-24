#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class GameMap : public cocos2d::Layer
{
public:
    static cocos2d::Layer* createLayer();
    virtual bool init();
    CREATE_FUNC(GameMap);
};

#endif // __HELLOWORLD_SCENE_H__
