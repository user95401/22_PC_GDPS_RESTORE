﻿// 22_PC_GDPS_MAIN.cpp: определяет точку входа для приложения.
//
#include "22_PC_GDPS_MAIN.h"

bool hooksLoaded = false;
int oldShipIcon;

void ModBase::ondontgiveashit(cocos2d::CCObject*) {
    idontgiveashitbro = (!idontgiveashitbro);
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, MenuLayer::scene(0)));
    GameSoundManager::sharedState()->playEffect("quitSound_01.ogg");
}
void ModBase::bringBackSavedIcons() {
    printf(__FUNCTION__"\n");
    GameManager::sharedState()->setPlayerFrame(GameManager::sharedState()->getIntGameVariable("oldFrameIcon"));//bring up by oldShipIcon
    GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
    GameManager::sharedState()->setPlayerBall(GameManager::sharedState()->getIntGameVariable("oldBallIcon"));//bring up by oldBallIcon
    GameManager::sharedState()->setPlayerBird(GameManager::sharedState()->getIntGameVariable("oldBirdIcon"));//bring up by oldBirdIcon
    GameManager::sharedState()->setPlayerDart(GameManager::sharedState()->getIntGameVariable("oldDartIcon"));//bring up by oldDartIcon
    GameManager::sharedState()->setPlayerRobot(GameManager::sharedState()->getIntGameVariable("oldRobotIcon"));//bring up by oldRobotIcon
    GameManager::sharedState()->setPlayerSpider(GameManager::sharedState()->getIntGameVariable("oldSpiderIcon"));//bring up by oldSpiderIcon
    GameManager::sharedState()->setPlayerStreak(GameManager::sharedState()->getIntGameVariable("oldStreak"));//bring up by oldStreak
    GameManager::sharedState()->setPlayerDeathEffect(GameManager::sharedState()->getIntGameVariable("oldDeathEffect"));//bring up by oldDeathEffect
    GameManager::sharedState()->setPlayerGlow(GameManager::sharedState()->getIntGameVariable("oldGlow"));//bring up by oldGlow
    GameManager::sharedState()->setPlayerColor(GameManager::sharedState()->getIntGameVariable("oldColor"));//bring up by oldColor
    GameManager::sharedState()->setPlayerColor2(GameManager::sharedState()->getIntGameVariable("oldColor2"));//bring up by oldColor2
}
void ModBase::saveIcons() {
    printf(__FUNCTION__"\n");
    GameManager::sharedState()->setIntGameVariable("oldFrameIcon", GameManager::sharedState()->getPlayerFrame());//save oldFrameIcon
    GameManager::sharedState()->setIntGameVariable("oldShipIcon", GameManager::sharedState()->getPlayerShip());//save oldShipIcon
    GameManager::sharedState()->setIntGameVariable("oldBallIcon", GameManager::sharedState()->getPlayerBall());//save oldBallIcon
    GameManager::sharedState()->setIntGameVariable("oldBirdIcon", GameManager::sharedState()->getPlayerBird());//save oldBirdIcon
    GameManager::sharedState()->setIntGameVariable("oldDartIcon", GameManager::sharedState()->getPlayerDart());//save oldDartIcon
    GameManager::sharedState()->setIntGameVariable("oldRobotIcon", GameManager::sharedState()->getPlayerRobot());//save oldRobotIcon
    GameManager::sharedState()->setIntGameVariable("oldSpiderIcon", GameManager::sharedState()->getPlayerSpider());//save oldSpiderIcon
    GameManager::sharedState()->setIntGameVariable("oldStreak", GameManager::sharedState()->getPlayerStreak());//save oldStreak
    GameManager::sharedState()->setIntGameVariable("oldDeathEffect", GameManager::sharedState()->getPlayerDeathEffect());//save oldDeathEffect
    GameManager::sharedState()->setIntGameVariable("oldGlow", GameManager::sharedState()->getPlayerGlow());//save oldGlow
    GameManager::sharedState()->setIntGameVariable("oldColor", GameManager::sharedState()->getPlayerColor());//save oldColor
    GameManager::sharedState()->setIntGameVariable("oldColor2", GameManager::sharedState()->getPlayerColor2());//save oldColor
    GameManager::sharedState()->save();
}
void ModBase::msg(CCLayer* self, const char* redText, const char* customMsg) {
    CCLabelTTF* msg = CCLabelTTF::create(
        "OBJECT HASN'T FOUNDED\nseems u delete or add some mods\n\n that prevent getting objects\n in this layer",
        "Comic Sans MS",
        120.0f);
    if (customMsg != "") msg = CCLabelTTF::create(customMsg, "Comic Sans MS", 80.0f);
    msg->setPosition(ModUtils::getCenterPoint());
    msg->setScale(0.150f);//120.0f for lbl fontSize
    CCLabelTTF* msg2 = CCLabelTTF::create(redText, "Comic Sans MS", 120.0f);
    msg2->setPosition({ msg->getContentSize().width / 2,  msg->getContentSize().height / 2 });
    msg2->setColor({ 255, 70, 70 });
    msg->addChild(msg2);
    if (!idontgiveashitbro) self->removeAllChildren(); //:trollface:
    if (!idontgiveashitbro) self->addChild(msg, 666, 666);
    if (!idontgiveashitbro) GameManager::sharedState()->fadeInMusic("shop3.mp3");
    CCMenu* dontgiveashit = CCMenu::createWithItem(
        CCMenuItemSpriteExtra::create(
            ButtonSprite::create("i dont give a shit, bro", 80, false, "gjFont06.fnt", "GJ_button_05.png", 30, 5.0f),
            self,
            menu_selector(ModBase::ondontgiveashit)
        )
    );
    dontgiveashit->setPositionY(dontgiveashit->getPositionY() - 120.0f);
    if (!idontgiveashitbro) self->addChild(dontgiveashit);
}


