#pragma once
#include "ModUtils.hpp"

class CustomTriggerPopup : public gd::FLAlertLayer {
public:
    gd::CCTextInputNode* mainInput;
    gd::FLAlertLayer* helper;
    cocos2d::CCLabelBMFont* saveString;
    gd::EffectGameObject* m_effectObject;
    gd::CCTextInputNode* input;
    CustomTriggerPopup();
    static CustomTriggerPopup* create(gd::EffectGameObject* obj);
    void onTouch(cocos2d::CCObject* sneder);
    void onSpawn(cocos2d::CCObject* sneder);
    void update();
    void onClose(cocos2d::CCObject* callback);
    virtual void keyBackClicked();

    bool init(gd::EffectGameObject* obj);
};

class SetupPortalPopup : public gd::FLAlertLayer {
public:
    gd::CCTextInputNode* mainInput;
    gd::FLAlertLayer* helper;
    cocos2d::CCLabelBMFont* saveString;
    gd::GameObject* m_effectObject;
    gd::CCTextInputNode* input;
    SetupPortalPopup();
    static SetupPortalPopup* create(gd::GameObject* obj);
    void onTouch(cocos2d::CCObject* sneder);
    void onfrfly(cocos2d::CCObject* sneder);
    void update();
    void onClose(cocos2d::CCObject* callback);
    virtual void keyBackClicked();

    bool init(gd::GameObject* obj);
};