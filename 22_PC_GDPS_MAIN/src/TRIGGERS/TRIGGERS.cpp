#include "ModUtils.hpp"
#include "HooksUtils.hpp"
using namespace cocos2d;
using namespace extension;
using namespace gd;

#define stop1 2701
#define stop2 2702
#define scale 2067
#define random 1912
#define adv_random 2068
#define zoom 1913
#define static_trig 1914
#define offset 1916
#define reverse 1917
#define song 1934
#define end 1931
#define stopJump 1932

PlayLayer* g_PlayLayer;
inline bool(__thiscall* LevelEditorLayer_init)(LevelEditorLayer*, GJGameLevel*);
bool __fastcall LevelEditorLayer_init_H(LevelEditorLayer* self, int edx, GJGameLevel* level) {
    g_PlayLayer = PlayLayer::create(level);
    g_PlayLayer->m_isTestMode;
    if (!LevelEditorLayer_init(self, level)) return false;
    CCLayerColor* THE_LINE = CCLayerColor::create({ 255,255,255,55 });
    THE_LINE->setAnchorPoint({ 0.f,0.f });
    THE_LINE->setPosition({ 0, CCDirector::sharedDirector()->getScreenTop() - 115 });
    THE_LINE->setScaleX({ 50 }); THE_LINE->setScaleY({ 0.002f });
    self->addChild(THE_LINE, -1);
    return true;
}

inline void(__thiscall* EditorUI_setupCreateMenu)(EditorUI*);
void __fastcall EditorUI_setupCreateMenu_H(EditorUI* self, void*) {
    EditorUI_setupCreateMenu(self);
    //tab14
    if (auto tab14 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(14))) {
        auto timeWarp = tab14->m_pButtonArray->objectAtIndex(4);
        tab14->m_pButtonArray->removeObjectAtIndex(4);
        tab14->m_pButtonArray->insertObject(self->getCreateBtn(2701, 5), 4);//stop
        tab14->m_pButtonArray->insertObject(self->getCreateBtn(2702, 5), 5);//stop
        tab14->m_pButtonArray->insertObject(self->getCreateBtn(2067, 5), 11);//scale
        tab14->m_pButtonArray->insertObject(self->getCreateBtn(1912, 5), 20);//random
        tab14->m_pButtonArray->insertObject(self->getCreateBtn(2068, 5), 21);//adv random
        tab14->m_pButtonArray->insertObject(self->getCreateBtn(zoom, 4), 22);//zoom
        tab14->m_pButtonArray->insertObject(self->getCreateBtn(static_trig, 4), 23);//static
        tab14->m_pButtonArray->insertObject(self->getCreateBtn(offset, 5), 24);//offset
        tab14->m_pButtonArray->insertObject(self->getCreateBtn(reverse, 4), 25);//reverse
        tab14->m_pButtonArray->insertObject(self->getCreateBtn(song, 4), 26);//song
        tab14->m_pButtonArray->insertObject(timeWarp, 27);//yo
        tab14->m_pButtonArray->insertObject(self->getCreateBtn(end, 4), 38);//end
        tab14->m_pButtonArray->insertObject(self->getCreateBtn(stopJump, 5), 39);//stopJump
        tab14->reloadItemsInNormalSize();
    }
}

inline void(__thiscall* editObject)(EditorUI*, cocos2d::CCObject*);
void __fastcall editObject_H(EditorUI* self, void*, cocos2d::CCObject* object) {
    if (self->m_pSelectedObject->m_nObjectID == stop1 ||
        self->m_pSelectedObject->m_nObjectID == stop2 ||
        self->m_pSelectedObject->m_nObjectID == scale ||
        self->m_pSelectedObject->m_nObjectID == random ||
        self->m_pSelectedObject->m_nObjectID == adv_random ||
        self->m_pSelectedObject->m_nObjectID == zoom ||
        self->m_pSelectedObject->m_nObjectID == static_trig ||
        self->m_pSelectedObject->m_nObjectID == offset ||
        self->m_pSelectedObject->m_nObjectID == reverse ||
        self->m_pSelectedObject->m_nObjectID == song ||
        self->m_pSelectedObject->m_nObjectID == end ||
        self->m_pSelectedObject->m_nObjectID == stopJump) {
        return self->editObject2(object);
    }
    editObject(self, object);
}

