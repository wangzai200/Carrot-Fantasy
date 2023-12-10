#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
// ¸üÐÂ
class MainScene :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainScene);
private:
	void InitSprite(cocos2d::Sprite*& outSprite, cocos2d::Node* parentNode, const std::string& fileName, float x, float y, int localZOrder);

	bool InitUI();

	bool InitUIAnimation();

private:
	static float actionDuration;
	cocos2d::Sprite* _monster1;
	cocos2d::Sprite* _monster2;
	cocos2d::Sprite* _monster3;
	cocos2d::Sprite* _monster4;
	cocos2d::Sprite* _monster5;
	cocos2d::Sprite* _monster6;
	cocos2d::Sprite* _monster6Hand;
	cocos2d::Sprite* _carrot;
};
