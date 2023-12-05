#include "Gameplay.hpp"

inline void(__thiscall* updateProgressbar)(PlayLayerExt*);
void __fastcall updateProgressbar_H(PlayLayerExt* self) {
    updateProgressbar(self);
    PlayLayerExt::PlayLayerFromINit = (PlayLayerExt*)self;
    //shit
    if (PlayLayerExt::freeMode && self->isRunning() && !self->m_isDead) {
        if (!self->m_bIsDualMode) self->m_bIsDualMode = true;
        self->m_pPlayer2->m_position = CCPoint(-999999, self->m_pPlayer1->m_position.y + 5);
    }
    //fire
    if (self->m_isDead) {
        self->m_pPlayer1->removeChildByTag(5903);//fup
        self->m_pPlayer1->removeChildByTag(7638);//fmid
        self->m_pPlayer1->removeChildByTag(9562);//fdown
        self->m_pPlayer2->removeChildByTag(5903);//fup
        self->m_pPlayer2->removeChildByTag(7638);//fmid
        self->m_pPlayer2->removeChildByTag(9562);//fdown
    }
}
void PlayLayerExt::schFreeModeCameraShit(float) {
    stopActionByTag(52);
    if (freeMode) {
        stopActionByTag(11);
        CCAction* cameraytween = CCRepeatForever::create(CCActionTween::create(0.2f, "cTY", m_cameraY, m_pPlayer1->m_position.y - 140));
        cameraytween->setTag(52);
        /*cameraleadshit*/this->runAction(cameraytween);//CCMoveTo::create(0.2f, pointerser));
    }
    //oldway
    CCPoint pointerser = CCPoint(m_pPlayer1->m_position.x - 260, m_pPlayer1->m_position.y - 140);
    if (freeMode && 1 != 0) {
        cameraleadshit->stopAllActions();
        cameraleadshit->runAction(CCMoveTo::create(0.2f, pointerser));
    }
    else cameraleadshit->setPosition(pointerser);
}
void PlayLayerExt::schFreeModeCameraSync(float) {
    //shit
    if (freeMode && !m_isDead) {
        //m_cameraY = cameraleadshit->getPosition().y;//
        //m_cameraX = cameraleadshit->getPosition().x;//
    }
}
void PlayLayerExt::updateByGamePlayOptins(PlayLayer* self) {
    //sai mod pack settings
    GameManager::sharedState()->setGameVariable("showLvlInfo", GameManager::sharedState()->getGameVariable("0109"));//showLvlInfo 0109
    GameManager::sharedState()->setGameVariable("practiceMusic", GameManager::sharedState()->getGameVariable("0125"));//practiceMusic 0125
    GameManager::sharedState()->setGameVariable("hideAttempt", GameManager::sharedState()->getGameVariable("0135"));//hideAttempt 0135
    if (self->m_isPracticeMode && GameManager::sharedState()->getGameVariable("0134")) self->m_attemptLabel->setVisible(false);

    if (GameManager::sharedState()->getGameVariable("0136")) {
        //No Glow
        ModUtils::write_bytes(base + 0xCFF35, { 0x90 , 0x90 });
        ModUtils::write_bytes(base + 0xF02A4, { 0xe9 , 0xc0, 0x00, 0x00, 0x00, 0x90 });
        ModUtils::write_bytes(base + 0xF0434, { 0xe9 , 0xc0, 0x00, 0x00, 0x00, 0x90 });
    }
    else {
        //return Glow
        ModUtils::write_bytes(base + 0xCFF35, { 0x74 , 0x0D });
        ModUtils::write_bytes(base + 0xF02A4, { 0x0F , 0x84 , 0xBF , 0x00 , 0x00 , 0x00 });
        ModUtils::write_bytes(base + 0xF0434, { 0x0F , 0x84 , 0xBF , 0x00 , 0x00 , 0x00 });
    }
}
void PlayLayerExt::schNoResstartFix(float) {
    if (!PlayLayerFromINit) return;
    if (PlayLayerFromINit->m_isDead && !PlayLayerFromINit->m_bIsPaused && !PlayLayerFromINit->m_hasCompletedLevel) {
        PlayLayerFromINit->resetLevel();
    }
}
bool(__thiscall* PlayLayer_init)(PlayLayerExt*, GJGameLevel*);
bool __fastcall PlayLayer_init_H(PlayLayerExt* self, int edx, GJGameLevel* level) {
    if (!PlayLayer_init(self, level)) return false;
    PlayLayerExt::PlayLayerFromINit = (PlayLayerExt*)self;
    self->cameraleadshit = CCNode::create();
    self->addChild(self->cameraleadshit);
    self->schedule(schedule_selector(PlayLayerExt::schFreeModeCameraSync), 0.0f);
    self->schedule(schedule_selector(PlayLayerExt::schFreeModeCameraShit), 0.1f);
    auto gm = gd::GameManager::sharedState();
    //smoothFix
    if (gm->getGameVariable("0023") == true) {
        gm->setGameVariable("0023", false);
        self->onQuit();
        AchievementNotifier::sharedState()->notifyAchievement("Do not enable Smooth Fix!", "just dont pls", "exMark_001.png", true);
        GameSoundManager::sharedState()->playEffect("door001.ogg");
    }
    PlayLayerExt::updateByGamePlayOptins(self);

    ModBase::bringBackSavedIcons();
    
    PlayLayerExt::freeMode = false;
    return true;
}

