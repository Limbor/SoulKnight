#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Hero.h"
#include "Bullet.h"
#include "Monster.h"
#include "Boss.h"
#include "Tool.h"

class GameScene : public cocos2d::Scene
{
private:
	int monster_p_x;
	int monster_p_y;
	int barrier[18][34];
	int monster[10] = { 0 };		
	int times = 0;
	int sceneNumber;
	int mapNumber;
	int monster_number;
	int heroNumber;
	int bossNumber;
	int toolNumber;
	float xEnd;
	float yEnd;
	bool skillCD = false;
	bool firstTouch;
	bool recover;
	bool next = false;
	Size size;
	Hero* hero;
	Boss* boss;
	Monster* monster_array[10];
	Tool* tool;
	Sprite* stateBoard;
	Sprite* red;
	Sprite* redB;
	Sprite* redBframe;
	Sprite* blue;
	Sprite* grey;
	Label* bloodNumber;
	Label* bloodNumberB;
	Label* shieldNumber;
	Label* blueNumber;
	DrawNode* cdBlue[5];
	DrawNode* cdGray[5];
public:
    static cocos2d::Scene* createScene(int sceneNumber, int heroNumber, int mapNumber, int blood, int shield, int blue, int blueReduce, int damage);
    virtual bool init();
	static GameScene* createscene(int sceneNumber, int heroNumber, int mapNumber, int blood, int shield, int blue, int blueReduce, int damage);
	void enemyInit(int sceneNumber, int heroNumber, int map, int blood, int shield, int blue, int blueReduce, int damage);
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual bool onContactBegin(PhysicsContact &contact);

	void addBoss(float x, float y);
	void bloodChange(int x);
	void bloodChangeB(int x);
	void shieldChange(int x);
	void blueChange(int x);
	bool nextMap();

	void bossAppear(float dt);
	void monsterAppear(float dt);
	void BossBullet(float dt);
	void BossFlash(float dt);
	void BossDie(float dt);
	void shieldRecover(float dt);
	void MonsterBullet(float dt);
	void MonsterDie(float dt);
	void HeroBullet(float dt);
	void showTime(float dt);
	void CD(float dt);
	void bTOg(float dt);
	void gTOb(float dt);
	void nextScene(float dt);

	CREATE_FUNC(GameScene);
};

#endif // __GAMESCENE_H__
