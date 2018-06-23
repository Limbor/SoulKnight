#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "GameMap.h"
#include "NewOrExit.h"
#include <cmath>

#define PI 3.14159265

USING_NS_CC;

Scene* GameScene::createScene(int sceneNumber, int heroNumber, int mapNumber, int blood, int shield, int blue ,int blueReduce, int damage)
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	auto layer = GameScene::createscene(sceneNumber, heroNumber, mapNumber, blood, shield, blue, blueReduce, damage);
	scene->addChild(layer);
	return scene;
}

GameScene* GameScene::createscene(int sceneNumber, int heroNumber, int mapNumber, int blood, int shield, int blue, int blueReduce, int damage)
{
	GameScene* enemy = new GameScene();
	if (enemy && enemy->init())
	{
		enemy->autorelease();
		enemy->enemyInit(sceneNumber, heroNumber, mapNumber, blood, shield, blue, blueReduce, damage);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	return true;
}

void GameScene::enemyInit(int sceneNumber, int heroNumber, int map, int blood, int shield, int blue, int blueReduce, int damage)
{
	this->sceneNumber = sceneNumber;
	this->heroNumber = heroNumber;
	recover = false;
	firstTouch = true;
    size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	srand(time(0));
	mapNumber = rand() % 3 + 1;
	if (sceneNumber % 2 == 1) mapNumber = 2 * mapNumber - 1;
	else mapNumber = map;
	bossNumber = mapNumber;
	//boss延时出现在地图中央5秒
	if (sceneNumber % 2 == 0) scheduleOnce(schedule_selector(GameScene::bossAppear), 5.0f);
	//导入地图
	GameMap* gamemap = GameMap::createmap(mapNumber);
	addChild(gamemap);
	//生成英雄
	hero = Hero::createhero(heroNumber);
	addChild(hero);
	hero->getBarreir(gamemap->barrierMap, 18);
	hero->blueReduce = blueReduce;
	hero->damage = damage;

	toolNumber = rand() % 3 + 1;
	tool = Tool::createtool(toolNumber);
	tool->setVisible(false);
	tool->setPosition(0, 0);
	addChild(tool);

	//生成怪物，个数随即在4~6个
	if (sceneNumber % 2 == 1) {
		monster_number = CCRANDOM_0_1() * 2 + 4;
		scheduleOnce(schedule_selector(GameScene::monsterAppear), 3.0f);
	}
	gamemap->addBarrier(this);

	//以下乱七八糟的
	stateBoard = Sprite::create("stateboard.png");
	stateBoard->setPosition(stateBoard->getContentSize().width / 2, size.height - stateBoard->getContentSize().height / 2);
	addChild(stateBoard);

	for (int i = 0;i < 5;i++) {
		cdBlue[i] = DrawNode::create();
		cdGray[i] = DrawNode::create();
		cdBlue[i]->drawDot(Vec2(40 * i + 20, size.height - 120), 7, cocos2d::Color4F(0.48f, 0.67f, 0.94f, 1.0f));
		cdGray[i]->drawDot(Vec2(40 * i + 20, size.height - 120), 7, cocos2d::Color4F(0.65f, 0.65f, 0.65f, 1.0f));
		addChild(cdBlue[i]);
		addChild(cdGray[i]);
		cdGray[i]->setVisible(false);
	}

	red = Sprite::create("red.png");
	red->setPosition(40 + red->getContentSize().width / 2, size.height - 11 - red->getContentSize().height / 2);
	addChild(red);
	bloodNumber = Label::create(String::createWithFormat("%i", hero->BLOOD)->getCString(), "Arial", 18);
	bloodNumber->setPosition(red->getPosition().x, red->getPosition().y);
	addChild(bloodNumber);
	grey = Sprite::create("grey.png");
	grey->setPosition(40 + grey->getContentSize().width / 2, size.height - 35 - grey->getContentSize().height / 2);
	addChild(grey);
	shieldNumber = Label::create(String::createWithFormat("%i", hero->SHIELD)->getCString(), "Arial", 18);
	shieldNumber->setPosition(grey->getPosition().x, grey->getPosition().y);
	addChild(shieldNumber);
	this->blue = Sprite::create("blue.png");
	this->blue->setPosition(40 + this->blue->getContentSize().width / 2, size.height - 59 - this->blue->getContentSize().height / 2);
	addChild(this->blue);
	this->blueNumber = Label::create(String::createWithFormat("%i", hero->BLUE)->getCString(), "Arial", 18);
	this->blueNumber->setPosition(this->blue->getPosition().x, this->blue->getPosition().y);
	addChild(this->blueNumber);

	bloodChange(blood - hero->BLOOD);
	shieldChange(shield - hero->SHIELD);
	blueChange(blue - hero->BLUE);

	if (hero->shield < hero->SHIELD) {
		schedule(schedule_selector(GameScene::shieldRecover), 3.0f);
		recover = true;
	}

	auto* dispatcher = Director::getInstance()->getEventDispatcher();
	auto keyListener = EventListenerKeyboard::create();
	auto touchListener = EventListenerTouchOneByOne::create();
	auto contactListener = EventListenerPhysicsContact::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	touchListener->onTouchEnded = [=](Touch* touch, Event* event) {
		unschedule(schedule_selector(GameScene::HeroBullet));
		hero->fire = false;
	};
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}
//下面是英雄的操作
void GameScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event)
{
	hero->stopAllActions();
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		hero->setSpeedy(1);
		if(hero->heroRight) hero->heroRightMove();
		else hero->heroLeftMove();
		break;
	case EventKeyboard::KeyCode::KEY_S:
		hero->setSpeedy(-1);
		if (hero->heroRight) hero->heroRightMove();
		else hero->heroLeftMove();
		break;
	case EventKeyboard::KeyCode::KEY_A:
		hero->setSpeedx(-1);
		if (hero->heroRight) hero->frameChange();
		hero->heroLeftMove();
		hero->heroRight = false;
		break;
	case EventKeyboard::KeyCode::KEY_D:
		hero->setSpeedx(1);
		if (!hero->heroRight) hero->frameChange();
		hero->heroRightMove();
		hero->heroRight = true;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		if (!skillCD) {
			skillCD = true;
			hero->showTimeBegan();
			scheduleOnce(schedule_selector(GameScene::showTime), 5.0f);
			schedule(schedule_selector(GameScene::bTOg), 1.0f);
			if (hero->fire && heroNumber == 1) {
				unschedule(schedule_selector(GameScene::HeroBullet));
				schedule(schedule_selector(GameScene::HeroBullet), hero->FiringRate);
			}
			else if (heroNumber == 2) {

			}
		}
	}
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event *event)
{
	hero->stopAllActions();
	if (!hero->heroRight) {
		hero->heroLeftStatic();
	}
	else if (hero->heroRight) {
		hero->heroRightStatic();
	}
	if(keycode == EventKeyboard::KeyCode::KEY_A || keycode == EventKeyboard::KeyCode::KEY_D) hero->setSpeedx(0);
	else if(keycode == EventKeyboard::KeyCode::KEY_W || keycode == EventKeyboard::KeyCode::KEY_S)hero->setSpeedy(0);
}
//判断英雄发出子弹的方向
bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	if (firstTouch) {
		if (hero->blue > 0) {
			xEnd = touch->getLocation().x;
			yEnd = touch->getLocation().y;
			hero->fire = true;
			schedule(schedule_selector(GameScene::HeroBullet), hero->FiringRate);
		}
		firstTouch = false;
	}
	else firstTouch = true;
	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{
	if (hero->blue > 0) {
		xEnd = touch->getLocation().x;
		yEnd = touch->getLocation().y;
	}
}

