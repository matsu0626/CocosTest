
#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    CREATE_FUNC(MainScene);

private:
    MainScene();
    virtual ~MainScene();

    virtual bool init() override;

    CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, _player, Player);

};

#endif // __HELLOWORLD_SCENE_H__