inline void(__thiscall* PlayLayer_resetLevel)(PlayLayer*);
void __fastcall PlayLayer_resetLevel_H(PlayLayer* self) {
    self->stopActionByTag(52);
    self->m_cameraY = 10.000f;
    self->m_cameraYLocked = 0;
    PlayLayer_resetLevel(self);
    PlayLayerExt::updateByGamePlayOptins(self);
    if (PlayLayerExt::isSwingCopterMode && !self->m_isPracticeMode || !self->m_pPlayer1->m_isShip) {
        ModBase::bringBackSavedIcons();
        PlayLayerExt::isSwingCopterMode = false;
    }
    if(PlayLayerExt::freeMode) self->m_bIsDualMode = false;
    PlayLayerExt::freeMode = false;
    self->m_pObjectLayer->setScale(1.0);
    self->m_bottomGround->setScale(1.0);
    self->m_topGround->setScaleX(1.0);
    self->unschedule(schedule_selector(PlayLayerExt::schNoResstartFix));
}

inline void (__thiscall* PlayLayer_destroyPlayer)(PlayLayer*, PlayerObject*, GameObject*);//0x20a1a0
void __fastcall PlayLayer_destroyPlayer_H(PlayLayer* self, void*, PlayerObject* plrobj, GameObject* obj) {
    if (PlayLayerExt::freeMode && plrobj == self->m_pPlayer2) return;
    PlayLayer_destroyPlayer(self, plrobj, obj);
    if (self->m_isDead) {
        self->scheduleOnce(schedule_selector(PlayLayerExt::schNoResstartFix), 1.2f);
    }
}

inline void(__thiscall* PlayLayer_levelComplete)(PlayLayer*);
void __fastcall PlayLayer_levelComplete_H(PlayLayer* self) {
    PlayLayer_levelComplete(self);
    GJGameLevel* level = self->m_level;
    if (level->m_nLevelID == 1070) {
        GameManager::sharedState()->setUGV("LevelAreaInnerLayer_level1", true);
        if (GameManager::sharedState()->getUGV("LevelAreaInnerLayer_level1")) { AchievementNotifier::sharedState()->notifyAchievement("Completed #1", "You completed level of The Tower.", "GJ_completesIcon_001.png", true); }
    }
    if (level->m_nLevelID == 2049) {
        GameManager::sharedState()->setUGV("LevelAreaInnerLayer_level2", true);
        if (GameManager::sharedState()->getUGV("LevelAreaInnerLayer_level2")) { AchievementNotifier::sharedState()->notifyAchievement("Completed #2", "You completed level of The Tower.", "GJ_completesIcon_001.png", true); }
    }
    if (level->m_nLevelID == 632) {
        GameManager::sharedState()->setUGV("LevelAreaInnerLayer_level3", true);
        if (GameManager::sharedState()->getUGV("LevelAreaInnerLayer_level3")) { AchievementNotifier::sharedState()->notifyAchievement("Completed #3", "You completed level of The Tower.", "GJ_completesIcon_001.png", true); }
    }
    if (level->m_nLevelID == 21) {
        GameManager::sharedState()->setUGV("LevelAreaInnerLayer_level4", true);
        if (GameManager::sharedState()->getUGV("LevelAreaInnerLayer_level4")) { AchievementNotifier::sharedState()->notifyAchievement("Completed #4", "You completed level of The Tower.", "GJ_completesIcon_001.png", true); }
    }
}