inline void(__thiscall* LoadingLayer_loadAssets)(LoadingLayer*);
void __fastcall LoadingLayer_loadAssets_H(LoadingLayer* self, void*) {
    LoadingLayer_loadAssets(self);
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    CCSprite* fmodLogo = ModUtils::createSprite("fmodLogo.png");
    self->removeChildByTag(9230);
    fmodLogo->setTag(9230);
    fmodLogo->setPosition({ winSize.width - 35, 30 });
    fmodLogo->setColor(ccc3(1, 1, 1));
    fmodLogo->setScale({ 0.7f });
    self->addChild(fmodLogo);

    CCSprite* cocos2DxLogo = ModUtils::createSprite("cocos2DxLogo.png");
    self->removeChildByTag(1086);
    fmodLogo->setTag(1086);
    cocos2DxLogo->setPosition({ winSize.width - 35, 12 });
    cocos2DxLogo->setScale({ 0.7f });
    self->addChild(cocos2DxLogo);

    if (self->m_nLoadIndex == 6) {
        //_ModsResources
        CCTextureCache::sharedTextureCache()->addImage("_ModsResources.png", 0);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("_ModsResources.plist");
        //game001Sheet platformer btns from other game :>
        CCTextureCache::sharedTextureCache()->addImage("game001Sheet.png", 0);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("game001Sheet.plist");
        //GJ_ParticleSheet
        CCTextureCache::sharedTextureCache()->addImage("GJ_ParticleSheet.png", 0);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("GJ_ParticleSheet.plist");
        //GJ_ParticleSheet
        CCTextureCache::sharedTextureCache()->addImage("PixelSheet_01.png", 0);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("PixelSheet_01.plist");
        //TreasureRoomSheet
        CCTextureCache::sharedTextureCache()->addImage("TreasureRoomSheet.png", 0);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("TreasureRoomSheet.plist");
        //TowerSheet
        CCTextureCache::sharedTextureCache()->addImage("TowerSheet.png", 0);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("TowerSheet.plist");

        CCFileUtils::sharedFileUtils()->addSearchPath("mods");
        CCFileUtils::sharedFileUtils()->addSearchPath("adaf-dll");

        //ObjectToolbox::sharedState()->addObject(2140, "pixelart_040_001.png");
    }
    self->removeChildByTag(777);
    if (!hooksLoaded && self->m_nLoadIndex > 8) {
        self->m_nLoadIndex = 8;
        self->addChild(
            CCLabelTTF::create("                                   Waiting for hooks...\n\n",
            "Comic Sans MS", 10)
        , 5, 777);
    }
    if(hooksLoaded && !self->m_bFromRefresh) self->addChild(
            CCLabelTTF::create("                                 All hooks enabled!\n\n",
            "Comic Sans MS", 10)
        , 5, 777);
}

