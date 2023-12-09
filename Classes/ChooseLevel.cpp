#include "ChooseLevel.h"
#include "MainScene.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;


float ChooseLevel::discountText = 7.5;

cocos2d::Scene* ChooseLevel::createScene()
{
	return ChooseLevel::create();
}

// 枚举，其中保存着各类节点的层级，这样使得各类节点的层级便于管理
enum zOrderMap
{
	route = 1,             // 道路层级
	routeButtonEffect = 5, // 按钮特效层级
	levelButton = 10       // 按钮层级
};

//// 构造函数
//ChooseLevel::ChooseLevel()
//{
//	InitUI();
//	InitEvent();
//}


bool ChooseLevel::init()
{
	if (!Scene::init())
		return false;


	InitUI();

	InitEvent();
	LoadTiledMap();

	return true;
}

void ChooseLevel::InitUI()
{
	//背景滚动界面
	auto scrollView = ScrollView::create();
	_scrollView = cocos2d::ui::ScrollView::create();
	_scrollView = cocos2d::ui::ScrollView::create();
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	scrollView->setTouchEnabled(true);
	scrollView->setContentSize(Director::getInstance()->getVisibleSize());
	scrollView->setScrollBarEnabled(false);
	this->addChild(scrollView);
	this->addChild(_scrollView);
	Sprite* imageView = nullptr;
	string filePath;
	float nextPosX = 0.f;
	for (int i = 0; i < 14; i++)
	{
		filePath = "ChooseLevel/Map/stage_map_" + to_string(i) + ".png";
		imageView = Sprite::create(filePath);
		//更改锚点位置是因为第14张地图跟前面的13张地图宽度不一致
		imageView->setAnchorPoint(Vec2(0, 0.5));
		imageView->setPosition(nextPosX, Director::getInstance()->getVisibleSize().height / 2);
		nextPosX += imageView->getContentSize().width;
		scrollView->addChild(imageView);
	}
	scrollView->setInnerContainerSize(Size(nextPosX, Director::getInstance()->getVisibleSize().height));


	//UI按钮控件
	auto layerUI = Layer::create();
	this->addChild(layerUI);
	auto leftPanelPinfo = AutoPolygon::generatePolygon("ChooseLevel/stagemap_toolbar_leftbg.png");
	//该背景图始终在屏幕的左上角
	auto leftPanel = Sprite::create(leftPanelPinfo);
	leftPanel->setAnchorPoint(Vec2(0, 1));
	leftPanel->setPosition(0, Director::getInstance()->getVisibleSize().height);
	leftPanel->setScale(0.7);
	layerUI->addChild(leftPanel);
	//创建背景图精灵的子节点（三个按钮）
	string toolbarHomeFilePath = "ChooseLevel/stagemap_toolbar_home.png";
	_toolbarHome = Button::create(toolbarHomeFilePath, toolbarHomeFilePath, "");
	_toolbarHome->setAnchorPoint(Vec2(0, 0));
	_toolbarHome->setPosition(Vec2(10, 10));
	_toolbarHome->setPressedActionEnabled(true);
	leftPanel->addChild(_toolbarHome);

	string toolbarShopFilePath = "ChooseLevel/stagemap_toolbar_shop.png";
	_toolbarShop = Button::create(toolbarShopFilePath, toolbarShopFilePath, "");
	_toolbarShop->setAnchorPoint(Vec2(0, 0));
	_toolbarShop->setPosition(Vec2(125, 10));
	_toolbarShop->setPressedActionEnabled(true);
	leftPanel->addChild(_toolbarShop);

	string toolbarLeaderboardFilePath = "ChooseLevel/stagemap_toolbar_leaderboard.png";
	_toolbarLeaderboard = Button::create(toolbarLeaderboardFilePath, toolbarLeaderboardFilePath, "");
	_toolbarLeaderboard->setAnchorPoint(Vec2(0, 0));
	_toolbarLeaderboard->setPosition(Vec2(235, 10));
	_toolbarLeaderboard->setPressedActionEnabled(true);
	leftPanel->addChild(_toolbarLeaderboard);


	//创建中间的促销按钮
	string discountTagStoneFilePath = "ChooseLevel/zh/discount_tag_stone.png";
	_discountTagStone = Button::create(discountTagStoneFilePath, discountTagStoneFilePath, "");
	_discountTagStone->setAnchorPoint(Vec2(0.5, 1));
	_discountTagStone->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height));
	_discountTagStone->setScale(0.7);

	_discountText = Label::createWithBMFont("ChooseLevel/discount.fnt", "8");
	_discountTagStone->addChild(_discountText);
	_discountText->setAnchorPoint(Vec2(0, 0));
	_discountText->setPosition(160, 65);
	layerUI->addChild(_discountTagStone);


	//创建右上角 生命星按钮
	string toolbarRightbgFilePath = "ChooseLevel/stagemap_toolbar_rightbg.png";
	_toolbarRightbg = Button::create(toolbarRightbgFilePath, toolbarRightbgFilePath, "");
	_toolbarRightbg->setAnchorPoint(Vec2(1, 1));
	_toolbarRightbg->setPosition(Director::getInstance()->getVisibleSize());
	_toolbarRightbg->setScale(0.7);
	layerUI->addChild(_toolbarRightbg);

	//创建生命星星的图片背景
	auto starImage = Sprite::create("ChooseLevel/zh/stagemap_toolbar_overten.png");
	starImage->setAnchorPoint(Vec2(1, 1));
	starImage->setPosition(Director::getInstance()->getVisibleSize());
	starImage->setScale(0.7);
	layerUI->addChild(starImage);

	auto text = Label::createWithSystemFont("010", "Arial", 24);
	text->setAnchorPoint(Vec2(0, 0));
	text->setPosition(Vec2(220, 73));
	starImage->addChild(text);
}

