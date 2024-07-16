#include "MainScene.h"


USING_NS_CC;

namespace {
    const int FRUIT_TOP_MARGIN = 40;
    const int FRUIT_SPAWN_RATE = 20;
    const float TIME_LIMIT_SECOND = 60;
};

MainScene::MainScene()
: _player(nullptr)
, _score(0)
, _scoreLabel(nullptr)
, _second(TIME_LIMIT_SECOND)
, _secondLabel(nullptr)
{
}


MainScene::~MainScene()
{
    CC_SAFE_RELEASE_NULL(_player);
    CC_SAFE_RELEASE_NULL(_scoreLabel);
    CC_SAFE_RELEASE_NULL(_secondLabel);
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

    // スコアラベル追加
    auto scoreLabel = Label::createWithSystemFont(StringUtils::toString(_score), "Marker Felt", 16);
    scoreLabel->setPosition(Vec2(size.width * 0.5 * 1.5, size.height - 40));
    scoreLabel->enableShadow(Color4B::BLACK, Size(0.5, 0.5), 3);
    scoreLabel->enableOutline(Color4B::BLACK, 1.5);
    this->setScoreLabel(scoreLabel);
    this->addChild(scoreLabel);

    auto scoreLabelHeader = Label::createWithSystemFont("SCORE", "Marker Felt", 16);
    scoreLabelHeader->setPosition(Vec2(size.width * 0.5 * 1.5, size.height - 20));
    scoreLabelHeader->enableShadow(Color4B::BLACK, Size(0.5, 0.5), 3);
    scoreLabelHeader->enableOutline(Color4B::BLACK, 1.5);
    this->addChild(scoreLabelHeader);


    // タイマーラベル追加
    int second = static_cast<int>(_second);
    auto secondLabel = Label::createWithSystemFont(StringUtils::toString(second), "Marker Felt", 16);
    secondLabel->setPosition(Vec2(size.width * 0.5, size.height - 40));
    secondLabel->enableShadow(Color4B::BLACK, Size(0.5, 0.5), 3);
    secondLabel->enableOutline(Color4B::BLACK, 1.5);
    this->setSecondLabel(secondLabel);
    this->addChild(secondLabel);

    auto secondLabelHeader = Label::createWithSystemFont("TIME", "Marker Felt", 16);
    secondLabelHeader->setPosition(Vec2(size.width * 0.5, size.height - 20));
    secondLabelHeader->enableShadow(Color4B::BLACK, Size(0.5, 0.5), 3);
    secondLabelHeader->enableOutline(Color4B::BLACK, 1.5);
    this->addChild(secondLabelHeader);


    // update()を毎フレーム呼ぶようにする
    scheduleUpdate();

    return true;
}

void MainScene::update(float dt)
{
    // フルーツ生成
    int random = rand() % FRUIT_SPAWN_RATE;
    if (random == 0) {
        addFruit();
    }

    // フルーツキャッチ
    cocos2d::Vector<cocos2d::Sprite*>::iterator it = _fruits.begin();
    while (it != _fruits.end()) {
        auto fruit = (*it);
        Vec2 busketPos = _player->getPosition() - Vec2(0, 10);
        Rect boundingBox = fruit->getBoundingBox();
        bool isHit = boundingBox.containsPoint(busketPos);
        if (isHit) {
            it = this->catchFruit(fruit);
        } else {
            it++;
        }
    }

    // 残り秒数を減らす
    _second -= dt;
    int second = static_cast<int>(_second);
    _secondLabel->setString(StringUtils::toString(second));
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

cocos2d::Vector<cocos2d::Sprite*>::iterator MainScene::removeFruit(cocos2d::Sprite* fruit)
{
    auto it = _fruits.find(fruit);
    CCASSERT(it!= _fruits.end(), "Not found object.");
    fruit->removeFromParent();
    return _fruits.erase(it);
}

cocos2d::Vector<cocos2d::Sprite*>::iterator MainScene::catchFruit(cocos2d::Sprite* fruit)
{
    // スコア設定
    _score += 1;
    _scoreLabel->setString(StringUtils::toString(_score));

    auto it = this->removeFruit(fruit);
    return it;
}