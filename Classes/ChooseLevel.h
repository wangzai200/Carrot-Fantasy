#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string.h>

class ChooseLevel :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(ChooseLevel);

private:
	void InitUI();

	void InitEvent();
	void LoadTiledMap();

private:
	cocos2d::ui::Button* _toolbarHome;
	cocos2d::ui::Button* _toolbarShop;
	cocos2d::ui::Button* _toolbarLeaderboard;
	cocos2d::ui::ScrollView* _scrollView;
	cocos2d::ui::Button* _discountTagStone;
	cocos2d::Label* _discountText;
	std::vector<cocos2d::ui::Button*> _routeButtonArray;
	cocos2d::ui::Button* _toolbarRightbg;

	static float discountText;
};