void ChooseLevel::InitEvent()
{

	//初始化首页按钮、商店按钮、排行榜按钮的三个事件
	_toolbarHome->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			auto mainScene = MainScene::createScene();
			Director::getInstance()->replaceScene(mainScene);
		}
		});

	_toolbarShop->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			log("open the shop");
		}
		});


	_toolbarLeaderboard->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			log("open the leaderboard");
		}
		});

	//初始化中间的促销按钮
	_discountTagStone->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			log("open the discountTagStone");
		}
		});


	//初始化右上角生命星星事件
	_toolbarRightbg->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED)
		{
			log("click the toolbarRightbg");
		}
		});

}

// LoadTiledMap 函数
void ChooseLevel::LoadTiledMap()
{
	TMXTiledMap* map = TMXTiledMap::create("ChooseLevel/Map/TiledMap.tmx");
	//获取瓦片地图中的point对象层
	auto objectGroup = map->getObjectGroup("point");
	//将对象层中的所有对象获取出来
	auto objs = objectGroup->getObjects();
	//遍历对象
	for (int i = 0; i < objs.size(); i++)
	{
		//根据瓦片地图中位置坐标信息配置关卡按钮
		auto button = Button::create();
		_scrollView->addChild(button, zOrderMap::levelButton, i);
		//std::vector<cocos2d::ui::Button*> _routeButtonArray;
		_routeButtonArray.push_back(button);
		//图片纹理
		string texture = "ChooseLevel/stagepoint_adv.png";
		auto valueMap = objs[i].asValueMap();
			//判断当前关卡类型
			if (valueMap["isBoos"].asString() == "YES")//是否为boss关卡
				texture = "ChooseLevel/stagepoint_gate.png";
			else if (valueMap["isTime"].asString() == "YES")//是否为时间关卡
				texture = "ChooseLevel/stagepoint_time.png";
			else if (valueMap["isChange"].asString() == "YES")//是否为随即关卡
				texture = "ChooseLevel/stagepoint_chance.png";

		button->loadTextures(texture, texture, "");
		//按钮的位置坐标
		button->setPosition(Vec2(valueMap["x"].asFloat(), valueMap["y"].asFloat()));//获取对象的属性:(as一类的方法 （转换类型）
		//设置按钮Tag非常重要，实际上就是当前关卡数，索引从0开始，即0表示第1关，1表示第2关，以此类推。
		button->setTag(i);
		button->setScale(0.7);
		//触摸事件监听器
		button->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				//当前关卡等级，根据Tag值加载对应关卡的数据
				log("hello %d", ((Button*)sender)->getTag());
				//TODO：加载关卡数据，进入游戏
			}
			});

	}
}

static void problemLoading(const char* filename)
{
	printf("Error while loading:%s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in ChooseLevel.cpp\n");
}