bool GameScene::onContactBegin(PhysicsContact &contact)
{
	auto NodeA = contact.getShapeA()->getBody()->getNode();
	auto NodeB = contact.getShapeB()->getBody()->getNode();
	if (NodeA && NodeB) {
		if ((NodeA->getTag() == 0 && NodeB->getTag() == 3) || (NodeB->getTag() == 0 && NodeA->getTag() == 3)) {
			if (hero->magicNumber < 3) {
				if (hero->shield > 0) {
					shieldChange(-1);
					if (!recover) schedule(schedule_selector(GameScene::shieldRecover), 3.0f);
					recover = true;
				}
				else bloodChange(-1);
				if (hero->blood <= 0) {
					auto scene = NewOrExit::createScene(0);
					Director::getInstance()->replaceScene(scene);
				}
			}
			if (NodeA->getTag() == 3) {
				NodeA->removeFromParentAndCleanup(true);
			}
			else {
				NodeB->removeFromParentAndCleanup(true);
			}
		}
		else if ((NodeA->getTag() == 1 && NodeB->getTag() == 2) || (NodeB->getTag() == 1 && NodeA->getTag() == 2)) {
			if (hero->hemophagia) {
				srand(time(0));
				if (rand() % 5 == 1 && hero->blood < hero->BLOOD) {
					bloodChange(1);
				}
				if (hero->blue < hero->BLUE) {
					if (hero->blue + 2 < hero->BLUE) blueChange(2);
					else blueChange(hero->BLUE - hero->blue);
				}
			}
			if (NodeA->getTag() == 2) {
				NodeA->removeFromParentAndCleanup(true);
			}
			else {
				NodeB->removeFromParentAndCleanup(true);
			}
			bloodChangeB(-hero->damage);
			if (boss->blood <= 0 && !next) {
				next = true;
				tool->setVisible(true);
				tool->setPosition(boss->getPosition());
				scheduleOnce(schedule_selector(GameScene::nextScene), 5.0f);
			}
		}
		else if ((NodeA->getTag() == 0 && NodeB->getTag() == 13) || (NodeB->getTag() == 13 && NodeA->getTag() == 0)) {
			if (NodeA->getTag() == 13) {
				NodeA->removeFromParentAndCleanup(true);
			}
			else {
				NodeB->removeFromParentAndCleanup(true);
			}
			bloodChange(hero->BLOOD - hero->blood);
		}
		else if ((NodeA->getTag() == 0 && NodeB->getTag() == 14) || (NodeB->getTag() == 14 && NodeA->getTag() == 0)) {
			if (NodeA->getTag() == 14) {
				NodeA->removeFromParentAndCleanup(true);
			}
			else {
				NodeB->removeFromParentAndCleanup(true);
			}
			blueChange(hero->BLUE - hero->blue);
		}
		else if ((NodeA->getTag() == 0 && NodeB->getTag() == 15) || (NodeB->getTag() == 15 && NodeA->getTag() == 0)) {
			if (NodeA->getTag() == 15) {
				NodeA->removeFromParentAndCleanup(true);
			}
			else {
				NodeB->removeFromParentAndCleanup(true);
			}
			hero->damage++;
			hero->blueReduce++;

		}
		if (!nextMap()) {
			for (int i = 0; i < monster_number; i++) {
				if ((NodeA->getTag() == i + 4 && NodeB->getTag() == 2) || (NodeB->getTag() == i + 4 && NodeA->getTag() == 2))
				{
					if (hero->hemophagia) {
						srand(time(0));
						if (rand() % 5 == 1 && hero->blood < hero->BLOOD) {
							bloodChange(1);
						}
						if (hero->blue < hero->BLUE) {
							if (hero->blue + 2 < hero->BLUE) blueChange(2);
							else blueChange(hero->BLUE - hero->blue);
						}
					}
					if (NodeA->getTag() == 2)
					{
						NodeA->removeFromParentAndCleanup(true);
					}
					else
					{
						NodeB->removeFromParentAndCleanup(true);
					}
					monster_array[i]->bloodM -= hero->damage;
				}
			}
		}
	}
	return false;
}

