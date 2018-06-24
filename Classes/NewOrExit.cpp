#include  "NewOrExit.h"
#include  "GameScene.h"
#include  "SelectHero.h"
#include  "SimpleAudioEngine.h"
#include  <string>

USING_NS_CC;

temp TEMP;

//��������
Scene* NewOrExit::createScene(int win)
{
	TEMP.WIN = win;
	auto scene = Scene::create();
	auto layer = NewOrExit::create();

	scene->addChild(layer);
	//���س���
	return scene;
}

//���ð�ť
bool NewOrExit::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//���ñ���ͼƬ
	auto bg = Sprite::create("overbg.png");
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2 );
	addChild(bg);

	if (TEMP.WIN == 1) {
		auto *chnStrings = Dictionary::createWithContentsOfFile("message.xml");
		const char *str = ((String*)chnStrings->objectForKey("winstring"))->getCString();
		auto *label = Label::create(str, "Arial", 60);
		label->setPosition(500, 650);
		addChild(label);
	}else if (TEMP.WIN == 0) {
		auto *chnStrings = Dictionary::createWithContentsOfFile("message.xml");
		const char *str = ((String*)chnStrings->objectForKey("losestring"))->getCString();
		auto *label = Label::create(str, "Arial", 60);
		label->setPosition(500, 650);
		addChild(label);
	}  

	//���á�������Ϸ����ť
	auto newgame = MenuItemImage::create("newgame.png",
		                               "newgame-click.png",
		                   CC_CALLBACK_1(NewOrExit::newgame, this));

	//���á�������Ϸ����ťλ��
	newgame->setPosition(Vec2(origin.x + newgame->getContentSize().width / 2 + 80,
		                      origin.y + newgame->getContentSize().height / 2 + 120));


	//���á��˳���Ϸ����ť
	auto exitgame = MenuItemImage::create("button-exit.png",
		                          "buttonexit-click.png",
		           CC_CALLBACK_1(NewOrExit::exitgame, this));

	//���á��˳���Ϸ����ťλ��
	exitgame->setPosition(Vec2(origin.x - exitgame->getContentSize().width / 2 - 80 + visibleSize.width/2,
		origin.y + exitgame->getContentSize().height / 2 + 120));

	auto menu = Menu::create(newgame, exitgame, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void NewOrExit::newgame(Ref* pSender)
{
	auto scene = SelectHero::createScene();
	Director::getInstance()->replaceScene(scene);
}

void NewOrExit::exitgame(Ref* pSender)
{
	Director::getInstance()->end();

	//������ɶ��֪����Ҳ����ɾ��
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}
