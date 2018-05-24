#include "StartScene.h"
#include  "GameScene.h"
#include "SimpleAudioEngine.h"

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
    if ( !Scene::init() )
    {
        return false;
    }

	//���ñ���
	auto bg = Sprite::create("homeBg.png");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(bg);

	//���á�������Ϸ����ť
	auto StartItem = MenuItemImage::create("button-start1.png",
		                                   "buttonstart-clicked.png",
		           CC_CALLBACK_1(StartScene::menuStartCallback, this));

	//���á�������Ϸ����ťλ��
	StartItem->setPosition(Vec2(origin.x + StartItem->getContentSize().width / 2 + 80,
		origin.y + StartItem->getContentSize().height / 2 + 120));
	
	
	//���á��˳���Ϸ����ť
	auto ExitItem = MenuItemImage::create("button-exit1.png",
		                                  "buttonexit-clicked.png",
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
	auto scene = GameScene::createScene();
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