inline void(__thiscall* triggerObject)(GameObject*, GJBaseGameLayer*);//0xd1790
void __fastcall triggerObject_H(GameObject* self, void*, GJBaseGameLayer* baseGameLayer) {
    /*return */triggerObject(self, baseGameLayer);
    auto PlayerObj = baseGameLayer->m_pPlayer1;
    auto pPlayLayer = reinterpret_cast<PlayLayer*>(baseGameLayer);
    if (self->m_bEditor) {
        pPlayLayer = g_PlayLayer;
    }
    if (self->m_nObjectID == reverse) {
        if (PlayerObj->m_playerSpeed > 0.0) {
            //goleft
            PlayerObj->m_playerSpeed = -fabs(PlayerObj->m_playerSpeed);
            //negative scaleX if plr is not dart
            if (!PlayerObj->m_isDart && !PlayerObj->m_isShip) PlayerObj->setScaleX(-PlayerObj->m_vehicleSize);
            //ship flipping
            if (PlayerObj->m_isShip && GameManager::sharedState()->getPlayerShip() != 170) {
                if (!PlayerObj->m_isUpsideDown) PlayerObj->setScaleY(-PlayerObj->m_vehicleSize);
                else PlayerObj->setScaleY(fabs(PlayerObj->m_vehicleSize));
            }
            //negative rot patch by sai 1E9CD8: org b4 00 00 00 // patch 4c ff ff ff
            ModUtils::WriteProcMem(base + 0x1E9CD8, { 0x4c, 0xff, 0xff, 0xff });
            //ModUtils::write_bytes(base + 0x1E9CD8, { 0xb4, 0x00, 0x00, 0x00 });
        }
        else {
            //r
            PlayerObj->m_playerSpeed = fabs(PlayerObj->m_playerSpeed);
            //negative scaleX if plr is not dart
            if (!PlayerObj->m_isDart && !PlayerObj->m_isShip) PlayerObj->setScaleX(fabs(PlayerObj->m_vehicleSize));
            //ship flipping
            if (PlayerObj->m_isShip && GameManager::sharedState()->getPlayerShip() != 170) {
                if (!PlayerObj->m_isUpsideDown) PlayerObj->setScaleY(fabs(PlayerObj->m_vehicleSize));
                else PlayerObj->setScaleY(-PlayerObj->m_vehicleSize);
            }
            //negative rot patch by sai 1E9CD8: org b4 00 00 00 // patch 4c ff ff ff
            ModUtils::WriteProcMem(base + 0x1E9CD8, { 0xb4, 0x00, 0x00, 0x00 });
        }
    }
    if (self->m_nObjectID == end/* && !self->m_bEditor*/) {
        pPlayLayer->levelComplete();
        pPlayLayer->m_hasCompletedLevel = true;
        pPlayLayer->moveCameraToPos({ self->getPosition().x - (CCDirector::sharedDirector()->getWinSize().width / 2), self->getPosition().y - (CCDirector::sharedDirector()->getWinSize().height / 2) });
        PlayerObj->m_isLocked = 1;
    }
    if (self->m_nObjectID == zoom) {
        CCLayer* layerToZoom = self->m_bEditor ? baseGameLayer->m_pObjectLayer : baseGameLayer;
        layerToZoom->runAction(CCEaseInOut::create(CCScaleTo::create(self->m_fAnimSpeed, self->m_fScale), 2.00f));
        if (!self->m_bEditor) layerToZoom->runAction(CCEaseInOut::create(CCRotateTo::create(self->m_fAnimSpeed, self->getRotation()), 2.00f));
    }
    if (self->m_nObjectID == song) {
        GameSoundManager::sharedState()->stopBackgroundMusic();
        if (self->m_bRandomisedAnimStart) {
            auto oldOffset = pPlayLayer->m_levelSettings->m_songOffset;
            auto offsetbylr = 0.f;
            if(!self->m_bEditor) offsetbylr = 0.9f;
            pPlayLayer->m_levelSettings->m_songOffset = self->m_fAnimSpeed * 100 - offsetbylr;
            pPlayLayer->startMusic();
            pPlayLayer->m_levelSettings->m_songOffset = oldOffset;
        };
    }
    if (self->m_nObjectID == static_trig) {
        if (!self->m_bEditor) {
            if (self->m_bRandomisedAnimStart) {
                CCPoint tarPos({ 
                self->getPosition().x - (CCDirector::sharedDirector()->getWinSize().width / 2),
                self->getPosition().y - (CCDirector::sharedDirector()->getWinSize().height / 2) 
                    });
                if (self->m_bIsRotatedSide) pPlayLayer->runAction(CCEaseInOut::create(CCActionTween::create(
                            self->m_fAnimSpeed, "cTY", pPlayLayer->m_cameraY, tarPos.y
                        ), 2.00f));
                else pPlayLayer->runAction(CCEaseInOut::create(CCActionTween::create(
                            self->m_fAnimSpeed, "cTX", pPlayLayer->m_cameraX, tarPos.x
                        ), 2.00f));
            }
            else {

                if (self->m_bIsRotatedSide) pPlayLayer->m_cameraYLocked = !pPlayLayer->m_cameraYLocked;
                else pPlayLayer->m_cameraXLocked = !pPlayLayer->m_cameraXLocked;
            }
        };
    }
}
#define bShitThatThisMFGAMECANSAVE m_bIsGlowDisabled
void setTrigger(EffectGameObject* self, bool atGettingByString) {
    auto id = self->m_nObjectID;
    //basicsetup
    if (id == song or id == zoom or id == static_trig or id == end or id == reverse) {
        if(!atGettingByString) self->m_bIsEffectObject = true;
        else self->m_bTouchTriggered = self->bShitThatThisMFGAMECANSAVE;
    }
}
inline void(__thiscall* GameObject_customSetup)(GameObject*);
void __fastcall GameObject_customSetup_H(GameObject* self, int) {
    GameObject_customSetup(self);
    auto ego = reinterpret_cast<EffectGameObject*>(self);
    setTrigger(ego, false);
    //pEffectGameObject
    if (self->m_nObjectID == 1814) self->setDisplayFrame(cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
        "edit_eCameraBtn_001.png"));
    if (self->m_nObjectID == 1817) self->setDisplayFrame(cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
        "edit_e2.2Btn_001.png"));
}