inline void(__thiscall* PlayLayer_onQuit)(PlayLayer*);
void __fastcall PlayLayer_onQuit_H(PlayLayer* self) {
    PlayLayer_onQuit(self);
    PlayLayerExt::updateByGamePlayOptins(self);
    if (PlayLayerExt::isSwingCopterMode) {
        GameManager::sharedState()->setPlayerShip(GameManager::sharedState()->getIntGameVariable("oldShipIcon"));//bring up by oldShipIcon
    }
    PlayLayerExt::isSwingCopterMode = false;
    PlayLayerExt::freeMode = false;
}

void CreatePlayLayerHooks() {
    HOOK(base + 0x1FB780, PlayLayer_init, true);
    HOOK(base + 0x20BF00, PlayLayer_resetLevel, true);
    HOOK(base + 0x20a1a0, PlayLayer_destroyPlayer, true);
    HOOK(base + 0x1FD3D0, PlayLayer_levelComplete, true);
    HOOK(base + 0x20D810, PlayLayer_onQuit, true);
}

inline void(__thiscall* PlayerObject_ringJump)(PlayerObject*, GameObject*);
void __fastcall PlayerObject_ringJump_H(gd::PlayerObject* self, int, gd::GameObject* ring) {
    PlayerObject_ringJump(self, ring);
    if (ring->m_nObjectID == 3004 && ring->m_bHasBeenActivated) {
        self->spiderTestJump(true);
        if (ring->m_bRandomisedAnimStart) ring->m_bHasBeenActivated = false;
        if (ring->m_bRandomisedAnimStart) ring->m_bHasBeenActivatedP2 = false;
    }
    //green portale
    if (ring->m_nObjectID == 2926) {
        if (!ring->m_bHasBeenActivated) {
            if (self->m_isInPlayLayer) PlayLayerExt::PlayLayerFromINit->playGravityEffect(!self->m_isUpsideDown);
            self->flipGravity(!self->m_isUpsideDown, true);
        }
        if (!ring->m_bRandomisedAnimStart) 
            ring->m_bHasBeenActivated = true;
    }
}

inline void(__thiscall* bumpPlayer)(GJBaseGameLayer*, PlayerObject*, GameObject*);
void __fastcall bumpPlayer_H(GJBaseGameLayer* self, int, gd::PlayerObject* Player, gd::GameObject* bumper) {
    bumpPlayer(self, Player, bumper);
    if (bumper->m_nObjectID == 3005) {
        Player->spiderTestJump(true);
        if (bumper->m_bRandomisedAnimStart) bumper->m_bHasBeenActivated = false;
        if (bumper->m_bRandomisedAnimStart) bumper->m_bHasBeenActivatedP2 = false;
    }
    if (bumper->m_bRandomisedAnimStart && bool(bumper->m_nObjectID == 3005 || bumper->m_nObjectID == 35 || bumper->m_nObjectID == 140 || bumper->m_nObjectID == 1332 || bumper->m_nObjectID == 67)) {
        bumper->m_bHasBeenActivated = false;
        bumper->m_bHasBeenActivatedP2 = false;
    }
}
//animationsUpdate
std::string lastRoboAnim;
void animationsUpdate(gd::PlayerObject* __this) {
    if (!__this) return;
    float playerSpeed = MEMBERBYOFFSET(float, __this, 0x648);
    if (__this->m_isRobot && __this->m_isOnGround) {
        std::string animName = "run";
        if (fabs(playerSpeed) > 1.29f) animName = "run2";
        if (fabs(playerSpeed) > 1.59f) animName = "run3";
        if (lastRoboAnim != animName)__this->RobotSprite->runAnimation(animName);
        lastRoboAnim = animName;
    }
    else lastRoboAnim = "";
    if (__this->m_isSpider && __this->m_isOnGround) {
        if (fabs(playerSpeed) > 1.59f) __this->SpiderSprite->runAnimation("run2");
        else __this->playDynamicSpiderRun();
    }
}

