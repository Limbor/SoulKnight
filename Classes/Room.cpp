#include  "Room.h"
#include  "SelectMode.h"
#include  "SelectHero.h"
#include  "SimpleAudioEngine.h"
#include  <string>

USING_NS_CC;

//创建场景
Scene* Room::createScene()
{   
	auto scene = Scene::create();
	auto layer = Room::create();

	scene->addChild(layer);
	//返回场景
	return scene;
}

//设置按钮
bool Room::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//设置背景图片
	auto bg = Sprite::create("bg.png");
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 200);
	addChild(bg);

	/*	//设置标签
	string str = "";
	auto myLabel = Label::createWithTTF(str, "fonts/arial.ttf", 65);
	myLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
	origin.y + visibleSize.height - myLabel->getContentSize().height));
	myLabel->setColor(Color3B(0, 0, 0));
	this->addChild(myLabel, 1);             */

	//设置“创建房间”按钮
	auto FormItem = MenuItemImage::create("button-form.png",
		                               "buttonform-click.png",
		                   CC_CALLBACK_1(Room::menuFormRoom, this));

	//设置“创建房间”按钮位置
	FormItem->setPosition(Vec2(origin.x + FormItem->getContentSize().width / 2 + 80,
		                      origin.y + FormItem->getContentSize().height / 2 + 120));


	//设置“进入房间”按钮
	auto IntoItem = MenuItemImage::create("button-into.png",
		                          "buttoninto-click.png",
		           CC_CALLBACK_1(Room::menuIntoRoom, this));

	//设置“进入房间”按钮位置
	IntoItem->setPosition(Vec2(origin.x - IntoItem->getContentSize().width / 2 - 80 + visibleSize.width,
		origin.y + IntoItem->getContentSize().height / 2 + 120));


	auto menu = Menu::create(FormItem, IntoItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void Room::menuFormRoom(Ref* pSender)
{
	//跳入选择英雄场景
	room = "form";
	auto scene = SelectHero::createScene(room);
	Director::getInstance()->replaceScene(scene);
}

void Room::menuIntoRoom(Ref* pSender)
{
	//跳入选择英雄场景
	room = "into";
	auto scene = SelectHero::createScene(room);
	Director::getInstance()->replaceScene(scene);

	//下面是啥不知道，也不敢删掉
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}
