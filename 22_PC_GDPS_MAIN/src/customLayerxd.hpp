#pragma once

#include <gd.h>

class customLayerxd : public cocos2d::CCLayer {
protected:
    virtual bool init();
    virtual void keyBackClicked();
    void onBack(cocos2d::CCObject*);
public:
    static customLayerxd* create();

    // button callback function. if we were robtop this would be in MenuLayer, however we are not
    void switchcustomLayerxdbtn(CCObject*);
    //links
    void openURLcredits(cocos2d::CCObject*);
    void gamejolt_openURL(cocos2d::CCObject*);
    void openURL(cocos2d::CCObject*);
    void discord_openURL(cocos2d::CCObject*);
    void vk_openURL(cocos2d::CCObject*);
    void yt_openURL(cocos2d::CCObject*);
};