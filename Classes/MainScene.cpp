#include "MainScene.h"


USING_NS_CC;


MainScene::MainScene()
{
}


Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}


bool MainScene::init()
{

    if ( !Layer::init() )
    {
        return false;
    }

    auto director = Director::getInstance();
    auto size = director->getWinSize();
    auto bg = Sprite::create("texture/bg000.png");
    bg->setPosition(Vec2(size.width * 0.5f, size.height * 0.5f));
    addChild(bg);


    return true;
}