void GameScene::HeroBullet(float dt)
{
	float xStart = hero->getPosition().x;
	float yStart = hero->getPosition().y;
	float rotation = atan((yEnd - yStart) / (xEnd - xStart)) * 180 / PI;
	if ((hero->heroRight && (xEnd - xStart) < 0)) {
		hero->stopAllActions();
		hero->heroRight = false;
		if (hero->getSpeedx() != 0 || hero->getSpeedy() != 0) hero->heroLeftMove();
		else hero->heroLeftStatic();
	}
	else if ((!hero->heroRight && (xEnd - xStart) > 0)) {
		hero->stopAllActions();
		hero->heroRight = true;
		if (hero->getSpeedx() != 0 || hero->getSpeedy() != 0) hero->heroRightMove();
		else hero->heroRightStatic();
	}
	hero->gun->setRotation(-rotation);
	auto* bullet = Bullet::createbullet(hero);
	bullet->setDirection(xEnd - xStart, yEnd - yStart);
	if (hero->heroRight) {
		float x = 50;
		float y = 50 * (yEnd - yStart) / (xEnd - xStart);
		if (y >= 68.0f) {
			y = 68.0f;
			x = 68.0f / ((yEnd - yStart) / (xEnd - xStart));
		}
		else if (y <= -32.0f) {
			y = -32.0f;
			x = -32.0f / ((yEnd - yStart) / (xEnd - xStart));
		}
		bullet->setPosition(hero->getPosition().x + x, hero->getPosition().y - 18 + y);
	}
	else {
		float x = -50;
		float y = -50 * (yEnd - yStart) / (xEnd - xStart);
		if (y >= 68.0f) {
			y = 68.0f;
			x = 68.0f / ((yEnd - yStart) / (xEnd - xStart));
		}
		else if (y <= -32.0f) {
			y = -32.0f;
			x = -32.0f / ((yEnd - yStart) / (xEnd - xStart));
		}
		bullet->setPosition(hero->getPosition().x + x, hero->getPosition().y - 18 + y);
	}
	addChild(bullet);
	bullet->getBarreir(hero->barrier, 18);
	bullet->setVisible(false);
	blueChange(-hero->blueReduce);
	if (hero->blue <= 0) {
		unschedule(schedule_selector(GameScene::HeroBullet));
	}
}
//下面是怪物的操作
//怪物的行为
void GameScene::monsterAppear(float dt)
{
	for (int k = 0; k < monster_number; k++)
	{
		monster[k] = 1;
		monster_array[k] = Monster::create();
		monster_p_x = CCRANDOM_0_1() * 1800 + 100;
		monster_p_y = CCRANDOM_0_1() * 800 + 200;
		for (int n = 0; n < 10000; n++)
		{
			int num = 0;
			for (int i = 0; i < 18; i++)
			{
				for (int j = 0; j < 34; j++)
				{
					if (barrier[17 - i][j] == 1)
					{
						if ((monster_p_x + monster_array[k]->getContentSize().width / 2) >(20 + 60 * j) || (monster_p_x - monster_array[k]->getContentSize().width / 2) < (50 + 60 * j) || (monster_p_y + monster_array[k]->getContentSize().height / 2) > (35 + 60 * i - 90) || (monster_p_y - monster_array[k]->getContentSize().height / 2) < (35 + 60 * i - 10))
						{
							num++;
						}
					}
				}
			}
			if (num != 0)
			{
				monster_p_x = CCRANDOM_0_1() * 1800 + 100;
				monster_p_y = CCRANDOM_0_1() * 800 + 200;
			}
			else
				break;
		}
		monster_array[k]->setLocalZOrder(0);
		monster_array[k]->setPosition(monster_p_x, monster_p_y);
		addChild(monster_array[k]);
		monster_array[k]->setTag(k + 4);
		monster_array[k]->addHero(hero);
		monster_array[k]->getBarreir(hero->barrier, 18);
	}
	schedule(schedule_selector(GameScene::MonsterBullet), 0.5f);
	schedule(schedule_selector(GameScene::MonsterDie), 0.5f);

}

