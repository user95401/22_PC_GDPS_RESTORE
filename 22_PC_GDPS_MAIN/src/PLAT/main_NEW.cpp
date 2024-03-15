#include "ModUtils.hpp"
#include "HooksUtils.hpp"
#include "SimpleIni.h"
using namespace std;
using namespace gd;
using namespace cocos2d;
using namespace cocos2d::extension;

float deltaTime;

bool dispatchKeyboardIsAlive;
bool KEY_A_IS_PRESSED;
bool KEY_D_IS_PRESSED;
bool KEY_Left_IS_PRESSED;
bool KEY_Right_IS_PRESSED;
bool KEY_F3_IS_PRESSED;
int lastKey1;
int lastKey2;

CCLabelTTF* dbg;

CSimpleIni cfg;

namespace PlatformerMod {
    bool enableMe;// >:3
    GJBaseGameLayer* gameLayer;
    float oldSpeed1;
    float oldSpeed2;
    double smoothingThing1;
    double moveSmoothingThing1;
    double smoothingThing2;
    double moveSmoothingThing2;
    double camXoffset;
    bool wasPlayedJumpAnim = false;// >:3
    bool laterally = false;// >:3
    bool dontmoovepls = false;// :T
    bool setSpeedHardly = false;// :T
    CCNode* getCamOffset() {
        return gameLayer->getChildByTag(518);
    }
    CCNode* getSpeedContainer1() {
        return gameLayer->getChildByTag(651);
    }
    CCNode* getSpeedContainer2() {
        return gameLayer->getChildByTag(512);
    }
    bool isIdleSpeed1(double incr = 0.0) {
        return fabs(gameLayer->m_pPlayer1->m_playerSpeed) <= (0.1f + incr);
    }
    bool isIdleSpeed2(double incr = 0.0) {
        return fabs(gameLayer->m_pPlayer2->m_playerSpeed) <= (0.1f + incr);
    }
    bool isForwardSpeed1(double incr = 0.0) {
        return gameLayer->m_pPlayer1->m_playerSpeed > (0.f + incr);
    }
    bool isForwardSpeed2(double incr = 0.0) {
        return gameLayer->m_pPlayer2->m_playerSpeed > (0.f + incr);
    }
    bool isBackwardSpeed1(double incr = 0.0) {
        return gameLayer->m_pPlayer1->m_playerSpeed < (0.f - incr);
    }
    bool isBackwardSpeed2(double incr = 0.0) {
        return gameLayer->m_pPlayer2->m_playerSpeed < (0.f - incr);
    }
    void updateSpeed() {
        if (KEY_A_IS_PRESSED) {
            lastKey1 = KEY_A;
            float spped = -fabs(oldSpeed1);
            if (setSpeedHardly) getSpeedContainer1()->setScale(spped);
            else if (!getSpeedContainer1()->getActionByTag(622)) {
                auto asd = CCEaseSineIn::create(CCScaleTo::create(fabs(oldSpeed1 / 10 * 2), spped));
                asd->setTag(622);
                getSpeedContainer1()->runAction(asd);
            };
        }
        if (KEY_D_IS_PRESSED) {
            lastKey1 = KEY_D;
            float spped = fabs(oldSpeed1);
            if (setSpeedHardly) getSpeedContainer1()->setScale(spped);
            else if (!getSpeedContainer1()->getActionByTag(541)) {
                auto asd = CCEaseSineIn::create(CCScaleTo::create(fabs(oldSpeed1 / 10 * 2), spped));
                asd->setTag(541);
                getSpeedContainer1()->runAction(asd);
            };
        }
        if (KEY_Left_IS_PRESSED) {
            lastKey2 = KEY_Left;
            float spped = -fabs(oldSpeed2);
            if (setSpeedHardly) getSpeedContainer2()->setScale(spped);
            else if (!getSpeedContainer2()->getActionByTag(622)) {
                auto asd = CCEaseSineIn::create(CCScaleTo::create(fabs(oldSpeed2 / 10 * 2), spped));
                asd->setTag(622);
                getSpeedContainer2()->runAction(asd);
            };
        }
        if (KEY_Right_IS_PRESSED) {
            lastKey2 = KEY_Right;
            float spped = fabs(oldSpeed2);
            if (setSpeedHardly) getSpeedContainer2()->setScale(spped);
            else if (!getSpeedContainer2()->getActionByTag(541)) {
                auto asd = CCEaseSineIn::create(CCScaleTo::create(fabs(oldSpeed2 / 10 * 2), spped));
                asd->setTag(541);
                getSpeedContainer2()->runAction(asd);
            };
        } 
        //idle
        if (!KEY_A_IS_PRESSED && !KEY_D_IS_PRESSED) {
            float spped = .0f;
            if (setSpeedHardly) getSpeedContainer1()->setScale(spped);
            else if (!getSpeedContainer1()->getActionByTag(451)) {
                auto asd = CCEaseSineInOut::create(CCScaleTo::create(0.2f, spped));
                asd->setTag(451);
                getSpeedContainer1()->stopActionByTag(622);
                getSpeedContainer1()->stopActionByTag(541);
                getSpeedContainer1()->runAction(asd);
            };
        }
        if (!KEY_Left_IS_PRESSED && !KEY_Right_IS_PRESSED) {
            float spped = .0f;
            if (setSpeedHardly) getSpeedContainer2()->setScale(spped);
            else if (!getSpeedContainer2()->getActionByTag(451)) {
                auto asd = CCEaseSineInOut::create(CCScaleTo::create(0.2f, spped));
                asd->setTag(451);
                getSpeedContainer2()->stopActionByTag(622);
                getSpeedContainer2()->stopActionByTag(541);
                getSpeedContainer2()->runAction(asd);
            };
        }
        gameLayer->m_pPlayer1->m_playerSpeed = getSpeedContainer1()->getScale();
        gameLayer->m_pPlayer2->m_playerSpeed = getSpeedContainer2()->getScale();
        getSpeedContainer1()->setScaleY(oldSpeed1);
        getSpeedContainer2()->setScaleY(oldSpeed2);
    }
    void updateRotation() {
        //stop Rotation
        if (isIdleSpeed1() && !gameLayer->m_pPlayer1->m_isDashing) {
            gameLayer->m_pPlayer1->stopRotation(false);
            if (gameLayer->m_pPlayer1->m_isShip) {
                if (fabs(gameLayer->m_pPlayer1->m_playerSpeed) > 0.01) {
                    auto rotAction1 = CCRotateTo::create(0.1, lastKey1 == KEY_A ? 180 : 0);
                    rotAction1->setTag(777);
                    if (!gameLayer->m_pPlayer1->getActionByTag(777)) gameLayer->m_pPlayer1->runAction(rotAction1);
                }
                else {
                    if (!gameLayer->m_pPlayer1->getActionByTag(777)) gameLayer->m_pPlayer1->setRotation(lastKey1 == KEY_A ? 180 : 0);
                }
            }
        }
        if (isIdleSpeed2() && !gameLayer->m_pPlayer2->m_isDashing) {
            gameLayer->m_pPlayer2->stopRotation(false);
            if (gameLayer->m_pPlayer2->m_isShip) {
                if (fabs(gameLayer->m_pPlayer2->m_playerSpeed) > 0.01) {
                    auto rotAction2 = CCRotateTo::create(0.1, lastKey2 == KEY_Left ? 180 : 0);
                    rotAction2->setTag(778);
                    if (!gameLayer->m_pPlayer2->getActionByTag(778)) gameLayer->m_pPlayer2->runAction(rotAction2);
                }
                else {
                    gameLayer->m_pPlayer2->setRotation(lastKey2 == KEY_Left ? 180 : 0);
                }
            }
        }
        //bird
        if (gameLayer->m_pPlayer1->m_isBird) 
            gameLayer->m_pPlayer1->setRotation(0);
        if (gameLayer->m_pPlayer2->m_isBird || (gameLayer->m_pPlayer2->isCube() && gameLayer->m_pPlayer2->m_isOnGround)) 
            gameLayer->m_pPlayer2->setRotation(0);
        //bot and spider in 3d 4k october
        if (gameLayer->m_pPlayer1->m_isRobot || gameLayer->m_pPlayer1->m_isSpider && gameLayer->m_pPlayer1->m_isOnGround) {
            auto rotAction = CCRotateTo::create(0.05, 0);
            rotAction->setTag(777);
            if (!gameLayer->m_pPlayer1->getActionByTag(777)) gameLayer->m_pPlayer1->runAction(rotAction);
        }
        if (gameLayer->m_pPlayer2->m_isRobot || gameLayer->m_pPlayer2->m_isSpider && gameLayer->m_pPlayer2->m_isOnGround) {
            auto rotAction = CCRotateTo::create(0.05, 0);
            rotAction->setTag(777);
            if (!gameLayer->m_pPlayer2->getActionByTag(777)) gameLayer->m_pPlayer2->runAction(rotAction);
        }
        //fucks cube
        if ((gameLayer->m_pPlayer1->isCube()) && gameLayer->m_pPlayer1->m_isOnGround) {
            float rot = gameLayer->m_pPlayer1->getRotation();
            float torot = 0;
            if (gameLayer->m_pPlayer1->getRotation() < 0) rot = fabs(rot);
            if (rot < 90 - 50) torot = 0;
            else if (rot < 180 - 50) torot = 90;
            else if (rot < 360 - 50) torot = 180;
            else if (rot < 420) torot = 360;
            else torot = 0;
            if (gameLayer->m_pPlayer1->getRotation() < 0) torot = -torot;
            auto rotAction = CCRotateTo::create(0.05, torot);
            rotAction->setTag(777);
            if(!gameLayer->m_pPlayer1->getActionByTag(777)) gameLayer->m_pPlayer1->runAction(rotAction);
        }
        if ((gameLayer->m_pPlayer2->isCube()) && gameLayer->m_pPlayer2->m_isOnGround) {
            float rot = gameLayer->m_pPlayer2->getRotation();
            float torot = 0;
            if (gameLayer->m_pPlayer2->getRotation() < 0) rot = fabs(rot);
            if (rot < 90 - 50) torot = 0;
            else if (rot < 180 - 50) { torot = 90; }
            else if (rot < 360 - 50) torot = 180;
            else if (rot < 420) torot = 360;
            else torot = 0;
            if (gameLayer->m_pPlayer2->getRotation() < 0) torot = -torot;
            auto rotAction = CCRotateTo::create(0.05, torot);
            rotAction->setTag(777);
            if (!gameLayer->m_pPlayer2->getActionByTag(777)) gameLayer->m_pPlayer2->runAction(rotAction);
        }
        //update laterally boolean
        float rot42 = fabs(gameLayer->m_pPlayer1->getRotation());
        if (bool(rot42 > 80 && rot42 < 100) || bool(rot42 > 260 && rot42 < 280)) laterally = true;
        else laterally = false;
    }
    void particlesUpdate() {
        //deactivateParticle
        if (isIdleSpeed1()) gameLayer->m_pPlayer1->deactivateParticle();
        gameLayer->m_pPlayer1->m_vehicleGroundParticles->setVisible(!isIdleSpeed1());
        if (isIdleSpeed2()) gameLayer->m_pPlayer2->deactivateParticle();
        gameLayer->m_pPlayer2->m_vehicleGroundParticles->setVisible(!isIdleSpeed2());
    }
    void scaleUpdate() {
        if (isBackwardSpeed1() && !gameLayer->m_pPlayer1->m_isDart) {
            if (!gameLayer->m_pPlayer1->m_isDart && !gameLayer->m_pPlayer1->m_isShip) gameLayer->m_pPlayer1->setScaleX(-fabs(gameLayer->m_pPlayer1->m_vehicleSize));
            //ship flipping
            if (gameLayer->m_pPlayer1->m_isShip && GameManager::sharedState()->getPlayerShip() != 170) {
                if (!gameLayer->m_pPlayer1->m_isUpsideDown) gameLayer->m_pPlayer1->setScaleY(-gameLayer->m_pPlayer1->m_vehicleSize);
                else gameLayer->m_pPlayer1->setScaleY(fabs(gameLayer->m_pPlayer1->m_vehicleSize));
            }
        }
        if (isBackwardSpeed2() && !gameLayer->m_pPlayer2->m_isDart) {
            if (!gameLayer->m_pPlayer2->m_isDart && !gameLayer->m_pPlayer2->m_isShip) gameLayer->m_pPlayer2->setScaleX(-fabs(gameLayer->m_pPlayer2->m_vehicleSize));
            //ship flipping
            if (gameLayer->m_pPlayer2->m_isShip && GameManager::sharedState()->getPlayerShip() != 170) {
                if (!gameLayer->m_pPlayer2->m_isUpsideDown) gameLayer->m_pPlayer2->setScaleY(-gameLayer->m_pPlayer2->m_vehicleSize);
                else gameLayer->m_pPlayer2->setScaleY(fabs(gameLayer->m_pPlayer2->m_vehicleSize));
            }
        }
        if (isForwardSpeed1()) {
            if (!gameLayer->m_pPlayer1->m_isDart && !gameLayer->m_pPlayer1->m_isShip) gameLayer->m_pPlayer1->setScaleX(fabs(gameLayer->m_pPlayer1->m_vehicleSize));
            //ship flipping
            if (gameLayer->m_pPlayer1->m_isShip && GameManager::sharedState()->getPlayerShip() != 170) {
                if (!gameLayer->m_pPlayer1->m_isUpsideDown) gameLayer->m_pPlayer1->setScaleY(fabs(gameLayer->m_pPlayer1->m_vehicleSize));
                else gameLayer->m_pPlayer1->setScaleY(-gameLayer->m_pPlayer1->m_vehicleSize);
            }
        }
        if (isForwardSpeed2()) {
            if (!gameLayer->m_pPlayer2->m_isDart && !gameLayer->m_pPlayer2->m_isShip) gameLayer->m_pPlayer2->setScaleX(fabs(gameLayer->m_pPlayer2->m_vehicleSize));
            //ship flipping
            if (gameLayer->m_pPlayer2->m_isShip && GameManager::sharedState()->getPlayerShip() != 170) {
                if (!gameLayer->m_pPlayer2->m_isUpsideDown) gameLayer->m_pPlayer2->setScaleY(fabs(gameLayer->m_pPlayer2->m_vehicleSize));
                else gameLayer->m_pPlayer2->setScaleY(-gameLayer->m_pPlayer2->m_vehicleSize);
            }
        }
        //jumpscare cube
        if (!gameLayer->m_pPlayer1->playerIsFalling()) wasPlayedJumpAnim = false;
        if (!wasPlayedJumpAnim) {
            if (gameLayer->m_pPlayer1->m_isHolding && gameLayer->m_pPlayer1->isCube()) {
                wasPlayedJumpAnim = true;
                CCSequence* jumpAnimSeq = CCSequence::create(
                    gameLayer->m_pPlayer1->getScaleX() < 0.f //test for
                    ? //scale < 0
                    CCEaseSineInOut::create(CCScaleTo::create(0.1,
                        laterally ? gameLayer->m_pPlayer1->getScaleX() : gameLayer->m_pPlayer1->getScaleX() + 0.3f,
                        laterally ? gameLayer->m_pPlayer1->getScaleY() - 0.25f : gameLayer->m_pPlayer1->getScaleY()
                    ))
                    : //else
                    CCEaseSineInOut::create(CCScaleTo::create(0.1,
                        laterally ? gameLayer->m_pPlayer1->getScaleX() : gameLayer->m_pPlayer1->getScaleX() - 0.3f,
                        laterally ? gameLayer->m_pPlayer1->getScaleY() - 0.3f : gameLayer->m_pPlayer1->getScaleY()
                    )),
                    CCEaseSineInOut::create(CCScaleTo::create(0.2, gameLayer->m_pPlayer1->getScaleX(), gameLayer->m_pPlayer1->getScaleY())),
                    nullptr
                );
                jumpAnimSeq->setTag(684093);
                if(!gameLayer->m_pPlayer1->getActionByTag(684093)) gameLayer->m_pPlayer1->runAction(jumpAnimSeq);
            }
        }
    }
    std::string lastAnim1;
    std::string lastAnim2;
    void runAnim1(std::string name) {
        lastAnim1 = name;
        //RobotSprite
        gameLayer->m_pPlayer1->RobotSprite->runAnimation(lastAnim1);
        //SpiderSprite
        if (lastAnim1 == cfg.GetValue("gdPlatformerMode", "idleAnimationName")) gameLayer->m_pPlayer1->SpiderSprite->runAnimation(lastAnim1);
        if (lastAnim1 == "run") gameLayer->m_pPlayer1->playDynamicSpiderRun();
    }
    void runAnim2(std::string name) {
        lastAnim2 = name;
        //RobotSprite
        gameLayer->m_pPlayer2->RobotSprite->runAnimation(lastAnim2);
        //SpiderSprite
        if (lastAnim2 == cfg.GetValue("gdPlatformerMode", "idleAnimationName")) gameLayer->m_pPlayer2->SpiderSprite->runAnimation(lastAnim2);
        if (lastAnim2 == "run") gameLayer->m_pPlayer2->playDynamicSpiderRun();
    }
    void animationsUpdate() {
        if (isIdleSpeed1() && gameLayer->m_pPlayer1->m_isOnGround) runAnim1(cfg.GetValue("gdPlatformerMode", "idleAnimationName"));
        else if (lastAnim1 != "run") runAnim1("run");
        if (isIdleSpeed2() && gameLayer->m_pPlayer2->m_isOnGround) runAnim2(cfg.GetValue("gdPlatformerMode", "idleAnimationName"));
        else if (lastAnim2 != "run") runAnim2("run");
    }
    void camXoffsetUpdate() {
        if (isBackwardSpeed1(oldSpeed1 - 0.1)) {
            if (!getCamOffset()->getActionByTag(622)) {
                float offset = -180.0f;
                //CCEaseSineOut
                auto asd = CCEaseSineInOut::create(CCMoveTo::create(1.0f, CCPoint(offset, .0f)));
                asd->setTag(622);
                if (getCamOffset()->getPositionX() != offset) getCamOffset()->runAction(asd);
            };
        }
        else if (isForwardSpeed1(oldSpeed1 - 0.1)) {
            if (!getCamOffset()->getActionByTag(642)) {
                float offset = 0.0f;
                //CCEaseSineInOut
                auto asd = CCEaseSineInOut::create(CCMoveTo::create(1.0f, CCPoint(0.0f, .0f)));
                asd->setTag(642);
                if (getCamOffset()->getPositionX() != offset) getCamOffset()->runAction(asd);
            };
        }
        else {
            getCamOffset()->stopAllActions();
            /*if (!getCamOffset()->getActionByTag(142)) {
                CCEaseSineInOut* asd = CCEaseSineInOut::create(CCMoveTo::create(0.8f, CCPoint(getCamOffset()->getPositionX(), .0f)));
                asd->setTag(142);
                if (getCamOffset()->getPositionX() != -90.0f) getCamOffset()->runAction(asd);
            };*/
        }
    }
    void ruin(GJBaseGameLayer* gameLayerArg) {
        gameLayer = gameLayerArg;

        PlatformerMod::enableMe = 
            gameLayer->m_levelSettings->m_level->m_nLevelLength == 5 
            or 
            gameLayer->m_levelSettings->m_level->m_sRecordString == "plat"
        ;
        if (cfg.GetBoolValue("gdPlatformerMode", "forcePlatformer")) enableMe = true;

        //oldSpeed1
        if (
            fabs(gameLayer->m_pPlayer1->m_playerSpeed) == 0.7f 
            or fabs(gameLayer->m_pPlayer1->m_playerSpeed) == 0.9f
            or fabs(gameLayer->m_pPlayer1->m_playerSpeed) == 1.1f
            or fabs(gameLayer->m_pPlayer1->m_playerSpeed) == 1.3f
            or fabs(gameLayer->m_pPlayer1->m_playerSpeed) == 1.6f
            )
            oldSpeed1 = fabs(gameLayer->m_pPlayer1->m_playerSpeed);
        //oldSpeed2
        if (
            fabs(gameLayer->m_pPlayer2->m_playerSpeed) == 0.7f
            or fabs(gameLayer->m_pPlayer2->m_playerSpeed) == 0.9f
            or fabs(gameLayer->m_pPlayer2->m_playerSpeed) == 1.1f
            or fabs(gameLayer->m_pPlayer2->m_playerSpeed) == 1.3f
            or fabs(gameLayer->m_pPlayer2->m_playerSpeed) == 1.6f
            )
            oldSpeed2 = fabs(gameLayer->m_pPlayer2->m_playerSpeed);
        if (!gameLayerArg->getChildByTag(518)) gameLayerArg->addChild(CCNode::create(), 999, 518);
        if (!gameLayerArg->getChildByTag(651)) gameLayerArg->addChild(CCNode::create(), 999, 651);
        if (!gameLayerArg->getChildByTag(512)) gameLayerArg->addChild(CCNode::create(), 999, 512);

        cfg.LoadFile("config/gdPlatformerMode.ini");

        //patch crash on dashing backwards (by cos8o): 0xE9, 0xA7, 0x00 0x1EEB92 // org is 0x0f, 0x84, 0xa6
        if (enableMe) ModUtils::WriteProcMem(base + 0x1EEB92, { 0xE9, 0xA7, 0x00 });
        else ModUtils::WriteProcMem(base + 0x1EEB92, { 0x0f, 0x84, 0xa6 });

        //conditions
        if (!enableMe) return;

        if (cfg.GetBoolValue("gdPlatformerMode", "updateRotation")) updateRotation();
        if (cfg.GetBoolValue("gdPlatformerMode", "particlesUpdate")) particlesUpdate();
        if (cfg.GetBoolValue("gdPlatformerMode", "scaleUpdate")) scaleUpdate();
        if (cfg.GetBoolValue("gdPlatformerMode", "animationsUpdate")) animationsUpdate();
        if (cfg.GetBoolValue("gdPlatformerMode", "camXoffsetUpdate")) camXoffsetUpdate();

        //playlayer
        //if (gameLayer->m_pPlayer1->m_isInPlayLayer) {
        //    PlayLayer* playLayer = reinterpret_cast<PlayLayer*>(gameLayerArg);
        //    if (!playLayer->m_isDead && !playLayer->m_hasCompletedLevel && cfg.GetBoolValue("gdPlatformerMode", "camXoffsetUpdate")) {
        //        auto tarxpos = (playLayer->m_pPlayer1->m_position.x - 180.0) + getCamOffset()->getPositionX();
        //        playLayer->stopActionByTag(10);
        //        playLayer->runAction(CCActionTween::create(0.1f, "cTX", tarxpos, tarxpos));
        //        //playLayer->m_cameraXLocked = 1;
        //        //playLayer->m_cameraX = /*playLayer->m_cameraXLocked ? playLayer->m_cameraX :*/ (playLayer->m_pPlayer1->m_position.x - 180.0) + getCamOffset()->getPositionX();
        //    }
        //}

        //m_isDashing
        if (gameLayer->m_pPlayer1->m_isDashing || gameLayer->m_pPlayer2->m_isDashing) {
            gameLayer->m_pPlayer1->m_playerSpeed = oldSpeed1;
            gameLayer->m_pPlayer2->m_playerSpeed = oldSpeed2;
            return;
        }

        //m_isDashing
        if (dontmoovepls) return;

        updateSpeed();
        PlatformerMod::setSpeedHardly = false;
    }
};
inline void(__thiscall* updateVisibility)(PlayLayer*);
void __fastcall updateVisibility_H(PlayLayer* self) {
    updateVisibility(self); //self->m_pPlayer1->runBallRotation
    PlatformerMod::ruin(self);//sometimes return;

    //if (self->getChildByTag(59320)) dbg->setString( (   "dispatchKeyboardIsAlive: " + std::to_string(dispatchKeyboardIsAlive)     ).c_str());
}

