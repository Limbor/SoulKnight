#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "GameMap.h"

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
	firstTouch = true;
    size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	GameMap* gamemap = GameMap::create();
	addChild(gamemap);

	hero = Hero::create();
	addChild(hero);

<<<<<<< HEAD
	for (int i = 0; i < CCRANDOM_0_1() * 5 + 5; i++) {
=======
	for (int i = 0; i < CCRANDOM_0_1() * 5 + 5; i++)
	{
>>>>>>> 24db339eac34a6b40a767ea7421b986d56c54a79
		addMonster(CCRANDOM_0_1() * 2000, CCRANDOM_0_1() * 1500);
	}

	gamemap->addBarrier(this);

	stateBoard = Sprite::create("stateboard.png");
	stateBoard->setPosition(stateBoard->getContentSize().width / 2, size.height - stateBoard->getContentSize().height / 2);
	addChild(stateBoard);

	red = Sprite::create("red.png");
	red->setPosition(40 + red->getContentSize().width / 2, size.height - 11 - red->getContentSize().height / 2);
	addChild(red);
	bloodNumber = Label::create(String::createWithFormat("%i", hero->blood)->getCString(), "Arial", 18);
	bloodNumber->setPosition(red->getPosition().x, red->getPosition().y);
	addChild(bloodNumber);
	grey = Sprite::create("grey.png");
	grey->setPosition(40 + grey->getContentSize().width / 2, size.height - 35 - grey->getContentSize().height / 2);
	addChild(grey);
	shieldNumber = Label::create(String::createWithFormat("%i", hero->shield)->getCString(), "Arial", 18);
	shieldNumber->setPosition(grey->getPosition().x, grey->getPosition().y);
	addChild(shieldNumber);
	blue = Sprite::create("blue.png");
	blue->setPosition(40 + blue->getContentSize().width / 2, size.height - 59 - blue->getContentSize().height / 2);
	addChild(blue);
	blueNumber = Label::create(String::createWithFormat("%i", hero->blue)->getCString(), "Arial", 18);
	blueNumber->setPosition(blue->getPosition().x, blue->getPosition().y);
	addChild(blueNumber);

	auto* dispatcher = Director::getInstance()->getEventDispatcher();
	auto keyListener = EventListenerKeyboard::create();
	auto touchListener = EventListenerTouchOneByOne::create();
	//auto contactListener = EventListenerPhysicsContact::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	//contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
<<<<<<< HEAD
	//dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
=======

>>>>>>> 24db339eac34a6b40a767ea7421b986d56c54a79

    return true;
}

void GameScene::addMonster(int x, int y)
{
	monster = Monster::create();
	monster->setPosition(x, y);
	addChild(monster);
	monster->addHero(hero);
}

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

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	if (firstTouch) {
		if (hero->blue > 0) {
			float xEnd = touch->getLocation().x;
			float yEnd = touch->getLocation().y;
			float xStart = hero->getPosition().x;
			float yStart = hero->getPosition().y;
			auto* bullet = Bullet::createbullet(hero);
			bullet->setPosition(hero->getPosition().x, hero->getPosition().y);
			bullet->setDirection(xEnd - xStart, yEnd - yStart);
			addChild(bullet);
			bullet->setVisible(false);
			if (bullet->getPosition().x > hero->getPosition().x + hero->getContentSize().width / 2 || bullet->getPosition().x < hero->getPosition().x - hero->getContentSize().width / 2) {
				bullet->setVisible(true);
			}
			else if (bullet->getPosition().y > hero->getPosition().y + hero->getContentSize().width / 2 || bullet->getPosition().y < hero->getPosition().y - hero->getContentSize().width / 2) {
				bullet->setVisible(true);
			}
			blueChange(-1);
		}
		firstTouch = false;
	}
	else firstTouch = true;
	return true;
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{

}

void GameScene::bloodChange(int x)
{
	double scale = double(hero->blood + x) / double(hero->blood);
	hero->blood += x;
	red->setScaleX(scale);
	red->setPosition(40 + red->getContentSize().width * scale / 2, size.height - 11 - red->getContentSize().height / 2);
	bloodNumber->setString(String::createWithFormat("%i", hero->blood)->getCString());
}

void GameScene::shieldChange(int x)
{
	double scale = double(hero->shield + x) / double(hero->shield);
	hero->shield += x;
	grey->setScaleX(scale);
	grey->setPosition(40 + grey->getContentSize().width * scale / 2, size.height - 35 - grey->getContentSize().height / 2);
	shieldNumber->setString(String::createWithFormat("%i", hero->shield)->getCString());
}

void GameScene::blueChange(int x)
{
	double scale = double(hero->blue + x) / 200;
	hero->blue += x;
	blue->setScaleX(scale);
	blue->setPosition(40 + blue->getContentSize().width * scale / 2, size.height - 59 - blue->getContentSize().height / 2);
	blueNumber->setString(String::createWithFormat("%i", hero->blue)->getCString());
}
