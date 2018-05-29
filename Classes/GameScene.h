#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Hero.h"
#include "Bullet.h"

class GameScene : public cocos2d::Scene
{
public:
	Size size;
	Hero* hero;
	Sprite* stateBoard;
	Sprite* red;
	Sprite* blue;
	Sprite* grey;
	Label* bloodNumber;
	Label* shieldNumber;
	Label* blueNumber;
	bool firstTouch;
    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event *event);
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchEnded(Touch *touch, Event *event);
	void bloodChange(int x);
	void shieldChange(int x);
	void blueChange(int x);
	void addBarrier();
	CREATE_FUNC(GameScene);
};

#endif // __GAMESCENE_H__