inline CCSprite* (__cdecl* CCSprite_create)(const char*);
CCSprite* CCSprite_create_H(const char* name) {
    if (strstr(name, "1337")) {
        CCSprite* no = CCSprite::create();
        //MessageBoxA(nullptr, name,"CCSprite_createHook -> no sprite", MB_ICONINFORMATION | MB_OK);
        return no;
    }
    if (std::string(name) == "GJ_colores_001.png" || std::string(name) == "GJ_paletaBtn_001.png")
        return ModUtils::createSprite("GJ_paintBtn_001.png");
    return CCSprite_create(name);
}

inline CCSprite* (__cdecl* CCSprite_createWithSpriteFrameName)(const char*);
CCSprite* CCSprite_createWithSpriteFrameName_H(const char* name) {
    if (std::string(name) == "groundSquareShadow_001.png" ||
        strstr(name, "1337")) {
        CCSprite* no = CCSprite::create();
        //MessageBoxA(nullptr, name, "CCSprite_createWithSpriteFrameNameHook -> no sprite", MB_ICONINFORMATION | MB_OK);
        return no;
    }
    if (std::string(name) == "GJ_colores_001.png" || std::string(name) == "GJ_paletaBtn_001.png")
        return ModUtils::createSprite("GJ_paintBtn_001.png");
    return CCSprite_createWithSpriteFrameName(name);
}

