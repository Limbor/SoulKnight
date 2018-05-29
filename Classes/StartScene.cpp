#include "StartScene.h"
#include  "SelectMode.h"
#include  "SimpleAudioEngine.h"
#include  <string>

USING_NS_CC;

//��������
Scene* StartScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();

	scene->addChild(layer);
	//���س���
	return scene;
}

//���ð�ť
bool StartScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//���ñ���ͼƬ
	auto bg = Sprite::create("bg.png");
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2+200);
	addChild(bg);

/*	//���ñ�ǩ
	String str = "";
	auto myLabel = Label::createWithTTF(str, "fonts/arial.ttf", 65);
 	              myLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
	                                  	origin.y + visibleSize.height-myLabel->getContentSize().height) );
				  myLabel->setColor(Color3B(0, 0, 0));
	              this->addChild(myLabel, 1);           */

	//���á�������Ϸ����ť
	auto StartItem = MenuItemImage::create("button-enter.png",
		                                   "buttonenter-click.png",
		           CC_CALLBACK_1(StartScene::menuStartCallback, this));

	//���á�������Ϸ����ťλ��
	StartItem->setPosition(Vec2(origin.x + StartItem->getContentSize().width / 2 + 80,
		origin.y + StartItem->getContentSize().height / 2 + 120));
	
	
	//���á��˳���Ϸ����ť
	auto ExitItem = MenuItemImage::create("button-exit.png",
		                                  "buttonexit-click.png",
		           CC_CALLBACK_1(StartScene::menuExitCallback, this));

	//���á��˳���Ϸ����ťλ��
	ExitItem->setPosition(Vec2(origin.x - ExitItem->getContentSize().width / 2 - 80 + visibleSize.width,
		origin.y + ExitItem->getContentSize().height / 2 + 120));
	

	auto menu = Menu::create(StartItem, ExitItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

    return true;
}

void StartScene::menuStartCallback(Ref* pSender)
{
	//Director::getInstance()->end();
	//������һ������
	auto scene = SelectMode::createScene();
	Director::getInstance()->replaceScene(scene);
}

void StartScene::menuExitCallback(Ref* pSender)
{
    Director::getInstance()->end();

	//������ɶ��֪����Ҳ����ɾ��
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
     
}
