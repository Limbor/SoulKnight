#include "Tool.h"
#include "cocos2d.h"
#include "GameMap.h"
USING_NS_CC;

Tool * Tool::createtool(int toolNumber)
{
	Tool* enemy = new Tool();
	if (enemy && enemy->init())
	{
		enemy->autorelease();
		enemy->enemyInit(toolNumber);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool Tool::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}
void Tool::enemyInit(int toolNumber)
{
	this->toolNumber = toolNumber;
	Sprite::initWithFile(String::createWithFormat("tool%d.png", toolNumber)->getCString());
	setPhysicsBody(PhysicsBody::createBox(Size(getContentSize().width, getContentSize().height)));
	getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	setTag(12+toolNumber);
}



