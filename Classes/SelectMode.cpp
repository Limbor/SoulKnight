#include "SelectMode.h"
#include "Room.h"
#include "SelectHero.h"
#include "SimpleAudioEngine.h"
#include <string>

USING_NS_CC;

//创建场景
Scene* SelectMode::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectMode::create();

	scene->addChild(layer);
	//返回场景
	return scene;
}

//设置按钮
bool SelectMode::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//设置背景图片
	auto bg = Sprite::create("bg2.png");
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 200);
	addChild(bg);

	/*	//设置标签
	string str = "";
	auto myLabel = Label::createWithTTF(str, "fonts/arial.ttf", 65);
	myLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
	origin.y + visibleSize.height - myLabel->getContentSize().height));
	myLabel->setColor(Color3B(0, 0, 0));
	this->addChild(myLabel, 1);             */

	//设置“单人模式”按钮
	auto SingleItem = MenuItemImage::create("button-single.png",
		                             "buttonsingle-click.png",
		         CC_CALLBACK_1(SelectMode::menuSingleMode, this));

	//设置“单人模式”按钮位置
	SingleItem->setPosition(Vec2(origin.x + SingleItem->getContentSize().width / 2+80,
		origin.y + SingleItem->getContentSize().height / 2 + 120));
	

	//设置“联机模式”按钮
	auto OnlineItem = MenuItemImage::create("button-online.png",
		                            "buttononline-click.png",
		           CC_CALLBACK_1(SelectMode::menuOnlineMode, this));

	//设置“联机模式”按钮位置
	OnlineItem->setPosition(Vec2(origin.x + SingleItem->getContentSize().width / 2 + 680,
		origin.y + OnlineItem->getContentSize().height / 2 + 120));
	

	auto menu = Menu::create(SingleItem, OnlineItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void SelectMode::menuSingleMode(Ref* pSender)
{    
	//进入选择英雄界面
	mode = "single";
	auto scene = SelectHero::createScene(mode);
	Director::getInstance()->replaceScene(scene);
}

void SelectMode::menuOnlineMode(Ref* pSender)
{
	//进入创建选择房间界面
	mode = "online";
	auto scene = Room::createScene();
	Director::getInstance()->replaceScene(scene);
	
	//下面是啥不知道，也不敢删掉
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}