inline bool(__thiscall* PlayLayer_init)(PlayLayer*, GJGameLevel*);
bool __fastcall PlayLayer_init_H(PlayLayer* self, void*, GJGameLevel* level) {
    if (!PlayLayer_init(self, level)) return false;
    PlatformerMod::enableMe = level->m_nLevelLength == 5 or level->m_sRecordString == "plat";
    if (!PlatformerMod::enableMe) return true;
    level->m_nLevelLength = 5;
    self->toggleDualMode(GameObject::createWithKey(12), bool(!self->m_bIsDualMode), self->m_pPlayer1, true);
    self->toggleDualMode(GameObject::createWithKey(12), bool(!self->m_bIsDualMode), self->m_pPlayer1, true);
    dbg = CCLabelTTF::create("", "Arial", 8.f);
    dbg->setHorizontalAlignment(CCTextAlignment::kCCTextAlignmentLeft);
    dbg->setAnchorPoint({ -0.01f, 0.01f });
    self->addChild(dbg, 100, 59320);
    return true;
}

inline bool(__thiscall* LevelEditorLayer_init)(LevelEditorLayer*, GJGameLevel*);
bool __fastcall LevelEditorLayer_init_H(LevelEditorLayer* self, int, GJGameLevel* level) {
    if (!LevelEditorLayer_init(self, level)) return false;
    PlatformerMod::enableMe = level->m_nLevelLength == 5 or level->m_sRecordString == "plat";
    if(!PlatformerMod::enableMe) return true;
    level->m_nLevelLength = 5;
    dbg = CCLabelTTF::create("", "Arial", 8.f);
    dbg->setHorizontalAlignment(CCTextAlignment::kCCTextAlignmentLeft);
    dbg->setAnchorPoint({ -0.01f, 0.01f });
    self->addChild(dbg, 100, 59320);
    return true;
}

