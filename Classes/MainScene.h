
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
    virtual ~MainScene() = default;

    virtual bool init() override;

};

#endif // __HELLOWORLD_SCENE_H__
