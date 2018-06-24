#include "ShowMessage.h"
#include "SelectHero.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include <string>

USING_NS_CC;

//创建场景
Scene* ShowMessage::createScene()
{
	auto scene = Scene::create();
	auto layer = ShowMessage::create();
	scene->addChild(layer);
	//返回场景
	return scene;
}

//设置按钮
bool ShowMessage::init()
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

	//auto ccLayer = LayerColor::create(ccc4(8, 48, 84, 255));
	auto ccLayer = LayerColor::create(ccc4(0, 0, 0, 255));
	setVisible(true);
	addChild(ccLayer);

	auto grassmap = Sprite::create("gressmap.png");
	grassmap->setPosition(grassmap->getContentSize().width / 2+60, visibleSize.height - grassmap->getContentSize().height / 2-10);
	addChild(grassmap);
	auto grassmapb = Sprite::create("gressmapb.png");
	grassmapb->setPosition(grassmapb->getContentSize().width / 2 + 60, visibleSize.height - grassmapb->getContentSize().height / 2 - 300);
	addChild(grassmapb);
	auto grassboss = Sprite::create("bossr1 1.png");
	grassboss->setPosition(grassmap->getContentSize().width / 2 + 50, visibleSize.height - grassmap->getContentSize().height / 2 - 500);
	addChild(grassboss);
	auto *chnStrings1 = Dictionary::createWithContentsOfFile("message.xml");
	const char *str1 = ((String*)chnStrings1->objectForKey("string1"))->getCString();
	auto *label1 = Label::create(str1, "Arial", 28);
	label1->setPosition(320, 300);
	addChild(label1);  

	auto snowmap = Sprite::create("snowmap.png");
	snowmap->setPosition(snowmap->getContentSize().width / 2 + 755, visibleSize.height - snowmap->getContentSize().height / 2 - 10);
	addChild(snowmap);
	auto snowmapb = Sprite::create("snowmapb.png");
	snowmapb->setPosition(snowmapb->getContentSize().width / 2 + 755, visibleSize.height - snowmapb->getContentSize().height / 2 - 300);
	addChild(snowmapb);
	auto snowboss = Sprite::create("bossr1 2.png");
	snowboss->setPosition(snowmap->getContentSize().width / 2 + 745, visibleSize.height - snowmap->getContentSize().height / 2 - 500);
	addChild(snowboss);
	auto *chnStrings2 = Dictionary::createWithContentsOfFile("message.xml");
	const char *str2 = ((String*)chnStrings2->objectForKey("string2"))->getCString();
	auto *label2 = Label::create(str2, "Arial", 28);
	label2->setPosition(1005, 300);
	addChild(label2);  

	auto castlemap = Sprite::create("castlemap.png");
	castlemap->setPosition(castlemap->getContentSize().width / 2 + 1450, visibleSize.height - castlemap->getContentSize().height / 2 - 10);
	addChild(castlemap);
	auto castlemapb = Sprite::create("castlemapb.png");
	castlemapb->setPosition(castlemapb->getContentSize().width / 2 + 1450, visibleSize.height - castlemapb->getContentSize().height / 2 - 300);
	addChild(castlemapb);
	auto castleboss = Sprite::create("bossr1 3.png");
	castleboss->setPosition(castlemap->getContentSize().width / 2 + 1440, visibleSize.height - castlemap->getContentSize().height / 2 - 500);
	addChild(castleboss);
	auto *chnStrings3 = Dictionary::createWithContentsOfFile("message.xml");
	const char *str3 = ((String*)chnStrings3->objectForKey("string3"))->getCString();
	auto *label3 = Label::create(str3, "Arial", 28);
	label3->setPosition(1700, 300);
	addChild(label3);

	auto *chnStrings4 = Dictionary::createWithContentsOfFile("message.xml");
	const char *str4 = ((String*)chnStrings4->objectForKey("string4"))->getCString();
	auto *label4 = Label::create(str4, "Arial", 28);
	label4->setPosition(visibleSize.width/2-200, 100);
	addChild(label4);

	//设置“选择英雄”按钮
	auto SingleItem = MenuItemImage::create("tohero.png",
		                             "tohero-click.png",
		         CC_CALLBACK_1(ShowMessage::tohero, this));

	//设置“选择英雄”按钮位置
	SingleItem->setPosition(Vec2(origin.x - SingleItem->getContentSize().width / 2-20+ visibleSize.width,
		origin.y + SingleItem->getContentSize().height / 2 + 30));

	auto menu = Menu::create(SingleItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void ShowMessage::tohero(Ref* pSender)
{   
	auto scene = SelectHero::createScene();
	Director::getInstance()->replaceScene(scene);
	
	//下面是啥不知道，也不敢删掉
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
