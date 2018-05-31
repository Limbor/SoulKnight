#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Hero.h"
#include "Bullet.h"
#include "Monster.h"

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
	//virtual bool onContactBegin(PhysicsContact* contact);
	void bloodChange(int x);
	void shieldChange(int x);
	void blueChange(int x);
	void addMonster(int x, int y);
	Monster * monster;
	CREATE_FUNC(GameScene);
};

#endif // __GAMESCENE_H__