static EffectGameObject* g_pObject;
static CCArray* g_pObjects;
static CCLabelBMFont* g_saveString;
class SetupAnimSettingsPopup : public FLAlertLayer {
public:
    CCTextInputNode* getTextInput() {
        return reinterpret_cast<CCTextInputNode*>(this->m_pLayer->getChildren()->objectAtIndex(5));
    }
    void onTouch(CCObject* sneder) { 
        g_pObject->bShitThatThisMFGAMECANSAVE = !g_pObject->bShitThatThisMFGAMECANSAVE;// == 1337 ? 0 : 1337;
        g_pObject->m_bTouchTriggered = g_pObject->bShitThatThisMFGAMECANSAVE;
    }
    void onPlaySound(CCObject* sneder) { 
        triggerObject_H(g_pObject, nullptr, GameManager::sharedState()->getEditorLayer());
    }
    void schupdate(float) {
        g_pObject->m_fAnimSpeed = atof(getTextInput()->getString());
        g_saveString->setString(g_pObject->getSaveString().c_str());
    }
};
//rva 0x233000
bool __fastcall SetupAnimSettingsPopupInit(SetupAnimSettingsPopup* __this, void* yp, EffectGameObject* pObject, cocos2d::CCArray* pObjects) {
    auto rtn = MappedHooks::getOriginal(SetupAnimSettingsPopupInit)(__this, yp, pObject, pObjects);
    //__this->setRotation(3);
    //add btns spawn and touch dk
    if (pObject->m_nObjectID == stop1 ||
        pObject->m_nObjectID == stop2 ||
        pObject->m_nObjectID == scale ||
        pObject->m_nObjectID == random ||
        pObject->m_nObjectID == adv_random ||
        pObject->m_nObjectID == zoom ||
        pObject->m_nObjectID == static_trig ||
        pObject->m_nObjectID == offset ||
        pObject->m_nObjectID == reverse ||
        pObject->m_nObjectID == song ||
        pObject->m_nObjectID == end ||
        pObject->m_nObjectID == stopJump) {

        g_pObject = pObject;
        g_pObjects = pObjects;

        g_saveString = CCLabelBMFont::create(pObject->getSaveString().c_str(), "chatFont.fnt", 160.f);
        __this->m_pButtonMenu->addChild(g_saveString);
        g_saveString->setOpacity(160);
        g_saveString->setPositionY(-35.000f);
        //touchnspawn
        {

            auto onTouchBtn = CCMenuItemToggler::createWithStandardSprites(__this, menu_selector(SetupAnimSettingsPopup::onTouch));
            onTouchBtn->setScale(0.7f);
            onTouchBtn->setPosition(-128.0f, 0.5f);
            onTouchBtn->toggle(pObject->bShitThatThisMFGAMECANSAVE);
            __this->m_pButtonMenu->addChild(onTouchBtn);

            auto TouchTriggered = CCLabelBMFont::create("Touch    \nTriggered", "bigFont.fnt");
            TouchTriggered->setScale(0.37f);
            TouchTriggered->setPosition({ -78.0f, 0.5f });
            __this->m_pButtonMenu->addChild(TouchTriggered);
        };
        if (pObject->m_nObjectID == song) {
            auto onPlaySoundBtn = CCMenuItemSpriteExtra::create(ModUtils::createSprite("GJ_playMusicBtn_001.png"), __this, menu_selector(SetupAnimSettingsPopup::onPlaySound));
            onPlaySoundBtn->setPosition(120.000f, 8.000f);
            __this->m_pButtonMenu->addChild(onPlaySoundBtn);
        }
        __this->schedule(schedule_selector(SetupAnimSettingsPopup::schupdate));
    }
    return rtn;
}

GameObject* (__cdecl* objectFromString)(std::string, bool);
GameObject* objectFromString_H(std::string str, bool idk) {
    //GameObject* obj = objectFromString(str, idk);
    //if (obj->m_nObjectID == 1913) {
    //    //obj = reinterpret_cast<EffectGameObject*>(obj);
    //    //if (strstr(std::string(str).c_str(), "11,1")) obj->m_bTouchTriggered = true;
    //    obj->m_bIsGroupParent = true;
    //}
    //return obj;
    auto go = objectFromString(str, idk);
    if (go) {
        auto ego = reinterpret_cast<EffectGameObject*>(go);
        setTrigger(ego, true);
        return ego;
    }
    return go;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;
    MH_Initialize();
    HOOK(base + 0x15ee00, LevelEditorLayer_init);
    HOOK(base + 0x7CAF0, EditorUI_setupCreateMenu);//huh
    HOOK(base + 0xd1c10, GameObject_customSetup);
    HOOK(base + 0xd1790, triggerObject);
    HOOK(base + 0x8ca50, editObject);
    HOOK(base + 0xEBE50, objectFromString);
    MappedHooks::registerHook(base + 0x233000, SetupAnimSettingsPopupInit);
    return TRUE;
}