LevelSettingsObject* g_levelSettings;
LevelEditorLayer* g_editor;
class LevelSettingsLayerExt : public FLAlertLayer {
public:
    void onToggle(CCObject*) {
        g_levelSettings->m_level->m_sRecordString = g_levelSettings->m_level->m_sRecordString == "plat" ? "" : "plat";
        g_levelSettings->m_level->m_nLevelLength = g_levelSettings->m_level->m_nLevelLength == 5 ? 0 : 5;
    }
};
inline bool(__thiscall* LevelSettingsLayer_init)(LevelSettingsLayerExt* self, LevelSettingsObject* levelSettings, LevelEditorLayer* editor);
bool __fastcall LevelSettingsLayer_init_H(LevelSettingsLayerExt* self, void*, LevelSettingsObject* levelSettings, LevelEditorLayer* editor) {
    if (!LevelSettingsLayer_init(self, levelSettings, editor) or !self) return false;
    g_levelSettings = levelSettings;
    g_editor = editor;
    auto toggle = CCMenuItemToggler::createWithStandardSprites(
        self,
        menu_selector(LevelSettingsLayerExt::onToggle),
        0.8f
    );
    toggle->setPosition({ -149.000f, -129.750f });
    toggle->toggle(levelSettings->m_level->m_nLevelLength == 5 or levelSettings->m_level->m_sRecordString == "plat");
    self->m_pButtonMenu->addChild(toggle, 20, 8056);
    return true;
}

