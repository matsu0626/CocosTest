
#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    CREATE_FUNC(MainScene);

private:
    enum class FruitType {
        APPLE,
        GRAPE,
        ORANGE,
        BANANA,
        CHERRY,
        // ----
        MAX
    };

    MainScene();
    virtual ~MainScene();

    virtual bool init() override;
    void update(float dt);


    cocos2d::Sprite* addFruit();
    cocos2d::Vector<cocos2d::Sprite*>::iterator removeFruit(cocos2d::Sprite* fruit);

    cocos2d::Vector<cocos2d::Sprite*>::iterator catchFruit(cocos2d::Sprite* fruit);


    CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, _player, Player);
    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Sprite*>, _fruits, Fruit);

};

#endif // __HELLOWORLD_SCENE_H__
