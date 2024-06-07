#include "ModUtils.hpp"
#include "HooksUtils.hpp"
#include "gd.h"
using namespace cocos2d;
using namespace extension;
using namespace gd;

bool DailyLevelIsWeekly;
class DailyLevelPageMod {
public:
    void onSafe(cocos2d::CCObject*) {
        CCScene* browserLayerScene = CCScene::create();
        browserLayerScene->addChild(LevelBrowserLayer::create(gd::GJSearchObject::create(DailyLevelIsWeekly ? SearchType::kSearchTypeWeekly : SearchType::kSearchTypeDaily)));
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5, browserLayerScene));
    }
};

inline bool(__thiscall* DailyLevelPage_init)(DailyLevelPage*, bool);
bool __fastcall DailyLevelPage_init_H(DailyLevelPage* self, void*, bool isWeekly) {
    if (!DailyLevelPage_init(self, isWeekly)) return false;
    //isWeekly thing
    DailyLevelIsWeekly = isWeekly;
    //remove corner
    CCLayer* layer = (CCLayer*)self->getChildren()->objectAtIndex(0);
    layer->removeChild((CCSprite*)layer->getChildren()->objectAtIndex(4));
    //safeBtn
    CCMenu* menu = self->m_pButtonMenu;
    auto safeBtn = gd::CCMenuItemSpriteExtra::create(ModUtils::createSprite("GJ_safeBtn_001.png"), self, menu_selector(DailyLevelPageMod::onSafe));
    safeBtn->setPosition({ 380, -20 });
    menu->addChild(safeBtn);
    return true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;
    MH_Initialize();
    HOOK(base + 0x6a900, DailyLevelPage_init, true);
    return TRUE;
}