void updateToSwing(gd::PlayerObject* __this) {
    //swing_01_001.png
    //self->m_pPlayer1->unk50C->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ship_82_001.png"));
    //self->m_pPlayer1->unk50C->setOpacity(90);
    //squarebase using cube and ball
    //cocos2d::CCSprite* unk4E8;-squarebase1
    //cocos2d::CCSprite* unk4EC;-squarebase2
    //cocos2d::CCSprite* unk4F0;-squarebaseExtra
    //cocos2d::CCSprite* unk4F4;-squarebaseGlow
    //vehicle using ship and bird
    //cocos2d::CCSprite* unk4F8;-vehicle1
    //cocos2d::CCSprite* unk4FC;-vehicle2
    //cocos2d::CCSprite* unk500;-bird3
    //cocos2d::CCSprite* unk504;-vehicleExtra
    //cocos2d::CCSprite* unk508;-vehicleGlow

    if (!PlayLayerExt::isSwingCopterMode) {
        if (__this->unk4FC) __this->unk4FC->setAnchorPoint({ 0.500f, 0.500f });
        if (__this->unk504) __this->unk504->setAnchorPoint({ 0.500f, 0.500f });
        return;
    };

    int currentSwing = GameManager::sharedState()->getIntGameVariable("6969");
    currentSwing = currentSwing == 0 ? 1 : currentSwing;
    std::string strnum = ((std::stringstream() << std::setw(2) << std::setfill('0') << currentSwing).str());
    //setframe
    CCSpriteFrame* pt1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(("swing_" + strnum + "_001.png").c_str());
    if (pt1) __this->unk4F8->setDisplayFrame(pt1); else __this->unk4F8->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("edit_eeNoneBtn_001.png"));
    CCSpriteFrame* pt2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(("swing_" + strnum + "_2_001.png").c_str());
    if (pt2) __this->unk4FC->setDisplayFrame(pt2); else __this->unk4F8->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("edit_eeNoneBtn_001.png"));
    CCSpriteFrame* pt3 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(("swing_" + strnum + "_extra_001.png").c_str());
    if (pt3) __this->unk504->setDisplayFrame(pt3); __this->unk504->setVisible(pt3);
    CCSpriteFrame* pt4 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(("swing_" + strnum + "_glow_001.png").c_str());
    if (pt4) __this->unk508->setDisplayFrame(pt4); else __this->unk4F8->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("edit_eeNoneBtn_001.png"));
    //set pos
    __this->unk4F8->setPosition({
        __this->unk4F8->displayFrame()->getOriginalSize().width / __this->unk4F8->getContentSize().width,
        __this->unk4F8->displayFrame()->getOriginalSize().height / __this->unk4F8->getContentSize().height,
        });
    __this->unk4FC->setPosition(__this->unk4F8->getContentSize() / 2);// ({ 16.600f, 16.200f });
    __this->unk504->setPosition(__this->unk4F8->getContentSize() / 2);// ({ 16.800f, 16.200f });
    __this->unk508->setPosition({
        __this->unk508->displayFrame()->getOriginalSize().width / __this->unk508->getContentSize().width,
        __this->unk508->displayFrame()->getOriginalSize().height / __this->unk508->getContentSize().height,
        });
}
void updateSwingFire(gd::PlayerObject* __this) {
        CCSprite* UpperFireThing = ModUtils::createSprite("fireBoost_001.png");
        CCSprite* FireThing = ModUtils::createSprite("fireBoost_001.png");
        CCSprite* DownFireThing = ModUtils::createSprite("fireBoost_001.png");
        //UpperFireThing
        if (!__this->getChildByTag(5903)) {
            UpperFireThing->setAnchorPoint({ 0.500f, 1.000f });
            UpperFireThing->setPosition({ -9.340f, 12.000f });
            UpperFireThing->setRotation(134.000f);
            __this->addChild(UpperFireThing, -1, 5903);
        }
        //update UpperFireThing
        if (__this->getChildByTag(5903)) {
            float a1 = 0.7f;
            CCAction* fireHere = CCRepeatForever::create(
                CCSequence::create(//really grabed from PlayerFireBoostSprite::loopFireAnimation(float *a1) 
                CCScaleTo::create(0.06f, a1 * 1.2, a1),
                CCScaleTo::create(0.06f, a1 * 0.6, a1 * 1.5),
                nullptr)
            );
            fireHere->setTag(69);
            CCAction* noFire = CCRepeatForever::create(CCScaleTo::create(0.2f, 0.0f, 0.0f));
            noFire->setTag(32);
            if (__this->m_isUpsideDown) {
                if (__this->getChildByTag(5903)->getActionByTag(69)) __this->getChildByTag(5903)->stopAllActions();
                if (!__this->getChildByTag(5903)->getActionByTag(32)) __this->getChildByTag(5903)->runAction(noFire);
            }
            else {
                if (__this->getChildByTag(5903)->getActionByTag(32)) __this->getChildByTag(5903)->stopAllActions();
                if (!__this->getChildByTag(5903)->getActionByTag(69)) __this->getChildByTag(5903)->runAction(fireHere);
            }
        }
        //FireThing middle one
        if (!__this->getChildByTag(7638)) {
            FireThing->setAnchorPoint({ 0.500f, 1.000f });
            FireThing->setPosition({ -14.000f, 1.000f });
            FireThing->setRotation(90.000f);//1.2f
            float a1 = 0.9f;
            FireThing->runAction(CCRepeatForever::create(CCSequence::create(//really grabed from PlayerFireBoostSprite::loopFireAnimation(float *a1) 
                CCScaleTo::create(0.06f, a1 * 1.2, a1),
                CCScaleTo::create(0.06f, a1 * 0.6, a1 * 1.5),
                nullptr)));
            __this->addChild(FireThing, -1, 7638);
        }
        //DownFireThing
        if (!__this->getChildByTag(9562)) {
            DownFireThing->setAnchorPoint({ 0.500f, 1.000f });
            DownFireThing->setPosition({ -9.340f, -10.140f });
            DownFireThing->setRotation(42.000f);
            __this->addChild(DownFireThing, -1, 9562);
        }
        //update DownFireThing
        if (__this->getChildByTag(9562)) {
            float a1 = 0.75f;
            CCAction* fireHere = CCRepeatForever::create(
                CCSequence::create(//really grabed from PlayerFireBoostSprite::loopFireAnimation(float *a1) 
                    CCScaleTo::create(0.06f, a1 * 1.2, a1),
                    CCScaleTo::create(0.06f, a1 * 0.6, a1 * 1.5),
                    nullptr)
            ); 
            fireHere->setTag(69);
            CCAction* noFire = CCRepeatForever::create(CCScaleTo::create(0.2f, 0.0f, 0.0f));
            noFire->setTag(32);
            if (__this->m_isUpsideDown) {
                if (__this->getChildByTag(9562)->getActionByTag(32)) __this->getChildByTag(9562)->stopAllActions();
                if (!__this->getChildByTag(9562)->getActionByTag(69)) __this->getChildByTag(9562)->runAction(fireHere);
            }
            else {
                if (__this->getChildByTag(9562)->getActionByTag(69)) __this->getChildByTag(9562)->stopAllActions();
                if (!__this->getChildByTag(9562)->getActionByTag(32)) __this->getChildByTag(9562)->runAction(noFire);
            }
        }
}
static inline void update_swing_copter(gd::PlayerObject* __this, const float delta) {
    if (!__this) return;
    __this->setScaleY((fabs(__this->getScaleY())));
    __this->deactivateParticle();
    __this->m_gravity = 0.8;
    updateSwingFire(__this);

    const auto _direction = __this->m_isUpsideDown ? -1.f : 1.f;
    const auto _size = (__this->m_vehicleSize != true) ? .85f : 1.f;
    const auto _gravity = (std::fabs(__this->m_yAccel) > 6.) ? __this->m_gravity + 1. : __this->m_gravity;

    const auto modifier = -.5 * _gravity * delta * _direction / _size;
    const auto y_acceleration = __this->m_yAccel + modifier;

    if (std::fabs(__this->m_yAccel) <= 6. || std::fabs(y_acceleration) <= std::fabs(__this->m_yAccel))
        __this->m_yAccel = y_acceleration;

    if (__this->m_isHolding && __this->m_hasJustHeld) {
        __this->m_hasJustHeld = false;
        __this->m_isHolding = false;
        __this->flipGravity(!__this->m_isUpsideDown, true);
    }
}
void(__thiscall* updateJump) (gd::PlayerObject* __this, float delta);
void  __fastcall  updateJump_H(gd::PlayerObject* __this, void*) {
    auto delta = 0.f;
    __asm movss[delta], xmm1;
    animationsUpdate(__this);
    //sWin copter
    __this->m_vehicleGroundParticles->setVisible(PlayLayerExt::isSwingCopterMode ? false : true);
    if (!PlayLayerExt::isSwingCopterMode) {
        if (__this->m_gravity == 0.8) __this->m_gravity = 0.958199;
    }
    //fire
    if (!PlayLayerExt::isSwingCopterMode) {
        __this->removeChildByTag(5903);
        __this->removeChildByTag(7638);
        __this->removeChildByTag(9562);
    }

    //ORIGINAL OR SWING UPDATE
    PlayLayerExt::isSwingCopterMode ? update_swing_copter(__this, delta) : updateJump(__this, delta);

    updateToSwing(__this);
}

void CreatePlayerObjectHooks() {
    HOOK(base + 0x208020, updateProgressbar, false);
    HOOK(base + 0x1E8F80, updateJump, true);
    HOOK(base + 0x1f4ff0, PlayerObject_ringJump, true);
    HOOK(base + 0x10ed50, bumpPlayer, true);
}