void GameScene::MonsterBullet(float dt)
{
	for (int i = 0; i < monster_number; i++)
	{
		if (monster_array[i]->bloodM > 0)
		{
			monster_array[i]->distance = (monster_array[i]->getPosition().x - hero->getPosition().x)*
			(monster_array[i]->getPosition().x - hero->getPosition().x) + (monster_array[i]->getPosition().y
			- hero->getPosition().y)*(monster_array[i]->getPosition().y - hero->getPosition().y);
			if (monster_array[i]->distance < 180000)
			{
				auto* bullet = Bullet::createbullet(monster_array[i]);
				bullet->getBarreir(hero->barrier, 18);
				bullet->setPosition(monster_array[i]->getPosition().x, monster_array[i]->getPosition().y);
				bullet->setDirection(hero->getPosition().x - monster_array[i]->getPosition().x, hero->getPosition().y - monster_array[i]->getPosition().y);
				addChild(bullet);
			}
		}
	}
}  

void GameScene::MonsterDie(float dt)
{
	for (int i = 0; i < monster_number; i++)
	{
		if (monster_array[i]->bloodM <= 0 && monster_array[i]->getOpacity() != 0)
		{
			monster_array[i]->runAction(FadeOut::create(0.2f));
		}
		if (monster_array[i]->getOpacity() == 0)
		{
			monster_array[i]->setPosition(5000, 5000);
			monster[i] = 0;
		}
	}
	if (nextMap() && !next) {
		tool->setVisible(true);
		tool->setPosition(size.width / 2, size.height / 2);
		scheduleOnce(schedule_selector(GameScene::nextScene), 5.0f);
		next = true;
	}
}
//下面是boss的操作
//添加boss
void GameScene::addBoss(float x, float y)
{
	boss = Boss::createboss(bossNumber / 2);
	boss->setPosition(x, y);
	addChild(boss);
	boss->addHero(hero);
	schedule(schedule_selector(GameScene::BossBullet), 0.6f);
	schedule(schedule_selector(GameScene::BossFlash), 8.0f);
	schedule(schedule_selector(GameScene::BossDie), 0.2f);
	boss->getBarreir(hero->barrier, 18);
	boss->setGlobalZOrder(hero->getGlobalZOrder());
}
//boss延时出现
void GameScene::bossAppear(float dt)
{
	addBoss(size.width / 2, size.height / 2);
	redBframe = Sprite::create("redBframe.png");
	redBframe->setPosition(size.width / 2, size.height - redBframe->getContentSize().height / 2 - 5);
	addChild(redBframe);
	redB = Sprite::create("redB.png");
	redB->setPosition(size.width / 2, size.height - redB->getContentSize().height / 2 - 10);
	addChild(redB);
	bloodNumberB = Label::create(String::createWithFormat("%i", boss->blood)->getCString(), "Arial", 18);
	bloodNumberB->setPosition(redB->getPosition().x, redB->getPosition().y);
	addChild(bloodNumberB);
}
//boss发射子弹
void GameScene::BossBullet(float dt) {
	if (boss->blood > 0) {
		if (bossNumber / 2 == 1) {
			for (int i = 0; i < 12; i++) {
				auto* bullet = Bullet::createbullet(boss);
				bullet->setPosition(boss->getPosition().x, boss->getPosition().y);
				switch (i)
				{
				case 0:  bullet->setDirection(1, 0);   break;
				case 1:  bullet->setDirection(2, 1);   break;
				case 2:  bullet->setDirection(1, 2);   break;
				case 3:  bullet->setDirection(0, 1);   break;
				case 4:  bullet->setDirection(-1, 2);   break;
				case 5:  bullet->setDirection(-2, 1);   break;
				case 6:  bullet->setDirection(-1, 0);   break;
				case 7:  bullet->setDirection(-2, -1);   break;
				case 8:  bullet->setDirection(-1, -2);   break;
				case 9:  bullet->setDirection(0, -1);   break;
				case 10:  bullet->setDirection(1, -2);   break;
				case 11:  bullet->setDirection(2, -1);   break;
				}
				addChild(bullet);
				bullet->getBarreir(hero->barrier, 18);
				bullet->setVisible(false);
				if (bullet->getPosition().x > boss->getPosition().x + boss->getContentSize().width / 2 ||
					bullet->getPosition().x < boss->getPosition().x - boss->getContentSize().width / 2) {
					bullet->setVisible(true);
				}
				else if (bullet->getPosition().y > boss->getPosition().y + boss->getContentSize().width / 2 ||
					bullet->getPosition().y < boss->getPosition().y - boss->getContentSize().width / 2) {
					bullet->setVisible(true);
				}
			}
		}
		else  if (bossNumber / 2 == 2 || bossNumber / 2 == 3) {
			auto* bullet = Bullet::createbullet(boss);
			bullet->setPosition(boss->getPosition().x, boss->getPosition().y);
			bullet->setDirection(hero->getPosition().x - boss->getPosition().x, hero->getPosition().y - boss->getPosition().y);
			addChild(bullet);
			bullet->getBarreir(hero->barrier, 18);
			bullet->setVisible(false);
			if (bullet->getPosition().x > boss->getPosition().x + boss->getContentSize().width / 2 ||
				bullet->getPosition().x < boss->getPosition().x - boss->getContentSize().width / 2) {
				bullet->setVisible(true);
			}
			else if (bullet->getPosition().y > boss->getPosition().y + boss->getContentSize().width / 2 ||
				bullet->getPosition().y < boss->getPosition().y - boss->getContentSize().width / 2) {
				bullet->setVisible(true);
			}
		}
	}
}

