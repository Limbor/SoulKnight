#include "GameMap.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Layer* GameMap::createLayer()
{
    return GameMap::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameMap::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	int card[18][34]={ 
	{2,2,4,2,4,4,2,4,4,4,4,4,4,4,4,4,4,2,4,4,2,2,2,4,4,4,2,4,2,4,4,4,4,2},
	{4,22,15,16,15,17,15,15,17,17,15,17,17,15,17,17,15,16,15,15,16,16,16,15,17,17,16,17,16,15,15,15,15,16},
	{4,21,22,12,13,12,11,11,12,12,11,12,11,11,12,12,11,13,20,11,13,13,13,11,12,12,11,12,13,11,13,11,13,4},
	{4,12,21,22,12,11,11,13,13,11,11,22,22,22,22,22,22,22,19,13,5,5,12,13,11,11,11,13,12,13,26,11,12,4},
	{4,11,11,21,22,11,11,12,12,11,22,21,21,21,21,21,21,21,18,12,5,12,26,12,11,13,11,12,13,5,24,11,11,4},
	{4,11,11,8,21,22,11,20,11,22,21,12,11,5,5,12,13,5,5,13,5,13,26,24,13,12,13,11,5,5,26,11,13,4},
	{4,11,13,8,11,21,22,19,22,21,11,5,5,11,5,5,5,11,5,5,12,5,24,26,12,13,5,11,12,5,24,11,5,4},
	{4,13,12,8,13,11,21,18,21,11,5,5,11,5,11,5,5,11,5,12,13,12,26,24,11,12,5,11,13,5,26,11,5,2},
	{4,12,11,8,12,11,8,5,11,5,5,11,5,13,5,11,5,5,5,13,5,13,24,26,24,24,26,26,24,24,26,11,5,4},
	{4,11,11,12,13,11,8,20,5,5,12,5,11,5,5,13,5,11,5,5,12,5,26,24,23,23,25,25,23,23,26,11,5,4},
	{4,10,11,11,12,11,22,19,22,5,11,5,11,12,5,12,5,11,12,5,13,12,24,26,11,11,5,11,5,11,24,13,5,2},
	{4,9,11,11,11,22,21,18,21,22,5,5,11,13,5,11,12,11,5,5,5,13,26,24,11,11,5,11,12,11,26,5,5,4},
	{4,8,11,11,22,21,6,5,11,21,22,5,5,5,5,5,5,5,20,5,12,5,26,23,11,11,12,11,13,11,24,5,5,2},
	{4,7,13,22,21,11,5,12,13,13,21,22,22,22,22,22,22,22,19,5,13,5,25,11,11,11,13,11,12,11,26,5,12,4},
	{4,11,22,21,13,12,12,13,12,12,12,21,21,21,21,21,21,21,18,13,11,13,11,11,5,5,5,11,11,13,25,5,11,4},
	{4,22,21,12,12,13,13,12,13,13,13,12,13,5,5,13,13,12,5,5,13,5,13,13,5,5,5,13,13,5,13,5,13,2},
	{2,4,4,4,4,4,4,2,4,2,2,4,4,2,4,4,4,4,2,4,4,4,2,4,2,2,4,2,2,2,2,4,2,2},
	{1,3,3,3,3,3,3,1,3,1,1,3,3,1,3,3,3,3,1,3,3,3,1,3,1,1,3,1,1,1,1,3,1,1}
	};
	Sprite* map[18][34];
	for (int i = 0;i < 18;i++) {
		for (int j = 0;j < 34;j++) {
			switch (card[17-i][j])
			{
				case 1:map[17-i][j] = Sprite::create("1.wall1.png");
					map[17-i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17-i][j]);break;
				case 2:map[17 - i][j] = Sprite::create("2.wall2.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 3:map[17 - i][j] = Sprite::create("3.grass1.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 4:map[17 - i][j] = Sprite::create("4.grass2.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 5:map[17 - i][j] = Sprite::create("5.floor1.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 6:map[17 - i][j] = Sprite::create("6.floor2.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 7:map[17 - i][j] = Sprite::create("7.floor3.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 8:map[17 - i][j] = Sprite::create("8.floor4.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 9:map[17 - i][j] = Sprite::create("9.floor5.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 10:map[17 - i][j] = Sprite::create("10.floor6.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 11:map[17 - i][j] = Sprite::create("11.floor7.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 12:map[17 - i][j] = Sprite::create("12.floor8.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 13:map[17 - i][j] = Sprite::create("13.floor9.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 14:map[17 - i][j] = Sprite::create("14.wall3.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 15:map[17 - i][j] = Sprite::create("15.gress3.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 16:map[17 - i][j] = Sprite::create("16.wall4.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 17:map[17 - i][j] = Sprite::create("17.grass4.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 18:map[17 - i][j] = Sprite::create("18.fire1.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 19:map[17 - i][j] = Sprite::create("19.fire2.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 20:map[17 - i][j] = Sprite::create("20.fire3.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 21:map[17 - i][j] = Sprite::create("21.tree1.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 22:map[17 - i][j] = Sprite::create("22.tree2.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 23:map[17 - i][j] = Sprite::create("23.box1.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 24:map[17 - i][j] = Sprite::create("24.box2.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 25:map[17 - i][j] = Sprite::create("25.stone1.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
				case 26:map[17 - i][j] = Sprite::create("26.stone2.png");
					map[17 - i][j]->setPosition(33 + 60 * j, 35 + 60 * i);
					addChild(map[17 - i][j]);break;
			}
		}
	}
    return true;
}


