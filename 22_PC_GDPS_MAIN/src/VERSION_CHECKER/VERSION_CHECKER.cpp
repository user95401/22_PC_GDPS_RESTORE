#include "ModUtils.hpp"
#include "HooksUtils.hpp"
#include "customLayerxd.hpp"
using namespace cocos2d;
using namespace extension;
auto version = "v1.13";
class MenuLayer : public gd::MenuLayer {
public:
    void onUpdateHttpResponse(CCHttpClient* client, CCHttpResponse* response) {
        std::vector<char>* responseData = response->getResponseData();
        std::string responseString(responseData->begin(), responseData->end());
        if (responseString != version && response->getResponseCode() == 200) {
            gd::AchievementNotifier::sharedState()->notifyAchievement(
                "Update available!",
                ("You can download actual " + responseString + " version on the website.").c_str(),
                "GJ_downloadsIcon_001.png",
                true
            );
        }
        if (response->getResponseCode() != 200) {
            //create and setup AchievementBar_
            gd::AchievementBar* AchievementBar_ = gd::AchievementBar::create(
                "Server problems!",
                ("Response code is not 200 (its " + std::to_string(response->getResponseCode()) + "),\n that means problems with server.").c_str(),
                "exMark_001.png",
                true
            );
            //create and setup discordBtn
            auto discordBtn = gd::CCMenuItemSpriteExtra::create(
                ModUtils::createSprite("gj_discordIcon_001.png"),
                AchievementBar_,
                menu_selector(customLayerxd::discord_openURL)
            );
            discordBtn->gd::CCMenuItemSpriteExtra::setScale(1.8f);
            discordBtn->setPositionY(-128.f);
            discordBtn->runAction(CCSequence::create(
                CCEaseExponentialOut::create(CCMoveTo::create(0.5f, { 0.f, -((CCDirector::sharedDirector()->getWinSize().height / 20) - 20.f) })),
                CCDelayTime::create(2.0f),
                CCEaseExponentialIn::create(CCMoveTo::create(0.5f, { 0.f, -(CCDirector::sharedDirector()->getWinSize().height) })),
                nullptr
            ));
            //create and add discordBtnLabel
            auto discordBtnLabel = CCLabelBMFont::create("Join Official Discord Server\nFor getting last news!\n \n \n \n \n \n \n \n ", "goldFont.fnt");
            discordBtnLabel->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);
            discordBtnLabel->setPositionX(discordBtn->getContentSize().width / 2);
            discordBtnLabel->setScale(0.4f);
            discordBtn->addChild(discordBtnLabel);
            //add menu with discordBtn to AchievementBar_
            AchievementBar_->addChild(CCMenu::createWithItem(discordBtn));
            //add to m_pQueue and show
            gd::AchievementNotifier::sharedState()->m_pQueue->addObject(AchievementBar_);
            if (!gd::AchievementNotifier::sharedState()->m_pCurrentAchievement) {
                gd::AchievementNotifier::sharedState()->showNextAchievement();
            }
        }
    }
    void customSetup(float) {
        //versionLabel
        auto versionLabel = CCLabelBMFont::create(version, "chatFont.fnt");
        versionLabel->setPosition({ CCDirector::sharedDirector()->getScreenRight(), 0});
        versionLabel->setAnchorPoint({ 1.1f, 0 });
        versionLabel->setOpacity({ 130 });
        versionLabel->setScale({ 0.5f });
        this->addChild(versionLabel);
        auto fadeTo200 = CCFadeTo::create(5, 200);
        auto fadeTo130 = CCFadeTo::create(5, 130);
        auto versionLabelseq = CCSequence::create(fadeTo200, fadeTo130, nullptr);
        auto versionLabelrepeat = CCRepeatForever::create(versionLabelseq);
        versionLabel->runAction(versionLabelrepeat);
        //udate if sddso herer
        if (!strstr(version, "pre")) {
            CCHttpRequest* request = new CCHttpRequest;
            request->setUrl("http://gdps22pc.7m.pl/lastUpdate.php");
            request->setRequestType(CCHttpRequest::HttpRequestType::kHttpPost);
            request->setResponseCallback(this, httpresponse_selector(MenuLayer::onUpdateHttpResponse));
            CCHttpClient::getInstance()->send(request);
            request->release();
        }
    }
};
bool (__thiscall* CCLayer_init)(CCLayer* pClass);
bool __fastcall CCLayer_init_H(CCLayer* pClass) {
        auto rtn = CCLayer_init(pClass);
        //MenuLayer
        if (auto pMenuLayer = dynamic_cast<MenuLayer*>(pClass); pMenuLayer)
            pMenuLayer->scheduleOnce(schedule_selector(MenuLayer::customSetup), 0.001f);
        return rtn;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;
    MH_Initialize();
    CC_HOOK("?init@CCLayer@cocos2d@@UAE_NXZ", CCLayer_init);
    return TRUE;
}