void GameScene::BossFlash(float dt)
{
	if (hero->blood > 0) {
		if (bossNumber / 2 == 3) {
			boss->setPosition(hero->getPosition().x + hero->getContentSize().width / 2, hero->getPosition().y + hero->getContentSize().height / 2);
			for (int i = 0; i < 3; i++) {
				auto* bullet = Bullet::createbullet(boss);
				bullet->setPosition(hero->getPosition().x, hero->getPosition().y);
				bullet->setDirection(-1, -1);
				addChild(bullet);
				bullet->getBarreir(hero->barrier, 18);
				bullet->setVisible(false);
				if (bullet->getPosition().x > boss->getPosition().x + boss->getContentSize().width / 2 ||
					bullet->getPosition().x < boss->getPosition().x - boss->getContentSize().width / 2) {
					bullet->setVisible(true);
				}
				else if (bullet->getPosition().y > boss->getPosition().y + boss->getContentSize().width / 2 ||
					bullet->getPosition().y < boss->getPosition().y - boss->getContentSize().width / 2) {
					bullet->setVisible(true);
				}
			}
		}
		else  if (bossNumber / 2 == 2) {
			for (int i = 0; i < 6; i++) {
				auto* bullet = Bullet::createbullet(boss);
				switch (i)
				{
				case 0:  bullet->setPosition(hero->getPosition().x + hero->getContentSize().width * 1, hero->getPosition().y + hero->getContentSize().height * 2);
					bullet->setDirection(-1, -2);
					break;
				case 1:  bullet->setPosition(hero->getPosition().x + hero->getContentSize().width * (-1), hero->getPosition().y + hero->getContentSize().height * 2);
					bullet->setDirection(1, -2);
					break;
				case 2:  bullet->setPosition(hero->getPosition().x + hero->getContentSize().width * (-1), hero->getPosition().y + hero->getContentSize().height * (-2));
					bullet->setDirection(1, 2);
					break;
				case 3:  bullet->setPosition(hero->getPosition().x + hero->getContentSize().width * 1, hero->getPosition().y + hero->getContentSize().height * (-2));
					bullet->setDirection(-1, 2);
					break;
				case 4:  bullet->setPosition(hero->getPosition().x + hero->getContentSize().width * 2.24, hero->getPosition().y);
					bullet->setDirection(-1, 0);
					break;
				case 5:  bullet->setPosition(hero->getPosition().x + hero->getContentSize().width * (-2.24), hero->getPosition().y);
					bullet->setDirection(1, 0);
					break;
				default:
					break;
				}
				addChild(bullet);
				bullet->getBarreir(hero->barrier, 18);
				bullet->setVisible(false);
				if (bullet->getPosition().x > boss->getPosition().x + boss->getContentSize().width / 2 ||
					bullet->getPosition().x < boss->getPosition().x - boss->getContentSize().width / 2) {
					bullet->setVisible(true);
				}
				else if (bullet->getPosition().y > boss->getPosition().y + boss->getContentSize().width / 2 ||
					bullet->getPosition().y < boss->getPosition().y - boss->getContentSize().width / 2) {
					bullet->setVisible(true);
				}
			}
		}
	}
}

