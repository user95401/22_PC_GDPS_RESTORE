#include "ModUtils.hpp"
#include "HooksUtils.hpp"
using namespace cocos2d;
using namespace extension;
class KeysLayer : public gd::KeysLayer {
public:
    void customSetup(float) {
        //TreasureRoomSheet
        CCTextureCache::sharedTextureCache()->addImage("TreasureRoomSheet.png", 0);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("TreasureRoomSheet.plist");
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        //treasureRoomGround_001
        auto treasureRoomGround_001 = ModUtils::createSprite("treasureRoomGround_001.png");
        treasureRoomGround_001->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
        auto size = treasureRoomGround_001->getContentSize();
        treasureRoomGround_001->setScaleX(winSize.width / size.width);
        treasureRoomGround_001->setScaleY(2.5);
        treasureRoomGround_001->setPosition({ winSize.width / 2, 0 });
        treasureRoomGround_001->setZOrder(-1);
        treasureRoomGround_001->setOpacity({ 150 });
        this->addChild(treasureRoomGround_001);
        //cornerUL
        auto cornerUL = ModUtils::createSprite("treasureRoomSpiderweb_001.png");
        cornerUL->setColor({ 0,0,0 }); cornerUL->setOpacity(100);
        cornerUL->setPosition({ 0, winSize.height });
        cornerUL->setScale(1.2);
        cornerUL->setAnchorPoint({ 0.05,0.05 });
        cornerUL->setFlipX(1); cornerUL->setFlipY(1);
        cornerUL->setRotation(90);
        this->addChild(cornerUL, -1);
        //cornerUR
        auto cornerUR = ModUtils::createSprite("treasureRoomSpiderweb_001.png");
        cornerUR->setColor({ 0,0,0 }); cornerUR->setOpacity(100);
        cornerUR->setPosition({ winSize.width,winSize.height });
        cornerUR->setScale(1.2);
        cornerUR->setAnchorPoint({ 0.05,0.05 });
        cornerUR->setFlipX(1); cornerUR->setFlipY(1);
        cornerUR->setRotation(180);
        this->addChild(cornerUR, -1);
    }
};
bool (__thiscall* CCLayer_init)(CCLayer* pClass);
bool __fastcall CCLayer_init_H(CCLayer* pClass) {
        auto rtn = CCLayer_init(pClass);
        //pKeysLayer
        if (auto pKeysLayer = dynamic_cast<KeysLayer*>(pClass); pKeysLayer)
            pKeysLayer->scheduleOnce(schedule_selector(KeysLayer::customSetup), 0.001f);
        return rtn;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;
    MH_Initialize();
    CC_HOOK("?init@CCLayer@cocos2d@@UAE_NXZ", CCLayer_init);
    return TRUE;
}