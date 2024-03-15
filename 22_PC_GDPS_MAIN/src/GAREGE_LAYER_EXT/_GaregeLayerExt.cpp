#include "ModUtils.hpp"
#include "HooksUtils.hpp"
using namespace cocos2d;
using namespace extension;
using namespace gd;
#include "EventLevelPage.hpp"
#include "LevelAreaInnerLayer.hpp"
#include "LevelAreaLayer.hpp"
class CreatorLayerMod : public cocos2d::CCLayer {
public:
    void onMultiplayer(cocos2d::CCObject*) {
    }
    void onEventLevel(cocos2d::CCObject* pSender) {
        EventLevelPage* alert = EventLevelPage::create();
        alert->m_bNoElasticity = true;
        alert->show();
    }
    void onAdventureMap(cocos2d::CCObject*) {
        auto layer = LevelAreaLayer::create();
        auto scene = CCScene::create();
        scene->addChild(layer);
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
    }
    void onTopLists(cocos2d::CCObject*) {
        auto layer = LevelBrowserLayer::create(GJSearchObject::create(kGJSearchTypeTopListsIDK));
        auto scene = CCScene::create();
        scene->addChild(layer);
        CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, scene));
    }
    void onPaths(cocos2d::CCObject*) {
    }
};
void addclbtn(const char* name, cocos2d::SEL_MenuHandler sus, const CCPoint& pos, CCMenu* menu) {
    CCSprite* btn = ModUtils::createSprite(name);
    btn->setScale(0.8f);
    auto btnItem = CCMenuItemSpriteExtra::create(btn, menu, sus);
    btnItem->setPosition(pos);
    menu->addChild(btnItem);
}
bool __fastcall CreatorLayer_init(CreatorLayer* self, void* asd) {
    MappedHooks::getOriginal(CreatorLayer_init)(self, asd);
    CCMenu* menu = reinterpret_cast<CCMenu*>(self->getChildren()->objectAtIndex(2));
    if (menu) {//menu->getChildrenCount() == 2) {
        //row1
        addclbtn("GJ_createBtn_001.png", menu_selector(CreatorLayer::onMyLevels), { -180,90 }, menu);
        addclbtn("GJ_savedBtn_001.png", menu_selector(CreatorLayer::onSavedLevels), { -90,90 }, menu);
        addclbtn("GJ_highscoreBtn_001.png", menu_selector(CreatorLayer::onLeaderboards), { 0,90 }, menu);
        addclbtn("GJ_challengeBtn_001.png", menu_selector(CreatorLayer::onChallenge), { 90,90 }, menu);
        addclbtn("GJ_versusBtn_001.png", nullptr, { 180,90 }, menu);
        //row2
        addclbtn("GJ_mapBtn_001.png", menu_selector(CreatorLayerMod::onAdventureMap), { -180,0 }, menu);
        addclbtn("GJ_dailyBtn_001.png", menu_selector(CreatorLayer::onDailyLevel), { -90,0 }, menu);
        addclbtn("GJ_weeklyBtn_001.png", menu_selector(CreatorLayer::onWeeklyLevel), { 0,0 }, menu);
        addclbtn("GJ_eventBtn_001.png", menu_selector(CreatorLayerMod::onEventLevel), { 90,0 }, menu);
        addclbtn("GJ_gauntletsBtn_001.png", menu_selector(CreatorLayer::onGauntlets), { 180,0 }, menu);
        //row3
        addclbtn("GJ_featuredBtn_001.png", menu_selector(CreatorLayer::onFeaturedLevels), { -180,-90 }, menu);
        addclbtn("GJ_listsBtn_001.png", menu_selector(CreatorLayerMod::onTopLists), { -90,-90 }, menu);
        addclbtn("GJ_pathsBtn_001.png", menu_selector(CreatorLayerMod::onPaths), { 0,-90 }, menu);
        addclbtn("GJ_mapPacksBtn_001.png", menu_selector(CreatorLayer::onMapPacks), { 90,-90 }, menu);
        addclbtn("GJ_searchBtn_001.png", menu_selector(CreatorLayer::onOnlineLevels), { 180,-90 }, menu);
    }
    return true;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;
    MH_Initialize();
    MappedHooks::registerHook(base + 0x4de40, CreatorLayer_init);
    return TRUE;
}