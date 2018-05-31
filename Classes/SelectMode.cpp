#include "SelectMode.h"
#include "Room.h"
#include "SelectHero.h"
#include "SimpleAudioEngine.h"
#include <string>

USING_NS_CC;

//��������
Scene* SelectMode::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectMode::create();

	scene->addChild(layer);
	//���س���
	return scene;
}

//���ð�ť
bool SelectMode::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//���ñ���ͼƬ
	auto bg = Sprite::create("bg2.png");
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 200);
	addChild(bg);

	/*	//���ñ�ǩ
	string str = "";
	auto myLabel = Label::createWithTTF(str, "fonts/arial.ttf", 65);
	myLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
	origin.y + visibleSize.height - myLabel->getContentSize().height));
	myLabel->setColor(Color3B(0, 0, 0));
	this->addChild(myLabel, 1);             */

	//���á�����ģʽ����ť
	auto SingleItem = MenuItemImage::create("button-single.png",
		                             "buttonsingle-click.png",
		         CC_CALLBACK_1(SelectMode::menuSingleMode, this));

	//���á�����ģʽ����ťλ��
	SingleItem->setPosition(Vec2(origin.x + SingleItem->getContentSize().width / 2+80,
		origin.y + SingleItem->getContentSize().height / 2 + 120));
	

	//���á�����ģʽ����ť
	auto OnlineItem = MenuItemImage::create("button-online.png",
		                            "buttononline-click.png",
		           CC_CALLBACK_1(SelectMode::menuOnlineMode, this));

	//���á�����ģʽ����ťλ��
	OnlineItem->setPosition(Vec2(origin.x + SingleItem->getContentSize().width / 2 + 680,
		origin.y + OnlineItem->getContentSize().height / 2 + 120));
	

	auto menu = Menu::create(SingleItem, OnlineItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void SelectMode::menuSingleMode(Ref* pSender)
{    
	//����ѡ��Ӣ�۽���
	mode = "single";
	auto scene = SelectHero::createScene(mode);
	Director::getInstance()->replaceScene(scene);
}

void SelectMode::menuOnlineMode(Ref* pSender)
{
	//���봴��ѡ�񷿼����
	mode = "online";
	auto scene = Room::createScene();
	Director::getInstance()->replaceScene(scene);
	
	//������ɶ��֪����Ҳ����ɾ��
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}