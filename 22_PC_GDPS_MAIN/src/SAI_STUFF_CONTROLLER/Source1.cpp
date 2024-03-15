#include "ModUtils.hpp"
#include "HooksUtils.hpp"
#include "customLayerxd.hpp"
using namespace cocos2d;
using namespace extension;

bool __fastcall LevelSettingsLayer_init(gd::FLAlertLayer* self, void* fuckthis, gd::LevelSettingsObject* levelSettings, gd::LevelEditorLayer* editor) {
    if (!MappedHooks::getOriginal(LevelSettingsLayer_init)(self, fuckthis, levelSettings, editor) or !self) return false;
    auto pMenu = self->m_pButtonMenu;
    //for PLAT. there is overlapping button by sai
    for (int i = 0; i < pMenu->getChildrenCount(); i++) {
        auto testNode = static_cast<CCNode*>(pMenu->getChildren()->objectAtIndex(i));
        const CCPoint& tarPos = CCPoint(-149.000f, -129.750f);
        if (testNode and testNode->getPosition().equals(tarPos) and testNode->getChildrenCount() == 1) {
            testNode->removeMeAndCleanup();
        }
    };
    return true;
}
bool __fastcall CreatorLayerInit(gd::CreatorLayer* self) {
    MappedHooks::getOriginal(CreatorLayerInit)(self);
    //remove sai's layer or what the fuck is that
    CCLayer* shit = dynamic_cast<CCLayer*>(self->getChildren()->objectAtIndex(0));
    if (shit and shit->getZOrder() == 100) self->removeChild(shit);
    return true;
}
bool __fastcall MenuLayer_init(gd::MenuLayer* self) {
    MappedHooks::getOriginal(MenuLayer_init)(self);

    //the mana principal from msvcr180.dll
    CCLayer* manaprincipalfrommsvcr180sonyx114promax = (CCLayer*)self->getChildren()->objectAtIndex(0);
    if (manaprincipalfrommsvcr180sonyx114promax->getZOrder() == 100) manaprincipalfrommsvcr180sonyx114promax->removeFromParent();
    //and then otrer shit from SaiModPack.dll
    CCLayer* SaiModPackThings = (CCLayer*)self->getChildren()->objectAtIndex(0);
    if (SaiModPackThings->getZOrder() == 100) SaiModPackThings->removeFromParent();

    return true;
}
bool __fastcall garageinit(gd::GJGarageLayer* self) {
    MappedHooks::getOriginal(garageinit)(self);
    //remove some idk nn random corners
    self->removeChild((CCLayer*)self->getChildren()->objectAtIndex(0));
    //saimodpacklayer
    CCLayer* saimodpacklayer = (CCLayer*)self->getChildren()->objectAtIndex(7); //this is carazy shit 7
    if (saimodpacklayer->getZOrder() == 1000) saimodpacklayer->getChildren()->removeLastObject();//remove socials
    CCMenu* menu = (CCMenu*)self->getChildren()->objectAtIndex(19); //this is carazy shit 19
    if (menu->getChildrenCount() == 5) {
        menu->getChildren()->removeLastObject();//remove infbtn
        menu->getChildren()->removeLastObject();//and remove colorsBtn
    }
    return true;
}

class schNoResstartFix : public gd::PlayLayer {
public:
    void a(float) {
        if (!this) return;
        if (this->m_isDead && !this->m_bIsPaused && !this->m_hasCompletedLevel) {
            this->resetLevel();
        }
    }
};
inline void(__thiscall* PlayLayer_resetLevel)(gd::PlayLayer*);
void __fastcall PlayLayer_resetLevel_H(gd::PlayLayer* self) {
    self->m_pObjectLayer->setScale(1.0);
    self->m_bottomGround->setScale(1.0);
    self->m_topGround->setScaleX(1.0);
    self->unschedule(schedule_selector(schNoResstartFix::a));
}

