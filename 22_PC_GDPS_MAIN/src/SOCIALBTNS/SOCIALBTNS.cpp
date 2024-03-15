#include "ModUtils.hpp"
#include "HooksUtils.hpp"
using namespace cocos2d;
using namespace extension;
class MenuLayer : public gd::MenuLayer {
public:
    void onTwitch(cocos2d::CCObject* pSender) { CCApplication::sharedApplication()->openURL("https://www.twitch.tv/robtopgames"); }
    void onDiscord(cocos2d::CCObject* pSender) { CCApplication::sharedApplication()->openURL("https://discord.com/invite/geometrydash"); }
    void customSetup(float) {
        //socialsMenu
        auto socialsMenu = CCMenu::create();
        this->addChild(socialsMenu, 2);
        socialsMenu->setPosition({ 50, 30 - 6 });
        //robtopLogo
        auto robtopLogo = ModUtils::createSprite("robtoplogo_small.png");
        robtopLogo->setScale(0.8f);
        auto robtopExtra = gd::CCMenuItemSpriteExtra::create(robtopLogo, this, menu_selector(MenuLayer::onRobTop));
        socialsMenu->addChild(robtopExtra);
        //facebookIcon
        auto facebookIcon = ModUtils::createSprite("gj_fbIcon_001.png");
        facebookIcon->setScale(0.8f);
        auto facebookExtra = gd::CCMenuItemSpriteExtra::create(facebookIcon, this, menu_selector(MenuLayer::onFacebook));
        facebookExtra->setSizeMult(1.5f);
        socialsMenu->addChild(facebookExtra);
        //twitterIcon
        auto twitterIcon = ModUtils::createSprite("gj_twIcon_001.png");
        twitterIcon->setScale(0.8f);
        auto twitterExtra = gd::CCMenuItemSpriteExtra::create(twitterIcon, this, menu_selector(MenuLayer::onTwitter));
        twitterExtra->setSizeMult(1.5f);
        socialsMenu->addChild(twitterExtra);
        //youtubeIcon
        auto youtubeIcon = ModUtils::createSprite("gj_ytIcon_001.png");
        youtubeIcon->setScale(0.8f);
        auto youtubeExtra = gd::CCMenuItemSpriteExtra::create(youtubeIcon, this, menu_selector(MenuLayer::onYouTube));
        youtubeExtra->setSizeMult(1.5f);
        socialsMenu->addChild(youtubeExtra);
        //twitchIcon
        auto twitchIcon = ModUtils::createSprite("gj_twitchIcon_001.png");
        twitchIcon->setScale(0.8f);
        auto twitchExtra = gd::CCMenuItemSpriteExtra::create(twitchIcon, this, menu_selector(MenuLayer::onTwitch));
        twitchExtra->setSizeMult(1.5f);
        socialsMenu->addChild(twitchExtra);
        //discordIcon
        auto discordIcon = ModUtils::createSprite("gj_discordIcon_001.png");
        discordIcon->setScale(0.8f);
        auto discordExtra = gd::CCMenuItemSpriteExtra::create(discordIcon, this, menu_selector(MenuLayer::onDiscord));
        discordExtra->setSizeMult(1.5f);
        socialsMenu->addChild(discordExtra);
        //set created btns
        facebookExtra->setPosition(socialsMenu->convertToNodeSpace(CCPoint({ CCDirector::sharedDirector()->getScreenLeft() + 22, CCDirector::sharedDirector()->getScreenBottom() + 55 })));
        twitterExtra->setPosition(facebookExtra->getPosition() + CCPoint({ 30, 0 }));
        youtubeExtra->setPosition(twitterExtra->getPosition() + CCPoint({ 30, 0 }));
        twitchExtra->setPosition(youtubeExtra->getPosition() + CCPoint({ 29, 0 }));
        discordExtra->setPosition(youtubeExtra->getPosition() + CCPoint({ 29, -29 }));
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