inline CCLabelBMFont* (__cdecl* CCLabelBMFont_create)(const char*, const char*);
CCLabelBMFont* CCLabelBMFont_create_H(const char* str, const char* fntFile) {
    //if (strstr(str, "1337")) {
    //    CCLabelBMFont* lbl = CCLabelBMFont::create("", "gjFont01.fnt");
    //    lbl->setVisible(false);
    //    lbl->setAnchorPoint({ -999.0f,-999.0f });
    //    //MessageBoxA(nullptr, str, "CCLabelBMFont_createHook -> no lbl", MB_ICONINFORMATION | MB_OK);
    //    return lbl;
    //}
    if (std::string(str) == "Practice music hack" || std::string(str) == "Show level info" ||  std::string(str) == "Hide attempt label")
        str = "Available in Gameplay Options only";
    if (std::string(str) == "Select Color") 
        str = "";
    //SetupAnimSettingsPopup
    if("SetupAnimSettingsPopup") {
        if (std::string(str) == "Edit Animation Settings") {
            if (LevelEditor::LevelEditor::lastSelectedObj->m_nObjectID == 3004 || LevelEditor::lastSelectedObj->m_nObjectID == 3005 //spider orb anda pad
                || LevelEditor::lastSelectedObj->m_nObjectID == 35 || LevelEditor::lastSelectedObj->m_nObjectID == 140 || LevelEditor::lastSelectedObj->m_nObjectID == 1332 || LevelEditor::lastSelectedObj->m_nObjectID == 67 //bumps
                || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeShipPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeCubePortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeBallPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeUfoPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeWavePortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeRobotPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeSpiderPortal //noground portals
                || LevelEditor::lastSelectedObj->m_nObjectID == 1934 //song trigger
                )
                str = "Object setup";
            if (LevelEditor::lastSelectedObj->m_nObjectID == 1913)
                str = "Zoom thing setup...";
            if (LevelEditor::lastSelectedObj->m_nObjectID == 1934)
                str = "Song trigger setup";
        }
        if (std::string(str) == "Speed: ") {
            if (LevelEditor::lastSelectedObj->m_nObjectID == 3004 || LevelEditor::lastSelectedObj->m_nObjectID == 3005  //spider orb anda pad
                || LevelEditor::lastSelectedObj->m_nObjectID == 35 || LevelEditor::lastSelectedObj->m_nObjectID == 140 || LevelEditor::lastSelectedObj->m_nObjectID == 1332 || LevelEditor::lastSelectedObj->m_nObjectID == 67 //bumps
                || LevelEditor::lastSelectedObj->m_nObjectID == 1934 //song trigger
                )
                str = "(No features)";
            if (LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeShipPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeCubePortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeBallPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeUfoPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeWavePortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeRobotPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeSpiderPortal) //noground portals
                {str = ">:3"; fntFile = "gjFont07.fnt";}
            if (LevelEditor::lastSelectedObj->m_nObjectID == 1913)
                str = "Scale: ";
        }
        if (std::string(str) == "Randomize Start") {
            if (LevelEditor::lastSelectedObj->m_nObjectID == 3004 || LevelEditor::lastSelectedObj->m_nObjectID == 3005 //spider orb anda pad
                || LevelEditor::lastSelectedObj->m_nObjectID == 35 || LevelEditor::lastSelectedObj->m_nObjectID == 140 || LevelEditor::lastSelectedObj->m_nObjectID == 1332 || LevelEditor::lastSelectedObj->m_nObjectID == 67 || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeInverseGravityPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeNormalGravityPortal
                || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeShipPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeCubePortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeBallPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeUfoPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeWavePortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeRobotPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeSpiderPortal //noground portals
                ) str = "Allow multi activate";
            if (LevelEditor::lastSelectedObj->m_nObjectID == 1913)
                str = "Take Scale for\n duration also :p";
            if (LevelEditor::lastSelectedObj->m_nObjectID == 1934)
                str = "Restart music";
            return CCLabelBMFont::create(str, fntFile, 220, kCCTextAlignmentCenter);
        }
        if (std::string(str) == "Animation settings help" && std::string(fntFile) == "chatFont.fnt") {
            CCLabelBMFont* lbl = CCLabelBMFont::create("", "chatFont.fnt", 435, kCCTextAlignmentCenter);
            std::string info = "";
            if (LevelEditor::lastSelectedObj->m_nObjectID == 3004 || LevelEditor::lastSelectedObj->m_nObjectID == 3005)
                info = "Allows multi activate feature.\nNote: set up first groundHeight(first 2 grounds gamemode) \nto reduce bugs with cube or robot";
            if (LevelEditor::lastSelectedObj->m_nObjectID == 35 || LevelEditor::lastSelectedObj->m_nObjectID == 140 || LevelEditor::lastSelectedObj->m_nObjectID == 1332 || LevelEditor::lastSelectedObj->m_nObjectID == 67)
                info = "Allows multi activate feature.";
            if (LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeShipPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeCubePortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeBallPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeUfoPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeWavePortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeRobotPortal || LevelEditor::lastSelectedObj->m_nObjectType == kGameObjectTypeSpiderPortal)
                info = "Allows multi activate feature.\nFree mode is buggy!";
            if (LevelEditor::lastSelectedObj->m_nObjectID == 1913)
                info = "No"; 
            if (LevelEditor::lastSelectedObj->m_nObjectID == 1934)
                info = "Can restart or stop music";
            lbl->setString(std::string("                      \n" + info + "\n\n\n ").c_str());
            if (info != "") return lbl;
        }
    }
    return CCLabelBMFont_create(str, fntFile);
}

struct CopyLeveltoClipboard
{   
    static CopyLeveltoClipboard* Init() {
        CopyLeveltoClipboard* pRet = new CopyLeveltoClipboard();
        if (pRet) {
            return pRet;
        }
        else {
            CC_SAFE_DELETE(pRet);
            return nullptr;
        }
    }
    bool TryIt(CCObject* pSender, GJGameLevel* pLevel) {
        if (GetKeyState(KEY_Control) & 0x8000) {
            ModUtils::copyToClipboard(pLevel->m_sLevelString.c_str());
            CCNode* pSenderNode = reinterpret_cast<CCNode*>(pSender);
            if (pSenderNode) {
                pSenderNode->removeChildByTag(521);
                CCLabelTTF* copyLvlStrLabel = CCLabelTTF::create("\n \nlevel string copied!", "arial", 6.0f);
                copyLvlStrLabel->setOpacity(90);
                copyLvlStrLabel->runAction(CCFadeTo::create(1.000f, 0));
                if (pSenderNode->getContentSize().width == CCDirector::sharedDirector()->getWinSize().width) {
                    copyLvlStrLabel = CCLabelTTF::create(copyLvlStrLabel->getString(), copyLvlStrLabel->getFontName(), 16.0f);
                    copyLvlStrLabel->setPosition(CCDirector::sharedDirector()->getWinSize() / 2);
                    copyLvlStrLabel->setOpacity(120);
                    copyLvlStrLabel->runAction(CCFadeTo::create(3.000f, 0));
                }
                pSenderNode->addChild(copyLvlStrLabel, 100, 521);
            }
            else {
                FLAlertLayer::create(nullptr, "Copy to Clipboard", "OK", nullptr, "level string copied!")->show();
            }
            return false;
        }
        else return true;
    }
};