class ProfilePage : public gd::ProfilePage {};
class SimplePlayer : public gd::SimplePlayer {
public:
    void controller(float) {
        if (auto pProfilePage = dynamic_cast<ProfilePage*>(this->getParent()->getParent()); pProfilePage) {
            std::stringstream num;
            num << std::setw(2) << std::setfill('0') << pProfilePage->m_score->getPlayerCube();
            bool isCube = strstr(
                ModUtils::getFrameName(this->m_pFirstLayer).c_str(),
                std::format("player_{}_001.png", num.str()).c_str()
            ) or strstr(
                ModUtils::getFrameName(this->m_pFirstLayer).c_str(),
                std::format("player_01_001.png", num.str()).c_str()
            );
                //(std::string(this->m_firstLayer) == "player_01_001.png");
            if (isCube)
                if (pProfilePage->m_pLayer->getChildByTag(1773))
                    this->setFrames("swing_01_001.png", "swing_01_2_001.png", nullptr, "swing_01_glow_001.png", "swing_01_extra_001.png");
                else
                    this->setTag(1773);
        }
    }
};
void __fastcall SimplePlayerSetFrames(SimplePlayer* pClass, void* fuckthis, const char* firstLayer, const char* secondLayer, const char* birdDome, const char* outlineSprite, const char* detailSprite) {
    //reinterpret_cast<void(__thiscall*)(SimplePlayer*, const char*, const char*, const char*, const char*, const char*)>(
        //base + 0x12c9e0)
        //(this, firstLayer, secondLayer, birdDome, outlineSprite, detailSprite);
    MappedHooks::getOriginal(SimplePlayerSetFrames)(pClass, fuckthis, firstLayer, secondLayer, birdDome, outlineSprite, detailSprite);
    pClass->scheduleOnce(schedule_selector(SimplePlayer::controller), 0.001f);
}

CCSprite* (__cdecl* CCSprite_create)(const char*);
CCSprite* CCSprite_create_H(const char* name) {
    auto rtn = CCSprite_create(name);
    if (std::string(name) == "GJ_colores_001.png" || std::string(name) == "GJ_paletaBtn_001.png")
        return ModUtils::createSprite("GJ_paintBtn_001.png");
    return rtn;
}
CCSprite* (__cdecl* CCSprite_createWithSpriteFrameName)(const char*);
CCSprite* CCSprite_createWithSpriteFrameName_H(const char* name) {
    auto rtn = CCSprite_createWithSpriteFrameName(name);
    if (std::string(name) == "groundSquareShadow_001.png") 
        return CCSprite::create();
    if (std::string(name) == "GJ_colores_001.png" || std::string(name) == "GJ_paletaBtn_001.png")
        return ModUtils::createSprite("GJ_paintBtn_001.png");
    return rtn;
}

class TextAlertPopup : public gd::TextAlertPopup {};
class PaletaDeColores : public gd::FLAlertLayer {};
class CreatedLabelController : public CCLabelBMFont {
public:
    void labelCustomSetups(float) {
        if (!dynamic_cast<CCLabelBMFont*>(this)) return;
        if (std::string(this->getString()) == "Mod Pack - By Sai") {
            this->setRotation(12);
            if (auto pTextAlertPopup = dynamic_cast<TextAlertPopup*>(this->getParent()); pTextAlertPopup) {
                pTextAlertPopup->setVisible(0);
                customLayerxd::create()->switchcustomLayerxdbtn(pTextAlertPopup);
            }
        }
        if (std::string(this->getString()) == "Select Color") {
            this->setVisible(0);
            if (auto pPaletaDeColores = dynamic_cast<PaletaDeColores*>(this->getParent()->getParent()); pPaletaDeColores) {
                //pPaletaDeColores->setRotation(3);
                //soo we got that... for future?
            }
        }
    }
};
CCLabelBMFont* (__cdecl* CCLabelBMFont_create)(const char*, const char*);
CCLabelBMFont* CCLabelBMFont_create_H(const char* str, const char* fntFile) {
    auto rtn = CCLabelBMFont_create(str, fntFile);
    if (rtn) rtn->scheduleOnce(schedule_selector(CreatedLabelController::labelCustomSetups), 0.001f);
    return rtn;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;
    MH_Initialize();
    MappedHooks::registerHook(gd::base + 0x170e50, LevelSettingsLayer_init);
    MappedHooks::registerHook(gd::base + 0x4DE40, CreatorLayerInit);
    MappedHooks::registerHook(gd::base + 0x1907b0, MenuLayer_init);
    MappedHooks::registerHook(gd::base + 0x1255D0, garageinit);
    MappedHooks::registerHook(gd::base + 0x12c9e0, SimplePlayerSetFrames);
    HOOK(gd::base + 0x20BF00, PlayLayer_resetLevel);
    CC_HOOK("?createWithSpriteFrameName@CCSprite@cocos2d@@SAPAV12@PBD@Z", CCSprite_createWithSpriteFrameName);
    CC_HOOK("?create@CCLabelBMFont@cocos2d@@SAPAV12@PBD0@Z", CCLabelBMFont_create);
    return TRUE;
}