inline void(__thiscall* LevelEditorLayer_update)(LevelEditorLayer*, float);
void __fastcall LevelEditorLayer_update_H(LevelEditorLayer* self, void*, float dt) {
    LevelEditorLayer_update(self, dt);
    deltaTime = dt;
    PlatformerMod::ruin(self);
}

inline void(__thiscall* GameObject_activateObject)(GameObject*, PlayerObject*);
void __fastcall GameObject_activateObject_H(GameObject* object, void*, PlayerObject* player) {
    GameObject_activateObject(object, player);
    bool AlwaysMultiActivate = (cfg.GetBoolValue("gdPlatformerMode", "AlwaysMultiActivate"));
    bool PlatMultiActivate = (cfg.GetBoolValue("gdPlatformerMode", "PlatMultiActivate")) and PlatformerMod::enableMe;
    if (AlwaysMultiActivate or PlatMultiActivate) {
        object->m_bHasBeenActivated = false;
        object->m_bHasBeenActivatedP2 = false;
    };
}

inline void(__thiscall* PlayerObject_ringJump)(PlayerObject*, GameObject*);
void __fastcall PlayerObject_ringJump_H(PlayerObject* self, void*, GameObject* object) {
    PlayerObject_ringJump(self, object);
    bool AlwaysMultiActivate = (cfg.GetBoolValue("gdPlatformerMode", "AlwaysMultiActivate"));
    bool PlatMultiActivate = (cfg.GetBoolValue("gdPlatformerMode", "PlatMultiActivate")) and PlatformerMod::enableMe;
    if (AlwaysMultiActivate or PlatMultiActivate) {
        object->m_bHasBeenActivated = false;
        object->m_bHasBeenActivatedP2 = false;
    };
}

