#pragma once

#include <gd.h>
using namespace cocos2d;
using namespace gd;

static bool s_didClick = false;

class FakeLevelSelectLayerLol : public CCLayer {
protected:
    virtual bool init(int page);
    virtual void keyBackClicked();
    void onBack(CCObject*);
    void onBackward(CCObject* object);
    void onForward(CCObject* object);
    void hopTo(CCObject* object);
    void updateButtons(CCObject* object);
    void downloadSongs(CCObject* object);
    void lvlinfo(CCObject* object);
    void copylvlstr(CCObject* object);
    void copylvlstrsch(float dt);
    void schedulethingyo(float dt);
    void scheduledelayed(float dt);
    bool mEarnedAchievement;
    CCLabelTTF* copyLvlStrLabel;
    CCSprite* mBackgroundSprite;
    GJGroundLayer* mGroundLayer;
    float mUnknown1;
    BoomScrollLayer* mBoomScrollLayer;
    CCMenu* shitcodingmenu;
    CCMenu* shitdotingmenu;
    CCMenuItemSpriteExtra* rightBtn;
    CCMenuItemSpriteExtra* leftBtn;
    CCMenuItem* rightTouchZone;
    CCMenuItem* leftTouchZone;
    int LEVEL_INDEX_START;
    int LEVEL_INDEX_END;
    int mPage;
public:
    static FakeLevelSelectLayerLol* create(int page);
    CCScene* scene(int page);
    static void makeHooks();
};