void GameScene::BossDie(float dt)
{
	if (boss->blood <= 0 && boss->getOpacity() != 0)
	{
		boss->runAction(FadeOut::create(0.2f));
	}
	if (boss->getOpacity() == 0 && sceneNumber == 6)
	{
		auto scene = NewOrExit::createScene(1);
		Director::getInstance()->replaceScene(scene);
	}
}

void GameScene::shieldRecover(float dt)
{
	if (hero->shield < hero->SHIELD) {
		shieldChange(1);
	}
	else {
		unschedule(schedule_selector(GameScene::shieldRecover));
		recover = false;
	}
}

void GameScene::showTime(float dt)
{
	hero->showTimeEnded();
	scheduleOnce(schedule_selector(GameScene::CD), 10.0f);
	schedule(schedule_selector(GameScene::gTOb), 2.0f);
	if (hero->fire && heroNumber == 1) {
		unschedule(schedule_selector(GameScene::HeroBullet));
		schedule(schedule_selector(GameScene::HeroBullet), hero->FiringRate);
	}
}

void GameScene::CD(float dt)
{
	skillCD = false;
}

void GameScene::bTOg(float dt)
{
	cdBlue[4 - times]->setVisible(false);
	cdGray[4 - times]->setVisible(true);
	times++;
	switch(hero->magicNumber) {
		case 1:
			if(hero->blood < hero->BLOOD) bloodChange(1);
			break;
		case 2:
			if (hero->blue < hero->BLUE) {
				if(hero->blue + 10 < hero->BLUE) blueChange(10);
				else blueChange(hero->BLUE - hero->blue);
			}
			break;
		default:
			break;
	}
	if (times == 5) {
		times = 0;
		unschedule(schedule_selector(GameScene::bTOg));
	}
}

