#include "MainScene.h"


USING_NS_CC;

namespace {
    const int FRUIT_TOP_MARGIN = 40;
    const int FRUIT_SPAWN_RATE = 20;
};

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

    // update()を毎フレーム呼ぶようにする
    scheduleUpdate();

    return true;
}

void MainScene::update(float dt)
{
    int random = rand() % FRUIT_SPAWN_RATE;
    if (random == 0) {
        addFruit();
    }
}

Sprite* MainScene::addFruit()
{
    auto winSize = Director::getInstance()->getWinSize();
    int type = rand() % static_cast<int>(FruitType::MAX);

    std::string fname = StringUtils::format("texture/fruit%d.png", type);

    auto fruit = Sprite::create(fname);
    fruit->setTag(type);

    auto fruitSize = fruit->getContentSize();
    float posX = rand() % static_cast<int>(winSize.width);

    fruit->setPosition(Vec2(posX, winSize.height - FRUIT_TOP_MARGIN - fruitSize.height * 0.5f));
    addChild(fruit);
    _fruits.pushBack(fruit);

    // アクション：地面に落下して消滅
    auto ground = Vec2(posX, 0);
    auto fall = MoveTo::create(3, ground);
    auto remove = CallFuncN::create([this](Node* node) {
        auto sprite = dynamic_cast<Sprite*>(node);
        this->removeFruit(sprite);
    });
    auto seq = Sequence::create(fall, remove, NULL);
    fruit->runAction(seq);

    return fruit;
}

void MainScene::removeFruit(cocos2d::Sprite* fruit)
{
    if (_fruits.contains(fruit)) {
        fruit->removeFromParent();
        _fruits.eraseObject(fruit);
    }
}