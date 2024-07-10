#include "MainScene.h"


USING_NS_CC;


MainScene::MainScene()
: _player(nullptr)
{
}


MainScene::~MainScene()
{
    CC_SAFE_RELEASE_NULL(_player);
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

    // BG
    auto director = Director::getInstance();
    auto size = director->getWinSize();
    auto bg = Sprite::create("texture/bg000.png");
    bg->setPosition(Vec2(size.width * 0.5f, size.height * 0.5f));
    bg->setContentSize(size);
    addChild(bg);


    // プレイヤー
    setPlayer(Sprite::create("texture/player000.png"));
    _player->setPosition(Vec2(size.width * 0.5f, size.height - 550));
    addChild(_player);

    // タッチ判定＆移動
    auto listner = EventListenerTouchOneByOne::create();
    listner->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
    };
    listner->onTouchMoved = [this](Touch* touch, Event* event) {
        Vec2 delta = touch->getDelta();
        Vec2 pos = _player->getPosition();
        pos.x += delta.x;
        auto winSize = Director::getInstance()->getWinSize();
        pos = pos.getClampPoint(Vec2(0, pos.y), Vec2(winSize.width, pos.y));
        _player->setPosition(pos);

    };
    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listner, this);


    return true;
}