inline void(__thiscall* GJBaseGameLayer_bumpPlayer)(GJBaseGameLayer*, PlayerObject*, GameObject*);
void __fastcall GJBaseGameLayer_bumpPlayer_H(GJBaseGameLayer* self, void*, PlayerObject* player, GameObject* object) {
    GJBaseGameLayer_bumpPlayer(self, player, object);
    bool AlwaysMultiActivate = (cfg.GetBoolValue("gdPlatformerMode", "AlwaysMultiActivate"));
    bool PlatMultiActivate = (cfg.GetBoolValue("gdPlatformerMode", "PlatMultiActivate")) and PlatformerMod::enableMe;
    if (AlwaysMultiActivate or PlatMultiActivate) {
        object->m_bHasBeenActivated = false;
        object->m_bHasBeenActivatedP2 = false;
    };
}

inline void(__thiscall* GameManager_update)(GameManager*, float);
void __fastcall GameManager_update_H(GameManager* self, void*, float dt) {
    GameManager_update(self, dt);
    deltaTime = dt;
    KEY_A_IS_PRESSED = (GetKeyState('A') & 0x8000);
    KEY_D_IS_PRESSED = (GetKeyState('D') & 0x8000);
    KEY_Left_IS_PRESSED = (GetKeyState(VK_LEFT) & 0x8000);
    KEY_Right_IS_PRESSED = (GetKeyState(VK_RIGHT) & 0x8000);
    if (PlatformerMod::enableMe) {
        //negative rot
        if ((KEY_A_IS_PRESSED || KEY_Left_IS_PRESSED)) {
            //patch by sai(founded by user666) 1E9CD8: org b4 00 00 00 // patch 4c ff ff ff
            ModUtils::WriteProcMem(base + 0x1E9CD8, { 0x4c, 0xff, 0xff, 0xff });//- rot
            //user666's patch: game + 1E9DED - C1 E0 06 // org: game + 1E9DED - C1 E0 06
            ModUtils::WriteProcMem(base + 0x1E9DED, { 0xC1, 0xE0, 0x06 });//-ball rot
        }
        if ((KEY_D_IS_PRESSED || KEY_Right_IS_PRESSED)) {
            ModUtils::WriteProcMem(base + 0x1E9CD8, { 0xb4, 0x00, 0x00, 0x00 });//normal rot
            ModUtils::WriteProcMem(base + 0x1E9DED, { 0xC1, 0xE0, 0x03 });//ball rot
        }
    }
    else if (!self->getEditorLayer() && !self->getPlayLayer() && !PlatformerMod::gameLayer) {
        ModUtils::WriteProcMem(base + 0x1E9CD8, { 0xb4, 0x00, 0x00, 0x00 });//normal rot
        ModUtils::WriteProcMem(base + 0x1E9DED, { 0xC1, 0xE0, 0x03 });//ball rot
    }
}

