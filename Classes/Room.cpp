#include  "Room.h"
#include  "SelectMode.h"
#include  "SelectHero.h"
#include  "SimpleAudioEngine.h"
#include  <string>

USING_NS_CC;

//��������
Scene* Room::createScene()
{   
	auto scene = Scene::create();
	auto layer = Room::create();

	scene->addChild(layer);
	//���س���
	return scene;
}

//���ð�ť
bool Room::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//���ñ���ͼƬ
	auto bg = Sprite::create("bg.png");
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 200);
	addChild(bg);

	/*	//���ñ�ǩ
	string str = "";
	auto myLabel = Label::createWithTTF(str, "fonts/arial.ttf", 65);
	myLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
	origin.y + visibleSize.height - myLabel->getContentSize().height));
	myLabel->setColor(Color3B(0, 0, 0));
	this->addChild(myLabel, 1);             */

	//���á��������䡱��ť
	auto FormItem = MenuItemImage::create("button-form.png",
		                               "buttonform-click.png",
		                   CC_CALLBACK_1(Room::menuFormRoom, this));

	//���á��������䡱��ťλ��
	FormItem->setPosition(Vec2(origin.x + FormItem->getContentSize().width / 2 + 80,
		                      origin.y + FormItem->getContentSize().height / 2 + 120));


	//���á����뷿�䡱��ť
	auto IntoItem = MenuItemImage::create("button-into.png",
		                          "buttoninto-click.png",
		           CC_CALLBACK_1(Room::menuIntoRoom, this));

	//���á����뷿�䡱��ťλ��
	IntoItem->setPosition(Vec2(origin.x - IntoItem->getContentSize().width / 2 - 80 + visibleSize.width,
		origin.y + IntoItem->getContentSize().height / 2 + 120));


	auto menu = Menu::create(FormItem, IntoItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

void Room::menuFormRoom(Ref* pSender)
{
	//����ѡ��Ӣ�۳���
	room = "form";
	auto scene = SelectHero::createScene(room);
	Director::getInstance()->replaceScene(scene);
}

void Room::menuIntoRoom(Ref* pSender)
{
	//����ѡ��Ӣ�۳���
	room = "into";
	auto scene = SelectHero::createScene(room);
	Director::getInstance()->replaceScene(scene);

	//������ɶ��֪����Ҳ����ɾ��
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}
