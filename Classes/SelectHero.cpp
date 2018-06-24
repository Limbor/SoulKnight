#include  "SelectHero.h"
#include  "ShowMessage.h"
#include  "SimpleAudioEngine.h"
<<<<<<< HEAD
#include  "GameScene.h"

=======
#include "GameScene.h"
#include  <string>
>>>>>>> origin/master

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

<<<<<<< HEAD

=======
>>>>>>> origin/master
//设置按钮
bool SelectHero::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

<<<<<<< HEAD
	auto ccLayer = LayerColor::create(ccc4(8, 48, 84, 255));
		setVisible(true);
	    addChild(ccLayer);
   
	auto onehero = Sprite::create("one.png");
	onehero->setPosition(visibleSize.width/4 , visibleSize.height - onehero->getContentSize().height / 2 - 50);
	addChild(onehero);
	auto *chnStringsone = Dictionary::createWithContentsOfFile("message.xml");
	const char *strone = ((String*)chnStringsone->objectForKey("onestring"))->getCString();
	auto *labelone = Label::create(strone, "Arial", 36);
	labelone->setPosition(visibleSize.width / 4, visibleSize.height/2);
	addChild(labelone);

	auto twohero = Sprite::create("two.png");
	twohero->setPosition((visibleSize.width / 4)*3, visibleSize.height - twohero->getContentSize().height / 2 - 50);
	addChild(twohero);
	auto *chnStringstwo = Dictionary::createWithContentsOfFile("message.xml");
	const char *strtwo = ((String*)chnStringstwo->objectForKey("twostring"))->getCString();
	auto *labeltwo = Label::create(strtwo, "Arial", 36);
	labeltwo->setPosition((visibleSize.width / 4)*3, visibleSize.height / 2);
	addChild(labeltwo);

	
	auto *chnStrings = Dictionary::createWithContentsOfFile("message.xml");
	const char *str = ((String*)chnStrings->objectForKey("string"))->getCString();
	auto *label = Label::create(str, "Arial", 28);
	label->setPosition((visibleSize.width / 4) * 2, 300);
	addChild(label);
=======
	//设置背景图片
	auto bg = Sprite::create();
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 200);
	addChild(bg);             
>>>>>>> origin/master

	//设置“选择一号英雄”按钮
	auto HeroOneItem = MenuItemImage::create("button-heroone.png",
		                                "buttonheroone-click.png",
		            CC_CALLBACK_1(SelectHero::menuHeroOne, this));

	//设置“选择一号英雄”按钮位置
<<<<<<< HEAD
	HeroOneItem->setPosition(Vec2(origin.x + HeroOneItem->getContentSize().width / 2 + 120 ,
		                        origin.y + HeroOneItem->getContentSize().height / 2 + 40));
=======
	HeroOneItem->setPosition(Vec2(origin.x - HeroOneItem->getContentSize().width / 2 - 80 + visibleSize.width,
		                        origin.y + HeroOneItem->getContentSize().height / 2 + 820));
>>>>>>> origin/master


	//设置“选择二号英雄”按钮
	auto HeroTwoItem = MenuItemImage::create("button-herotwo.png",
		                                "buttonherotwo-click.png",
	             	CC_CALLBACK_1(SelectHero::menuHeroTwo, this));

	//设置“选择二号英雄”按钮位置
<<<<<<< HEAD
	HeroTwoItem->setPosition(Vec2(origin.x - HeroTwoItem->getContentSize().width / 2 -120 +visibleSize.width,
		origin.y + HeroTwoItem->getContentSize().height / 2 + 40));
=======
	HeroTwoItem->setPosition(Vec2(origin.x - HeroTwoItem->getContentSize().width / 2 - 80 +visibleSize.width,
		origin.y + HeroTwoItem->getContentSize().height / 2 + 120));
>>>>>>> origin/master

	//设置“选择二号英雄”按钮
	auto StartGame = MenuItemImage::create("button-start.png",
		                             "buttonstart-click.png",
		            CC_CALLBACK_1(SelectHero::StartGame, this));

	//设置“选择二号英雄”按钮位置
	StartGame->setPosition(Vec2(origin.x +visibleSize.width/2,
		origin.y + StartGame->getContentSize().height / 2 + 40));


	auto menu = Menu::create(HeroOneItem, HeroTwoItem,StartGame, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void SelectHero::menuHeroOne(Ref* pSender)
{
<<<<<<< HEAD
	heronum = 1;
=======

	//进入游戏界面
	hero = "one";
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
>>>>>>> origin/master
}

void SelectHero::menuHeroTwo(Ref* pSender)
{
<<<<<<< HEAD
	heronum = 2;
}

void SelectHero::StartGame(Ref* pSender)
{
	//进入游戏界面
	 if (heronum == 1) {
		auto scene = GameScene::createScene(1, 1, 0, 6, 5, 200 , 1, 1);
		Director::getInstance()->replaceScene(scene);
	}
	else  if (heronum==2){
		auto scene = GameScene::createScene(1, 2, 0, 10, 3, 240 , 1, 1);
		Director::getInstance()->replaceScene(scene);
     }  

=======
	//进入游戏界面
    hero = "two";
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);

>>>>>>> origin/master
	//下面是啥不知道，也不敢删掉
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