void markObj(CCNode* obj) {
    if (!obj->getActionByTag(51)) {
        CCSequence* asd = CCSequence::create(CCHide::create(), CCDelayTime::create(.1f), CCShow::create(), nullptr);
        asd->setTag(51);
        obj->runAction(asd);
    }
}
CCNode* getDot(GameObject* obj) {
    if (!obj->getParent()->getChildByTag(951)) {
        auto newDot = ModUtils::createSprite("d_link_b_01_color_001.png");
        obj->getParent()->addChild(newDot, 999, 951);
    }
    return obj->getParent()->getChildByTag(951);
}
inline bool(__thiscall* PlayerObject_collidedWithObject)(PlayerObject* self, GameObject* obj, int va, int vb, int vc, int vd);
bool __fastcall PlayerObject_collidedWithObject_H(PlayerObject* self, void*, GameObject* obj, int va, int vb, int vc, int vd) {
    if (!PlatformerMod::enableMe) return PlayerObject_collidedWithObject(self, obj, va, vb, vc, vd);
    bool dontRetOrg = false;
    auto plr = self;//PlatformerMod::gameLayer->m_pPlayer1;
    //pos
    auto plrPos = CCPoint(plr->getPositionX(), plr->getPositionY());
    auto objPos = CCPoint(obj->getPositionX(), obj->getPositionY());
    //Size
    auto pS = plr->m_obObjectSize;
    auto objS = obj->m_obObjectSize;
    //corner obj pos
    auto cd = (objPos.y) - (objS.height / 2);
    auto cu = (objPos.y) + (objS.height / 2);
    auto cr = (objPos.x) + (objS.width / 2);
    auto cl = (objPos.x) - (objS.width / 2);
    //0* corner with plain space
    auto sd = (objPos.y) - (objS.height);
    auto su = (objPos.y) + (objS.height);
    auto sr = (objPos.x) + (objS.width);
    auto sl = (objPos.x) - (objS.width);
    auto poffset = 0;
    //booleans
    bool pO = (plrPos.x <= objPos.x);
    bool Op = (objPos.x <= plrPos.x);
    //dbg.
    /*dbg->setString(std::format(
        "cd={} cu={} cr={} cl={}""\n"
        "sd={} su={} sr={} sl={}""\n"
        "ox={} oy={}""\n"
        "px={} py={}""\n"
        "\n"
        "pS={},{}""\n"
        "objS={},{}""\n"
        , cd, cu, cr, cl
        , sd, su, sr, sl
        , objPos.x, objPos.y
        , plrPos.x, plrPos.y
        , pS.width, pS.height
        , objS.width, objS.height
    ).c_str());*/
    //to dont touch wall or "wall stairs bug" LEFT
    {
        auto rstickoffset = (sl - 8);
        auto rstickoffset2 = (sl + 2);
        if (pO and (plrPos.x > rstickoffset) and (plrPos.x < rstickoffset2)) {
            dontRetOrg = true;
        }
    };
    //to dont touch wall or "wall stairs bug" RIGHT
    {
        auto rstickoffset = (sr + 8);
        auto rstickoffset2 = (sr - 2);
        if (Op and (plrPos.x < rstickoffset) and (plrPos.x > rstickoffset2)) {
            dontRetOrg = true;
        }
    };
    //to dont touch blocks for downs cubes
    {
        bool canPass = (plrPos.x > sl + 5) and (sr - 5 > plrPos.x);//todoshit
        bool needsHeadProtection = plr->isCube() or plr->m_isRobot or plr->m_isSpider;
        //!m_isUpsideDown
        auto dstickoffset = (objPos.y);
        auto dfreeffset = (sd);
        bool isUnderBlock = (plrPos.y < dstickoffset) and (plrPos.y > dfreeffset);
        if (!plr->m_isUpsideDown and isUnderBlock and needsHeadProtection and canPass) {
            dontRetOrg = true;
            plr->m_yAccel = -fabs(plr->m_yAccel / 2);
            plr->setPositionY(sd);
        }
        //m_isUpsideDown
        auto ustickoffset = (objPos.y);
        auto ufreeffset = (su);
        bool isOnBlock = (plrPos.y > ustickoffset) and (plrPos.y < ufreeffset);
        if (plr->m_isUpsideDown and isOnBlock and needsHeadProtection and canPass) {
            dontRetOrg = true;
            plr->m_yAccel = fabs(plr->m_yAccel / 2);
            plr->setPositionY(su);
        }
    };
    //not on or under block, cetterx or innerx like
    if (plrPos.y < cu + 5 and plrPos.y > cd - 5) {
        plr->m_playerSpeed = .0f;
        dontRetOrg = true;
        //p > o
        if (pO) {
            plr->setPositionX(sl - poffset);
        }
        //o < p
        if (Op) {
            plr->setPositionX(sr + poffset);
        }
    }
    return dontRetOrg ? false : PlayerObject_collidedWithObject(self, obj, va, vb, vc, vd);
}