PlayLayer* (__thiscall* PlayLayer_create)(GJGameLevel* pLevel);//0x1fb6d0
PlayLayer* __fastcall PlayLayer_create_H(GJGameLevel* pLevel) {
    PlayLayer* pOfPlayLayer_create = PlayLayer_create(pLevel);
    CopyLeveltoClipboard::Init()->TryIt(pOfPlayLayer_create, pLevel);
    return pOfPlayLayer_create;
}

inline void(__thiscall* LevelInfoLayer_onPlay)(LevelInfoLayer*, CCObject*);//0x179730
void __fastcall LevelInfoLayer_onPlay_H(LevelInfoLayer* self, void*, CCObject* pSender) {
    if (!CopyLeveltoClipboard::Init()->TryIt(pSender, self->m_pLevel)) return;
    LevelInfoLayer_onPlay(self, pSender);
}

#pragma comment (lib, "urlmon.lib")
#include <urlmon.h>
#include "SimpleIni.h"
void InitializeConfig() {
    std::filesystem::create_directories("Resources");
    //LevelAreaList
    CSimpleIni LevelAreaList;
    LevelAreaList.LoadFile("Resources/LevelAreaList.ini");
    const char* info = {
        "\n; --- levels config for the tower ---"
        "\n; --- EXAMPLE: ---"
        "\n; [1]"
        "\n; m_nLevelID = value"
        "\n; m_sLevelName = value"
        "\n; m_sCreatorName = value"
        "\n; m_nSongID = value"
        "\n; [2]"
        "\n; m_nLevelID = value"
        "\n; m_sLevelName = value"
        "\n; ..."
        "\n; [3]"
        "\n; ..."
        "\n; [4]"
        "\n; ..."
        "\n"
        "\n"
    };
    if (!(LevelAreaList.KeyExists("LevelAreaList", info))) LevelAreaList.SetValue("LevelAreaList", info, "= = = = = = = = =");
    if (!(LevelAreaList.KeyExists("LevelAreaList", "updateUrl"))) LevelAreaList.SetValue("LevelAreaList", "updateUrl", "url_to_text_file_on_server");
    LevelAreaList.SaveFile("Resources/LevelAreaList.ini");
}

