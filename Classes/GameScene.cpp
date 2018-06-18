#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "GameMap.h"
#include <cmath>

#define PI 3.14159265

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
	recover = false;
	firstTouch = true;
	bossNumber = 1;
    size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//boss延时出现在地图中央5秒
	scheduleOnce(schedule_selector(GameScene::bossAppear), 5.0f);
	//导入地图
	GameMap* gamemap = GameMap::create();
	addChild(gamemap);

	//生成英雄
	hero = Hero::createhero(2);
	addChild(hero);
	hero->setTag(0);
	hero->getBarreir(gamemap->barrierMap, 18);

	//生成怪物，个数随即在4~6个
	/*monster_number = CCRANDOM_0_1() * 2 + 4;
	for (int i = 0; i <monster_number; i++)
	{
		monster_array[i] = Monster::create();
		monster_array[i]->setPosition(CCRANDOM_0_1() * 1800 + 100, CCRANDOM_0_1() * 1000 + 100);
		addChild(monster_array[i]);
		monster_array[i]->setTag(i + 4);
		monster_array[i]->addHero(hero);
		monster_array[i]->getBarreir(gamemap->barrierMap, 18);
	}   
	schedule(schedule_selector(GameScene::MonsterBullet), 0.5f);*/

	gamemap->addBarrier(this);

	//以下乱七八糟的
	stateBoard = Sprite::create("stateboard.png");
	stateBoard->setPosition(stateBoard->getContentSize().width / 2, size.height - stateBoard->getContentSize().height / 2);
	addChild(stateBoard);

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
	blue = Sprite::create("blue.png");
	blue->setPosition(40 + blue->getContentSize().width / 2, size.height - 59 - blue->getContentSize().height / 2);
	addChild(blue);
	blueNumber = Label::create(String::createWithFormat("%i", hero->BLUE)->getCString(), "Arial", 18);
	blueNumber->setPosition(blue->getPosition().x, blue->getPosition().y);
	addChild(blueNumber);

	bloodChange(hero->blood - hero->BLOOD);
	shieldChange(hero->shield - hero->SHIELD);
	blueChange(hero->blue - hero->BLUE);

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
	};
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    return true;
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
		if (!hero->musth && !skillCD) {
			hero->showTimeBegan();
			scheduleOnce(schedule_selector(GameScene::showTime), 5.0f);
			unschedule(schedule_selector(GameScene::HeroBullet));
			schedule(schedule_selector(GameScene::HeroBullet), hero->FiringRate);
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
			if (NodeA->getTag() == 3) {
				if (hero->shield > 0) {
					shieldChange(-1);
					if (!recover) schedule(schedule_selector(GameScene::shieldRecover), 3.0f);
					recover = true;
				}
				else bloodChange(-1);
				NodeA->removeFromParentAndCleanup(true);
			}
			else {
				if (hero->shield > 0) {
					shieldChange(-1);
					if (!recover) schedule(schedule_selector(GameScene::shieldRecover), 3.0f);
					recover = true;
				}
				else bloodChange(-1);
				NodeB->removeFromParentAndCleanup(true);
			}
			return false;
		}
		else if ((NodeA->getTag() == 1 && NodeB->getTag() == 2) || (NodeB->getTag() == 1 && NodeA->getTag() == 2)) {
			if (hero->hemophagia && hero->blood < hero->BLOOD) bloodChange(1);
			if (NodeA->getTag() == 2) {
				NodeA->removeFromParentAndCleanup(true);
			}
			else {
				NodeB->removeFromParentAndCleanup(true);
			}
			bloodChangeB(-1);
		}
		for (int i = 0; i < monster_number; i++) {
			if ((NodeA->getTag() == i + 4 && NodeB->getTag() == 2) || (NodeB->getTag() == i + 4 && NodeA->getTag() == 2))
			{
				if (hero->hemophagia) {
					srand(time(0));
					if (rand() % 2 == 1 && hero->blood < hero->BLOOD) {
						bloodChange(1);
					}
					if(hero->blue < hero->BLUE) blueChange(1);
				}
				if (NodeA->getTag() == 2)
				{
					NodeA->removeFromParentAndCleanup(true);
				}
				else
				{
					NodeB->removeFromParentAndCleanup(true);
				}
				monster_array[i]->bloodM--;
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
	blueChange(-1);
}
//下面是怪物的操作
//怪物的行为
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

}
//下面是boss的操作
//添加boss
void GameScene::addBoss(float x, float y)
{
	boss = Boss::createboss(bossNumber);
	boss->setPosition(x, y);
	addChild(boss);
	boss->addHero(hero);
	schedule(schedule_selector(GameScene::BossBullet), 0.6f);
	schedule(schedule_selector(GameScene::BossFlash), 5.0f);
	boss->setTag(1);
	boss->getBarreir(hero->barrier, 18);
	boss->setLocalZOrder(hero->getLocalZOrder());
}
//boss延时出现
void GameScene::bossAppear(float dt)
{
	addBoss(size.width / 2, size.height / 2);
	redB = Sprite::create("red.png");
	redB->setPosition(size.width / 2, size.height - redB->getContentSize().height / 2);
	addChild(redB);
	bloodNumberB = Label::create(String::createWithFormat("%i", boss->blood)->getCString(), "Arial", 18);
	bloodNumberB->setPosition(redB->getPosition().x, redB->getPosition().y);
	addChild(bloodNumberB);
}
//boss发射子弹
void GameScene::BossBullet(float dt) {
	if (bossNumber == 1) {
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
	else  if (bossNumber == 2 || bossNumber == 3) {
		auto* bullet = Bullet::createbullet(boss);
		bullet->setPosition(boss->getPosition().x, boss->getPosition().y);
		bullet->setDirection(hero->getPosition().x - boss->getPosition().x, hero->getPosition().y - boss->getPosition().y);
		addChild(bullet);
		bullet->setTag(4);
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

void GameScene::BossFlash(float dt)
{
	if (bossNumber == 3) {
		boss->setPosition(hero->getPosition().x + hero->getContentSize().width / 2, hero->getPosition().y + hero->getContentSize().height / 2);
		for (int i = 0; i < 4; i++) {
			auto* bullet = Bullet::createbullet(boss);
			bullet->setPosition(hero->getPosition().x, hero->getPosition().y);
			bullet->setDirection(-1, -1);
			addChild(bullet);
			bullet->setTag(4);
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
	else  if (bossNumber == 2) {
		for (int i = 0; i < 4; i++) {
			auto* bullet = Bullet::createbullet(boss);
			switch (i)
			{
			case 0:  bullet->setPosition(hero->getPosition().x + hero->getContentSize().width * 2, hero->getPosition().y + hero->getContentSize().height * 2);
				bullet->setDirection(-1, -1);
				break;
			case 1:  bullet->setPosition(hero->getPosition().x - hero->getContentSize().width * 2, hero->getPosition().y - hero->getContentSize().height * 2);
				bullet->setDirection(1, 1);
				break;
			case 2:  bullet->setPosition(hero->getPosition().x - hero->getContentSize().width * 2, hero->getPosition().y + hero->getContentSize().height * 2);
				bullet->setDirection(1, -1);
				break;
			case 3:  bullet->setPosition(hero->getPosition().x + hero->getContentSize().width * 2, hero->getPosition().y - hero->getContentSize().height * 2);
				bullet->setDirection(-1, 1);
				break;
			default:
				break;
			}
			addChild(bullet);
			bullet->setTag(4);
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
//下面是对战情况的显示情况
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
	double scale = double(boss->blood + x) / 60;
	boss->blood += x;
	redB->setScaleX(scale);
	redB->setPosition(size.width / 2, size.height  - redB->getContentSize().height / 2);
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
	blue->setScaleX(scale);
	blue->setPosition(40 + blue->getContentSize().width * scale / 2, size.height - 59 - blue->getContentSize().height / 2);
	blueNumber->setString(String::createWithFormat("%i", hero->blue)->getCString());
}

void GameScene::shieldRecover(float dt)
{
	if (hero->shield < hero->SHIELD) {
		shieldChange(1);
	}
	else
	{
		unschedule(schedule_selector(GameScene::shieldRecover));
		recover = false;
	}
}

void GameScene::showTime(float dt)
{
	hero->showTimeEnded();
	skillCD = true;
	scheduleOnce(schedule_selector(GameScene::CD), 10);
	unschedule(schedule_selector(GameScene::HeroBullet));
	schedule(schedule_selector(GameScene::HeroBullet), hero->FiringRate);
}

void GameScene::CD(float dt)
{
	skillCD = false;
}
