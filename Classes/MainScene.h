
#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    CREATE_FUNC(MainScene);

private:
    enum class GameState {
        PLAYING,
        RESULT,
    };


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

    bool init() override;
    void onEnterTransitionDidFinish() override;

    void update(float dt);

    


    void onResult();


    cocos2d::Sprite* addFruit();
    cocos2d::Vector<cocos2d::Sprite*>::iterator removeFruit(cocos2d::Sprite* fruit);

    cocos2d::Vector<cocos2d::Sprite*>::iterator catchFruit(cocos2d::Sprite* fruit);

    CC_SYNTHESIZE(GameState, _state, State);
    CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, _player, Player);
    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Sprite*>, _fruits, Fruit);
    CC_SYNTHESIZE(int, _score, Score);
    CC_SYNTHESIZE_RETAIN(cocos2d::Label*, _scoreLabel, ScoreLabel);
    CC_SYNTHESIZE(float, _second, Second);
    CC_SYNTHESIZE_RETAIN(cocos2d::Label*, _secondLabel, SecondLabel);

};

#endif // __HELLOWORLD_SCENE_H__