DWORD WINAPI PROCESS_ATTACH(void* hModule) {

    // initialize minhook
    MH_Initialize();

    HOOK(base + 0x18C8E0, LoadingLayer_loadAssets, false);
    
    CC_HOOK("?create@CCSprite@cocos2d@@SAPAV12@PBD@Z", CCSprite_create, false);
    CC_HOOK("?createWithSpriteFrameName@CCSprite@cocos2d@@SAPAV12@PBD@Z", CCSprite_createWithSpriteFrameName, false);
    CC_HOOK("?create@CCLabelBMFont@cocos2d@@SAPAV12@PBD0@Z", CCLabelBMFont_create, false);

    //FakeLevelSelectLayerLol::makeHooks();
    CreatePlayLayerHooks(); printf("Created PlayLayer Hooks\n");
    CreatePlayerObjectHooks(); printf("Created PlayerObject Hooks\n");
    CreateObjectsThemedHooks(); printf("Created Objects Themed Hooks\n");
    CreateGameLayersHooks(); printf("Created GameLayers Hooks\n");
    CreateLevelEditorHooks(); printf("Created LevelEditor Hooks\n");
    HOOK(base + 0x1fb6d0, PlayLayer_create, false); printf("PlayLayer_create hook created\n");
    HOOK(base + 0x179730, LevelInfoLayer_onPlay, false); printf("LevelInfoLayer_onPlay hook created\n");
    hooksLoaded = true;
    printf("hooksLoaded\n");

    ModBase::bringBackSavedIcons();

    if ("hacks container lol") {
        //cant fuck dlux
        // Address	Length	Original bytes	Patched bytes
            /*100C5711	0x1	A1 	B8
            100C5716	0x1	05 	B8
            100C5718	0x2	55 18 	00 00*/

            // Level Completion
        ModUtils::write_bytes(base + 0x1FD557, { 0xEB, 0x0C, });
        ModUtils::write_bytes(base + 0x1FD742, { 0xC7, 0x87, 0xE0, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xC7, 0x87, 0xE4, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x1FD756, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x1FD79A, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x1FD7AF, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
        // Load Failed
        ModUtils::write_bytes(base + 0x18B2B4, { 0xB0 , 0x01 });
        //Rotation Hack
        ModUtils::write_bytes(base + 0x85CBC, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
        ModUtils::write_bytes(base + 0x8BDDD, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
        ModUtils::write_bytes(base + 0x8BE16, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
        ModUtils::write_bytes(base + 0xECA3D, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
        ModUtils::write_bytes(base + 0xEE5A9, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
        ModUtils::write_bytes(base + 0x20181E, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 });
        //DefaultSongBypass
        ModUtils::write_bytes(base + 0x174407, { 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x174411, { 0x90, 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x174456, { 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x174460, { 0x90, 0x90, 0x90 });
        //Allows you to scroll out the editor
        ModUtils::write_bytes(base + 0x8FAAC, { 0xEB });
        ModUtils::write_bytes(base + 0x8FA95, { 0xEB });
        ModUtils::write_bytes(base + 0x8FAC5, { 0xEB });
        ModUtils::write_bytes(base + 0x8FADC, { 0xEB });
        //ZoomInBypass
        ModUtils::write_bytes(base + 0x87801, { 0x90, 0x90, 0x90 });
        ModUtils::write_bytes(base + 0x87806, { 0x90, 0x90, 0x90 });
        //SmoothEditorTrail
        ModUtils::write_bytes(base + 0x16AB0D, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
        //Music Sync Correction
        ModUtils::write_bytes(base + 0x208808, { 0xEB, 0x08 });
    }

    LoadLibrary("cocos-explorer.dll");

    InitializeConfig();//and this

    return 0;
}

DWORD WINAPI KEY_HANDLE(void* hModule) {
    //yeah fucks keypress wait to open console
    while (true) {
        if (GetAsyncKeyState(VK_F4) & 0x8000) {
            AllocConsole();
            freopen("conin$", "r", stdin);
            freopen("conout$", "w", stdout);
            freopen("conout$", "w", stderr);
        }
    }
    return 0;
}

#include <errhandlingapi.h>
#include <dbghelp.h>
long __stdcall VectoredExceptionHandler(_EXCEPTION_POINTERS* pExceptInfo) {
    //save game?
    GameManager::sharedState()->save();
    //save log why no
    printf("game saved\n");
    //LevelEditorLayer* LevelEditorLayer_ = GameManager::sharedState()->getEditorLayer();
    //if (LevelEditorLayer_) {//level editor tries
    //    LevelEditorLayer_->getEditorUI()->undoLastAction(CCNode::create());
    //    LevelEditorLayer_->getEditorUI()->undoLastAction(CCNode::create());
    //    LevelEditorLayer_->getEditorUI()->undoLastAction(CCNode::create());
    //    printf("Was performed 3 undo actions in current level editor layer\n");
    //    EditorPauseLayer::create(LevelEditorLayer_)->saveLevel();
    //    printf("current level saved\n");
    //}
    //error msg
    DWORD exc_code = pExceptInfo->ExceptionRecord->ExceptionCode;
    bool dontfuckingcare = false;
    //msg text
    std::stringstream buffer;
    buffer << "Received fatal exception: ";
    switch (exc_code) {
    case EXCEPTION_ACCESS_VIOLATION:
        buffer << "EXCEPTION_ACCESS_VIOLATION";
        break;
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
        buffer << "EXCEPTION_ARRAY_BOUNDS_EXCEEDED";
        break;
    case EXCEPTION_BREAKPOINT:
        buffer << "EXCEPTION_BREAKPOINT";
        break;
    case EXCEPTION_DATATYPE_MISALIGNMENT:
        buffer << "EXCEPTION_DATATYPE_MISALIGNMENT";
        break;
    case EXCEPTION_FLT_DENORMAL_OPERAND:
        buffer << "EXCEPTION_FLT_DENORMAL_OPERAND";
        break;
    case EXCEPTION_FLT_DIVIDE_BY_ZERO:
        buffer << "EXCEPTION_FLT_DIVIDE_BY_ZERO";
        break;
    case EXCEPTION_FLT_INEXACT_RESULT:
        buffer << "EXCEPTION_FLT_INEXACT_RESULT";
        break;
    case EXCEPTION_FLT_INVALID_OPERATION:
        buffer << "EXCEPTION_FLT_INVALID_OPERATION";
        break;
    case EXCEPTION_FLT_OVERFLOW:
        buffer << "EXCEPTION_FLT_OVERFLOW";
        break;
    case EXCEPTION_FLT_STACK_CHECK:
        buffer << "EXCEPTION_FLT_STACK_CHECK";
        break;
    case EXCEPTION_FLT_UNDERFLOW:
        buffer << "EXCEPTION_FLT_UNDERFLOW";
        break;
    case EXCEPTION_ILLEGAL_INSTRUCTION:
        buffer << "EXCEPTION_ILLEGAL_INSTRUCTION";
        break;
    case EXCEPTION_IN_PAGE_ERROR:
        buffer << "EXCEPTION_IN_PAGE_ERROR";
        break;
    case EXCEPTION_INT_DIVIDE_BY_ZERO:
        buffer << "EXCEPTION_INT_DIVIDE_BY_ZERO";
        break;
    case EXCEPTION_INT_OVERFLOW:
        buffer << "EXCEPTION_INT_OVERFLOW";
        break;
    case EXCEPTION_INVALID_DISPOSITION:
        buffer << "EXCEPTION_INVALID_DISPOSITION";
        break;
    case EXCEPTION_NONCONTINUABLE_EXCEPTION:
        buffer << "EXCEPTION_NONCONTINUABLE_EXCEPTION";
        break;
    case EXCEPTION_PRIV_INSTRUCTION:
        buffer << "EXCEPTION_PRIV_INSTRUCTION";
        break;
    case EXCEPTION_SINGLE_STEP:
        buffer << "EXCEPTION_SINGLE_STEP";
        break;
    case EXCEPTION_STACK_OVERFLOW:
        buffer << "EXCEPTION_STACK_OVERFLOW";
        break;
    case DBG_PRINTEXCEPTION_WIDE_C:
        buffer << "DBG_PRINTEXCEPTION_WIDE_C";
        dontfuckingcare = true;
        break;
    case DBG_PRINTEXCEPTION_C:
        buffer << "DBG_PRINTEXCEPTION_C";
        dontfuckingcare = true;
        break;
    default:
        buffer << "0x" << std::hex << exc_code;
        break;
    }
    printf((buffer.str() + "\n").c_str());
    buffer << "\nCONTINUE EXECUTION?";
    //msg text makeup end
    if (dontfuckingcare) return EXCEPTION_CONTINUE_EXECUTION;
    auto MessageBox_ = MessageBoxA(nullptr, buffer.str().c_str(), __FUNCTION__, MB_ICONERROR | MB_RETRYCANCEL | MB_TOPMOST);
    return MessageBox_ == IDRETRY ? EXCEPTION_CONTINUE_EXECUTION : EXCEPTION_CONTINUE_SEARCH;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        AddVectoredExceptionHandler(1, VectoredExceptionHandler);
        CreateThread(0, 0, PROCESS_ATTACH, hModule, 0, 0);
        CreateThread(0, 0, KEY_HANDLE, hModule, 0, 0);
    }
    return TRUE;
}