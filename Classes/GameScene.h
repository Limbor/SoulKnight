#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Hero.h"
#include "Bullet.h"
#include "Monster.h"
#include "Boss.h"

class GameScene : public cocos2d::Scene
{
private:
	int monster_number;
	float xEnd;
	float yEnd;
	bool skillCD = false;
	bool firstTouch;
	bool recover;
	Size size;
	Hero* hero;
	Boss* boss;
	Monster * monster_array[10];
	Sprite* stateBoard;
	Sprite* red;
	Sprite* redB;
	Sprite* blue;
	Sprite* grey;
	Label* bloodNumber;
	Label* bloodNumberB;
	Label* shieldNumber;
	Label* blueNumber;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual bool onContactBegin(PhysicsContact &contact);
	void addBoss(float x, float y);
	void bossAppear(float dt);
	void bloodChange(int x);
	void bloodChangeB(int x);
	void shieldChange(int x);
	void blueChange(int x);

	void BossBullet(float dt);
	void shieldRecover(float dt);
	void MonsterBullet(float dt);
	void MonsterDie(float dt);
	void HeroBullet(float dt);
	void showTime(float dt);
	void CD(float dt);

	CREATE_FUNC(GameScene);
};

#endif // __GAMESCENE_H__
