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
void GameMap::addBarrier(GameScene* scene) {
	Sprite* wall[34];
	for (int i = 0;i < 34;i++) {
		wall[i] = Sprite::create("27.wall1.png");
		wall[i]->setPosition(33 + 60 * i, 35 + 30);
		scene->addChild(wall[i]);
	}
	int treemap[14][32] = {
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
	};
	Sprite* tree[14][32];
	for (int i = 0;i < 14;i++) {
		for (int j = 0;j < 32;j++) {
			switch (treemap[13 - i][j]) {
			case 0:break;
			case 1:tree[13 - i][j] = Sprite::create("29.tree1.png");
				tree[13 - i][j]->setPosition(93 + 60 * j, 200 + 60 * i);
				
				scene->addChild(tree[13 - i][j]);break;
			}
		}
	}
	int boxmap[14][32] = {
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,4,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,5,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,1,3,1,1,3,3,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,5,0,0 },
	{ 0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,4,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
	};
	Sprite* box[14][32];
	for (int i = 0;i < 14;i++) {
		for (int j = 0;j < 32;j++) {
			switch (boxmap[13 - i][j]) {
				case 0:break;
				case 1:box[13 - i][j] = Sprite::create("28.bigstone1.png");
					box[13 - i][j]->setPosition(93 + 60 * j, 185 + 60 * i);
					scene->addChild(box[13 - i][j]);break;
				case 2:box[13 - i][j] = Sprite::create("30.fire1.png");
					box[13 - i][j]->setPosition(93 + 60 * j, 185 + 60 * i);
					scene->addChild(box[13 - i][j]);break;
				case 3:box[13 - i][j] = Sprite::create("31.bigstone2.png");
					box[13 - i][j]->setPosition(93 + 60 * j, 185 + 60 * i);
					scene->addChild(box[13 - i][j]);break;
				case 4:box[13 - i][j] = Sprite::create("32.box1.png");
					box[13 - i][j]->setPosition(93 + 60 * j, 185 + 60 * i);
					scene->addChild(box[13 - i][j]);break;
				case 5:box[13 - i][j] = Sprite::create("33.box2.png");
					box[13 - i][j]->setPosition(93 + 60 * j, 185 + 60 * i);
					scene->addChild(box[13 - i][j]);break;
			}
		}
	}
}
bool GameMap::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	int card[18][34] = { { 2,2,4,2,4,4,2,4,4,4,4,4,4,4,4,4,4,2,4,4,2,2,2,4,4,4,2,4,2,4,4,4,4,2 },
	{ 4,16,15,16,15,17,15,15,17,17,15,17,17,15,17,17,15,16,15,15,16,16,16,15,17,17,16,17,16,15,15,15,15,4 },
	{ 4,13,13,12,13,12,11,11,12,12,11,12,12,11,12,12,11,13,5,11,13,13,13,11,12,12,11,12,13,11,13,11,13,4 },
	{ 4,12,12,11,12,11,11,13,13,11,11,11,11,13,11,11,11,5,5,13,5,5,12,13,11,11,11,13,12,13,12,11,12,4 },
	{ 4,11,11,10,11,11,11,12,12,11,11,13,11,5,13,13,11,5,5,12,5,12,13,12,11,13,11,12,13,5,11,11,11,4 },
	{ 4,11,11,8,11,11,11,11,11,11,11,12,11,5,5,12,13,5,5,13,5,13,12,11,13,12,13,11,5,5,11,11,13,4 },
	{ 4,11,13,8,11,11,13,13,13,11,11,13,11,5,5,11,5,5,5,5,12,5,5,11,12,13,5,11,12,5,11,11,5,4 },
	{ 4,13,12,8,13,11,8,8,12,13,11,5,11,12,5,11,5,12,5,12,13,12,5,11,11,12,5,11,13,5,13,11,5,2 },
	{ 4,12,11,8,12,11,8,8,11,12,13,5,11,13,5,11,5,11,5,13,5,13,5,11,13,13,5,11,5,12,5,11,5,4 },
	{ 4,11,11,12,13,11,8,8,11,11,12,5,11,5,5,13,5,11,5,5,12,5,5,11,12,12,6,11,5,11,5,11,5,4 },
	{ 4,10,11,11,12,11,8,5,11,11,11,5,11,12,5,12,5,11,12,5,13,12,5,11,11,11,5,11,5,11,12,13,5,2 },
	{ 4,9,11,11,11,11,8,5,11,11,11,5,11,13,5,11,12,11,11,5,5,13,5,13,11,11,5,11,12,11,11,5,5,4 },
	{ 4,8,11,11,11,11,6,5,11,11,11,5,11,5,12,11,11,11,11,5,12,5,5,12,11,11,12,11,13,11,11,5,5,2 },
	{ 4,7,13,13,11,11,5,12,13,13,13,12,11,5,11,11,11,11,11,5,13,5,12,11,11,11,13,11,12,11,11,5,12,4 },
	{ 4,6,6,5,13,12,12,13,12,12,12,13,11,12,13,12,11,5,11,13,11,13,11,11,5,5,5,11,11,13,11,5,11,4 },
	{ 4,5,5,12,12,13,13,12,13,13,13,12,13,13,12,13,13,12,13,5,13,5,13,13,5,5,5,13,13,5,13,5,13,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } };
	Sprite* map[18][34];
	for (int i = 0;i < 18;i++) {
		for (int j = 0;j < 34;j++) {
			switch (card[17-i][j]) {
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


