#include  "SelectHero.h"
#include  "SelectMode.h"
#include   "Room.h"
#include   "GameScene.h"
#include  "SimpleAudioEngine.h"
#include  <string>

USING_NS_CC;

//����һ��������÷Ǿ�̬���������ݱ���
htemp test;

//��������
Scene* SelectHero::createScene(string str)
{   
	test.st = str;
	auto scene = Scene::create();
	auto layer = SelectHero::create();

	scene->addChild(layer);
	//���س���
	return scene;
}

//���ð�ť
bool SelectHero::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//���ñ���ͼƬ
	auto bg = Sprite::create();
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 200);
	addChild(bg);             

	//���á�ѡ��һ��Ӣ�ۡ���ť
		auto HeroOneItem = MenuItemImage::create("button-heroone.png",
		                                	"buttonheroone-click.png",
		            	CC_CALLBACK_1(SelectHero::menuHeroOne, this));

		//���á�ѡ��һ��Ӣ�ۡ���ťλ��
		HeroOneItem->setPosition(Vec2(origin.x - HeroOneItem->getContentSize().width / 2 - 80 + visibleSize.width,
			origin.y + HeroOneItem->getContentSize().height / 2 + 500));
	
	    //���ñ�ǩ��ʾ��ͬģʽ�µ���Ϣ
		auto *chnString = Dictionary::createWithContentsOfFile("message.xml");
		const char *str;

		if (test.st == "single") {
			str = ((String*)chnString->objectForKey("string1"))->getCString();
		}
		else  if (test.st == "form") {
		   str = ((String*)chnString->objectForKey("string2"))->getCString();
		}
		else {
			str = ((String*)chnString->objectForKey("string3"))->getCString();
		}
		auto *Labell = Label::create(str, "Arial", 36);
		Labell->setPosition(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - Labell->getContentSize().height);
		Labell->setColor(Color3B(255, 255, 255));
		addChild(Labell);
		
	    

	//���á�ѡ�����Ӣ�ۡ���ť
	auto HeroTwoItem = MenuItemImage::create("button-herotwo.png",
		                                "buttonherotwo-click.png",
	             	CC_CALLBACK_1(SelectHero::menuHeroTwo, this));

	//���á�ѡ�����Ӣ�ۡ���ťλ��
	HeroTwoItem->setPosition(Vec2(origin.x - HeroTwoItem->getContentSize().width / 2 - 80 +visibleSize.width,
		origin.y + HeroTwoItem->getContentSize().height / 2 + 100));


	auto menu = Menu::create(HeroOneItem, HeroTwoItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}


void SelectHero::menuHeroOne(Ref* pSender)
{

	//������Ϸ����
	hero = "one";
	//auto scene = GameScene::createScene();
	Director::getInstance()->end();
}


void SelectHero::menuHeroTwo(Ref* pSender)
{
	//������Ϸ����
    hero = "two";
	Director::getInstance()->end();

	//������ɶ��֪����Ҳ����ɾ��
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

}
