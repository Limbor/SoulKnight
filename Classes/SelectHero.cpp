#include  "SelectHero.h"
#include  "SelectMode.h"
#include   "Room.h"
#include  "SimpleAudioEngine.h"
#include  <string>

USING_NS_CC;

//创建场景
Scene* SelectHero::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectHero::create();

	scene->addChild(layer);
	//返回场景
	return scene;
}

//设置按钮
bool SelectHero::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//设置背景图片
	auto bg = Sprite::create();
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 200);
	addChild(bg);             

	//设置“选择一号英雄”按钮
	auto HeroOneItem = MenuItemImage::create("button-heroone.png",
		                                "buttonheroone-click.png",
		            CC_CALLBACK_1(SelectHero::menuHeroOne, this));

	//设置“选择一号英雄”按钮位置
	HeroOneItem->setPosition(Vec2(origin.x - HeroOneItem->getContentSize().width / 2 - 80 + visibleSize.width,
		                        origin.y + HeroOneItem->getContentSize().height / 2 + 820));


	//设置“选择二号英雄”按钮
	auto HeroTwoItem = MenuItemImage::create("button-herotwo.png",
		                                "buttonherotwo-click.png",
	             	CC_CALLBACK_1(SelectHero::menuHeroTwo, this));

	//设置“选择二号英雄”按钮位置
	HeroTwoItem->setPosition(Vec2(origin.x - HeroTwoItem->getContentSize().width / 2 - 80 +visibleSize.width,
		origin.y + HeroTwoItem->getContentSize().height / 2 + 120));


	auto menu = Menu::create(HeroOneItem, HeroTwoItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}


void SelectHero::menuHeroOne(Ref* pSender)
{

	//进入游戏界面
	hero = "one";
	Director::getInstance()->end();
}


void SelectHero::menuHeroTwo(Ref* pSender)
{
	//进入游戏界面
    hero = "two";
	Director::getInstance()->end();

	//下面是啥不知道，也不敢删掉
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}