void GameScene::gTOb(float dt)
{
	cdBlue[times]->setVisible(true);
	cdGray[times]->setVisible(false);
	times++;
	if (times == 5) {
		times = 0;
		unschedule(schedule_selector(GameScene::gTOb));
	}
}

void GameScene::nextScene(float dt)
{
	auto scene = GameScene::createScene(++sceneNumber, heroNumber, ++mapNumber, hero->blood, hero->shield, hero->blue, hero->blueReduce, hero->damage);
	Director::getInstance()->replaceScene(scene);
}

void GameScene::bloodChange(int x)
{
	double scale = double(hero->blood + x) / hero->BLOOD;
	hero->blood += x;
	red->setScaleX(scale);
	red->setPosition(40 + red->getContentSize().width * scale / 2, size.height - 11 - red->getContentSize().height / 2);
	bloodNumber->setString(String::createWithFormat("%i", hero->blood)->getCString());
}

void GameScene::bloodChangeB(int x)
{
	double scale = double(boss->blood + x) / boss->BLOOD;
	boss->blood += x;
	if (boss->blood < 0){
		boss->blood = 0;
		scale = 0;
	}
	redB->setScaleX(scale);
	redB->setPosition(size.width / 4 + 12 + redB->getContentSize().width * scale / 2, size.height - redB->getContentSize().height / 2 - 10);
	bloodNumberB->setString(String::createWithFormat("%i", boss->blood)->getCString());
}

void GameScene::shieldChange(int x)
{
	double scale = double(hero->shield + x) / hero->SHIELD;
	hero->shield += x;
	grey->setScaleX(scale);
	grey->setPosition(40 + grey->getContentSize().width * scale / 2, size.height - 35 - grey->getContentSize().height / 2);
	shieldNumber->setString(String::createWithFormat("%i", hero->shield)->getCString());
}

void GameScene::blueChange(int x)
{
	double scale = double(hero->blue + x) / hero->BLUE;
	hero->blue += x;
	if (hero->blue < 0) {
		scale = 0;
		hero->blue = 0;
	}
	blue->setScaleX(scale);
	blue->setPosition(40 + blue->getContentSize().width * scale / 2, size.height - 59 - blue->getContentSize().height / 2);
	blueNumber->setString(String::createWithFormat("%i", hero->blue)->getCString());
}

bool GameScene::nextMap()
{
	for (int i = 0;i < monster_number;i++) {
		if(monster[i] == 1) return false;
	}
	return true;
}
