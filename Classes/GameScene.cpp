#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "GameMap.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
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
	
	auto* gamemap = GameMap::createLayer();
	addChild(gamemap);

	hero = Hero::create();
	addChild(hero);

	addBarrier();

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
	auto* keyListener = EventListenerKeyboard::create();
	auto* touchListener = EventListenerTouchOneByOne::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
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
			auto* bullet = Bullet::create();
			bullet->setPosition(hero->getPosition().x, hero->getPosition().y);
			bullet->setDirection(xEnd - xStart, yEnd - yStart);
			addChild(bullet);
			bullet->setVisible(false);
			bullet->addHero(hero);
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

void GameScene::addBarrier() {
	Sprite* wall[34];
	for (int i = 0;i < 34;i++) {
		wall[i] = Sprite::create("27.wall1.png");
		wall[i]->setPosition(33 + 60 * i, 35 + 30);
		addChild(wall[i]);
	}
	int treemap[14][32] = {
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
	};
	Sprite* tree[14][32];

	for (int i = 0;i < 14;i++) {
		for (int j = 0;j < 32;j++) {
			switch (treemap[13 - i][j]) {
			case 0:break;
			case 1:tree[13 - i][j] = Sprite::create("29.tree1.png");
				tree[13 - i][j]->setPosition(93 + 60 * j, 200 + 60 * i);
				addChild(tree[13 - i][j]);break;
			}
		}
	}
	int boxmap[14][32] = {
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,4,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,5,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,1,3,1,1,3,3,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,5,0,0 },
	{ 0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,4,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
	};
	Sprite* box[14][32];
	for (int i = 0;i < 14;i++) {
		for (int j = 0;j < 32;j++) {
			switch (boxmap[13 - i][j]) {
			case 0:break;
			case 1:box[13 - i][j] = Sprite::create("28.bigstone1.png");
				box[13 - i][j]->setPosition(93 + 60 * j, 185 + 60 * i);
				addChild(box[13 - i][j]);break;
			case 2:box[13 - i][j] = Sprite::create("30.fire1.png");
				box[13 - i][j]->setPosition(93 + 60 * j, 185 + 60 * i);
				addChild(box[13 - i][j]);break;
			case 3:box[13 - i][j] = Sprite::create("31.bigstone2.png");
				box[13 - i][j]->setPosition(93 + 60 * j, 185 + 60 * i);
				addChild(box[13 - i][j]);break;
			case 4:box[13 - i][j] = Sprite::create("32.box1.png");
				box[13 - i][j]->setPosition(93 + 60 * j, 185 + 60 * i);
				addChild(box[13 - i][j]);break;
			case 5:box[13 - i][j] = Sprite::create("33.box2.png");
				box[13 - i][j]->setPosition(93 + 60 * j, 185 + 60 * i);
				addChild(box[13 - i][j]);break;
			}
		}
	}
}