//static gd::string lengthKeyToString(int key) = mac 0x2DBBD0, win 0xbd910;
std::string __fastcall lengthKeyToString(int key) {
    auto rtn = MappedHooks::getOriginal(lengthKeyToString)(key);
    return key == 5 ? "Plat." : rtn;
}

//void loadCustomLevelCell() = mac 0x1183b0, win 0x5a020;
void __fastcall loadCustomLevelCell(LevelCell* pClass) {
    auto oldVersion = pClass->m_pLevel->m_nGameVersion;
    ModUtils::log(std::format("m_nGameVersion={}", pClass->m_pLevel->m_nGameVersion));
    pClass->m_pLevel->m_nGameVersion = 21;
    MappedHooks::getOriginal(loadCustomLevelCell)(pClass);
    //pClass->m_pLevel->m_nGameVersion = oldVersion;
    
    //server will not give level anyways...
}

DWORD WINAPI thread_func(void* hModule) {
    
    // initialize minhook
    MH_Initialize();

    //ModUtils::OpenConsole();
    HOOK(base + 0x170e50, LevelSettingsLayer_init);
    MappedHooks::registerHook(base + 0xbd910, lengthKeyToString);
    //MappedHooks::registerHook(base + 0x5a020, loadCustomLevelCell);
    HOOK(base + 0x1ebdd0, PlayerObject_collidedWithObject);

    HOOK(base + 0x205460, updateVisibility);
    HOOK(base + 0x1FB780, PlayLayer_init);
    HOOK(base + 0x15ee00, LevelEditorLayer_init);
    HOOK(base + 0x16a660, LevelEditorLayer_update);
    HOOK(base + 0xEF0E0, GameObject_activateObject);
    HOOK(base + 0x1F4FF0, PlayerObject_ringJump);
    HOOK(base + 0x10ed50, GJBaseGameLayer_bumpPlayer);

    HOOK(base + 0xce440, GameManager_update);

    filesystem::create_directories("config");
    cfg.LoadFile("config/gdPlatformerMode.ini");
    
    if (!(cfg.KeyExists("gdPlatformerMode", "updateRotation")))
        cfg.SetBoolValue("gdPlatformerMode", "updateRotation", true, "; allow all features related to rotation");
    if (!(cfg.KeyExists("gdPlatformerMode", "particlesUpdate")))
        cfg.SetBoolValue("gdPlatformerMode", "particlesUpdate", true, "; allow all features related to particles");
    if (!(cfg.KeyExists("gdPlatformerMode", "scaleUpdate")))
        cfg.SetBoolValue("gdPlatformerMode", "scaleUpdate", true, "; allow all features related to scale");
    if (!(cfg.KeyExists("gdPlatformerMode", "animationsUpdate")))
        cfg.SetBoolValue("gdPlatformerMode", "animationsUpdate", true, "; allow all features related to animations of robot or spider");
    if (!(cfg.KeyExists("gdPlatformerMode", "idleAnimationName")))
        cfg.SetValue("gdPlatformerMode", "idleAnimationName", "idle01", "; set \"idle\" if u have not 2.2 animations");
    /*if (!(cfg.KeyExists("gdPlatformerMode", "camXoffsetUpdate")))
        cfg.SetBoolValue("gdPlatformerMode", "camXoffsetUpdate", true, "; allow camera moving x feature");*/
    if (!(cfg.KeyExists("gdPlatformerMode", "AlwaysMultiActivate")))
        cfg.SetBoolValue("gdPlatformerMode", "AlwaysMultiActivate", false, "; set HasBeenActivated = false for every object (or its multi activate feature).\n; WARN: cube portal maybe imposter");
    if (!(cfg.KeyExists("gdPlatformerMode", "PlatMultiActivate")))
        cfg.SetBoolValue("gdPlatformerMode", "PlatMultiActivate", false, "; set HasBeenActivated = false for every object (or its multi activate feature).\n; WARN: cube portal maybe imposter");
    if (!(cfg.KeyExists("gdPlatformerMode", "forcePlatformer")))
        cfg.SetBoolValue("gdPlatformerMode", "forcePlatformer", false, "; plat in all levels ");

    SI_Error err;
    err = cfg.SaveFile("config/gdPlatformerMode.ini");

    return 0;
}
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, thread_func, hModule, 0, 0);
    return TRUE;
}
