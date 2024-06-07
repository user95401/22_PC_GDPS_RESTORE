#include "FakeLevelSelectLayerLol.hpp"
#include "mod_utils.hpp"

#include "gd.h"
using namespace gd;
using namespace std;
using namespace cocos2d;
using namespace cocos2d::extension;

class LevelItem : public CCMenuItem {
public:
    GJGameLevel* level;
    CCMenu* menu;
    static LevelItem* create(GJGameLevel* level) {
        LevelItem* pRet = new LevelItem();
        pRet->level = level;
        if (pRet && pRet->init()) {
            pRet->autorelease();
            return pRet;
        }
        else {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }
    bool init() {
        setContentSize(CCDirector::sharedDirector()->getWinSize());
        //menu
        menu = CCMenu::create();
        menu->setContentSize(getContentSize());
        addChild(menu, 10);
        //square bg
        CCScale9Sprite* CCScale9Sprite_ = CCScale9Sprite::create("square02_small.png");
        CCScale9Sprite_->setContentSize({ 340.000f, 95.000f });
        CCScale9Sprite_->setOpacity(125);
        //PlayBtn
        CCMenuItemSpriteExtra* PlayBtn = CCMenuItemSpriteExtra::create(CCScale9Sprite_, this, menu_selector(LevelItem::onPlay));
        PlayBtn->setPositionY(62.000f);
        menu->addChild(PlayBtn, -2);
        if (PlayBtn) {//PlayBtn containerssf
            //sLevelName
            CCLabelBMFont* sLevelName = CCLabelBMFont::create(level->m_sLevelName.c_str(), "bigFont.fnt");
            sLevelName->setAlignment(kCCTextAlignmentLeft);
            sLevelName->setAnchorPoint({ 0.0f, 0.5f });
            sLevelName->setPositionX(66.000f);
            sLevelName->setPositionY(50.000f);
            if (sLevelName->getContentSize().width > 200.000f)
                sLevelName->setScale((CCScale9Sprite_->getContentSize().width - 110) / sLevelName->getContentSize().width);
            PlayBtn->addChild(sLevelName);
            //difficulty texture :skull:
            const char* difficultySpriteName;
            switch (level->m_eDifficulty) {
            case kGJDifficultyAuto:
                difficultySpriteName = "difficulty_auto_btn_001.png";
                break;
            case kGJDifficultyEasy:
                difficultySpriteName = "difficulty_01_btn_001.png";
                break;
            case kGJDifficultyNormal:
                difficultySpriteName = "difficulty_02_btn_001.png";
                break;
            case kGJDifficultyHard:
                difficultySpriteName = "difficulty_03_btn_001.png";
                break;
            case kGJDifficultyHarder:
                difficultySpriteName = "difficulty_04_btn_001.png";
                break;
            case kGJDifficultyInsane:
                difficultySpriteName = "difficulty_05_btn_001.png";
                break;
            case kGJDifficultyDemon:
                difficultySpriteName = "difficulty_06_btn_001.png";
                break;
            default:
                difficultySpriteName = "difficulty_00_btn_001.png";
                break;
            }
            CCSprite* DifficultySprite = ModUtils::createSprite(difficultySpriteName);
            PlayBtn->addChild(DifficultySprite);
            DifficultySprite->setPositionX(36.000f);
            DifficultySprite->setPositionY(44.000f);
            DifficultySprite->setScale(1.100f);
        }
        //normalmode
        CCLabelBMFont* normalmode = CCLabelBMFont::create(
            ("Normal Mode"), "bigFont.fnt");
        normalmode->setAlignment(kCCTextAlignmentCenter);
        normalmode->setPositionY(-10.000f);
        normalmode->setScale(0.600f);
        menu->addChild(normalmode);
        //normalPercent
        CCLabelBMFont* normalPercent = CCLabelBMFont::create(
            ("%" + to_string(level->m_nNormalPercent)).c_str(), "bigFont.fnt");
        normalPercent->setAlignment(kCCTextAlignmentCenter);
        normalPercent->setPositionY(-33.000f);
        normalPercent->setScale(0.500f);
        normalPercent->runAction(CCTintBy::create(0.1, -fabs(level->m_nNormalPercent), 0, -fabs(level->m_nNormalPercent)));
        menu->addChild(normalPercent);
          // --------------------------------------------------------------------------------
         // Normal Bar
        // --------------------------------------------------------------------------------
        CCSprite* pBarNormalSprite = CCSprite::create("GJ_progressBar_001.png");
        if (pBarNormalSprite) {
            pBarNormalSprite->setColor(ccBLACK);
            pBarNormalSprite->setPositionY(-34.000f);
            pBarNormalSprite->setOpacity(125);
            pBarNormalSprite->setScale(1.0f);
            menu->addChild(pBarNormalSprite, -3);
            //pBarNormalSprite->setPosition(CCPoint(winSize.width * 0.5f, winSize.height * 0.5f - 30.0f));
            //mUnknownArray1->addObject(pBarNormalSprite);
            CCSprite* mProgressBarNormal = CCSprite::create("GJ_progressBar_001.png");
            mProgressBarNormal->setScaleX(0.992f);
            mProgressBarNormal->setScaleY(0.86f);
            mProgressBarNormal->setColor({ 0, 255, 0 });
            CCRect pBarRectNormal = mProgressBarNormal->getTextureRect();
            float mUnknownFloat1 = pBarRectNormal.size.width;
            float valNormal = pBarRectNormal.size.width - pBarRectNormal.size.width * 0.992f;
            pBarNormalSprite->addChild(mProgressBarNormal, 1);
            mProgressBarNormal->setAnchorPoint(CCPoint(0.0f, 0.5f));
            mProgressBarNormal->setPosition(CCPoint(valNormal * 0.5f, pBarNormalSprite->getContentSize().height * 0.5f));
            float normPercent = mUnknownFloat1;
            if (normPercent > (mUnknownFloat1 * (static_cast<float>(level->m_nNormalPercent) / 100.0f)))
                normPercent = mUnknownFloat1 * (static_cast<float>(level->m_nNormalPercent) / 100.0f);
            mProgressBarNormal->setTextureRect(CCRect(0.0f, 0.0f, normPercent, mProgressBarNormal->getTextureRect().size.height));
        }
        //practiceText 
        CCLabelBMFont* practiceText = CCLabelBMFont::create(
            ("Practice Mode"), "bigFont.fnt");
        practiceText->setAlignment(kCCTextAlignmentCenter);
        practiceText->setPositionY(-62.000f);
        practiceText->setScale(0.600f);
        menu->addChild(practiceText);
        //practicePercent
        CCLabelBMFont* practicePercent = CCLabelBMFont::create(
            ("%" + to_string(level->m_nPracticePercent)).c_str(), "bigFont.fnt");
        practicePercent->setAlignment(kCCTextAlignmentCenter);
        practicePercent->setPositionY(-85.000f);
        practicePercent->setScale(0.500f);
        practicePercent->runAction(CCTintBy::create(0.1, -fabs(level->m_nPracticePercent), 0, 0));
        menu->addChild(practicePercent);
          // --------------------------------------------------------------------------------
         // Practice Bar
        // --------------------------------------------------------------------------------
        CCSprite* pBarPracticeSprite = CCSprite::create("GJ_progressBar_001.png");
        if (pBarPracticeSprite) {
            pBarPracticeSprite->setColor(ccBLACK);
            pBarPracticeSprite->setPositionY(-86.000f);
            pBarPracticeSprite->setOpacity(125);
            pBarPracticeSprite->setScale(1.0f);
            menu->addChild(pBarPracticeSprite, -3);
            //pBarPracticeSprite->setPosition(CCPoint(winSize.width * 0.5f, winSize.height * 0.5f - 30.0f));
            //mUnknownArray1->addObject(pBarPracticeSprite);
            CCSprite* mProgressBarPractice = CCSprite::create("GJ_progressBar_001.png");
            mProgressBarPractice->setScaleX(0.992f);
            mProgressBarPractice->setScaleY(0.86f);
            mProgressBarPractice->setColor({ 0, 255, 255 });
            CCRect pBarRectPractice = mProgressBarPractice->getTextureRect();
            float mUnknownFloat2 = pBarRectPractice.size.width;
            float valPractice = pBarRectPractice.size.width - pBarRectPractice.size.width * 0.992f;
            pBarPracticeSprite->addChild(mProgressBarPractice, 1);
            mProgressBarPractice->setAnchorPoint(CCPoint(0.0f, 0.5f));
            mProgressBarPractice->setPosition(CCPoint(valPractice * 0.5f, pBarPracticeSprite->getContentSize().height * 0.5f));
            float PracticePercent = mUnknownFloat2;
            if (PracticePercent > (mUnknownFloat2 * (static_cast<float>(level->m_nPracticePercent) / 100.0f)))
                PracticePercent = mUnknownFloat2 * (static_cast<float>(level->m_nPracticePercent) / 100.0f);
            mProgressBarPractice->setTextureRect(CCRect(0.0f, 0.0f, PracticePercent, mProgressBarPractice->getTextureRect().size.height));
        }
        //star
        CCSprite* mStarSprite = CCSprite::createWithSpriteFrameName("GJ_starsIcon_001.png");
        PlayBtn->addChild(mStarSprite);
        mStarSprite->setScale(0.7f);
        mStarSprite->setPosition(CCPoint(CCScale9Sprite_->getScaledContentSize().width - 12.0f, CCScale9Sprite_->getScaledContentSize().height - 12.0f));
        CCLabelBMFont* mUnknownText4 = CCLabelBMFont::create(("" + to_string(level->m_nStars)).c_str(), "bigFont.fnt");
        PlayBtn->addChild(mUnknownText4);
        mUnknownText4->setAnchorPoint(CCPoint(1.0f, 0.5f));
        mUnknownText4->setPosition(mStarSprite->getPosition() + CCPoint(-12.0f, 0.5f));
        mUnknownText4->setScale(0.5f); ;
        if (reinterpret_cast<bool(__thiscall*)(GameStatsManager*, GJGameLevel*)>
            (base + 0xF63E0)(GameStatsManager::sharedState(), level))
             mUnknownText4->setColor({ 255, 255, 50 });
        else mUnknownText4->setColor(ccWHITE);
        return true;
    }
    void onPlay(CCObject* object) {
        LevelInfoLayer* LevelInfoLayer_ = LevelInfoLayer::create(level);
        reinterpret_cast<void(__thiscall*)(LevelInfoLayer*, cocos2d::CCObject*)>(base + 0x179730)(LevelInfoLayer_, object);
        //ok fine then i create it
        CCDirector::sharedDirector()->pushScene(
            CCTransitionFade::create(
                0.5f, 
                PlayLayer::scene(level)
            )
        );
    }
};

class CumingSoonItem : public CCMenuItem {
public:
    CCMenu* menu;
    static CumingSoonItem* create() {
        CumingSoonItem* pRet = new CumingSoonItem();
        if (pRet && pRet->init()) {
            pRet->autorelease();
            return pRet;
        }
        else {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }
    bool init() {
        setContentSize(CCDirector::sharedDirector()->getWinSize());
        //menu
        menu = CCMenu::create();
        addChild(menu, 10);
        //comingSoonActually
        CCLabelBMFont* comingSoonActually = CCLabelBMFont::create("Coming soon!", "bigFont.fnt");
        comingSoonActually->setAlignment(kCCTextAlignmentLeft);
        comingSoonActually->setAnchorPoint({ 0.500f, -0.500f });
        menu->addChild(comingSoonActually);
        return true;
    }
};

FakeLevelSelectLayerLol* FakeLevelSelectLayerLol::create(int page)
{
    FakeLevelSelectLayerLol* pRet = new FakeLevelSelectLayerLol();
    //get levels count
    pRet->LEVEL_INDEX_START = 1;
    pRet->LEVEL_INDEX_END = 1;
    for (int i = pRet->LEVEL_INDEX_START; i < 100; i++)
    {
        if (
            GameLevelManager::sharedState()->getMainLevel(i, 0)->m_sLevelName 
            != 
            GameLevelManager::sharedState()->getMainLevel(pRet->LEVEL_INDEX_START, 0)->m_sLevelName
            )
            ++pRet->LEVEL_INDEX_END;
    }
    if (pRet && pRet->init(page))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

CCScene* FakeLevelSelectLayerLol::scene(int page) {
    // 'scene' is an autorelease object
    CCScene* scene = CCScene::create();
    // 'layer' is an autorelease object
    FakeLevelSelectLayerLol* layer = FakeLevelSelectLayerLol::create(page);
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

void FakeLevelSelectLayerLol::keyBackClicked() {
    CCDirector::sharedDirector()->popSceneWithTransition(0.500f, PopTransition::kPopTransitionFade);
}

void FakeLevelSelectLayerLol::onBack(CCObject* object) {
    keyBackClicked();
}

void FakeLevelSelectLayerLol::onBackward(CCObject* object) {
    if (mPage <= LEVEL_INDEX_START - 1 
        || 
        (mPage <= LEVEL_INDEX_START && !strstr(to_string(((double)LEVEL_INDEX_END / 2)).data(), ".5"))) {
        for (int i = LEVEL_INDEX_START; i <= LEVEL_INDEX_END + 1; i++) {
            shitcodingmenu->runAction(CCMoveBy::create(
                0.000f,
                CCPoint(-(CCDirector::sharedDirector()->getWinSize().width), 0.000f)
            ));
            ++mPage;
        }
        return onBackward(object);
    }
    //move page so
    --mPage;
    shitcodingmenu->runAction(
        CCEaseElasticOut::create(CCMoveBy::create(0.6f,
            CCPoint(CCDirector::sharedDirector()->getWinSize().width, 0.000f)
        ), 0.65f));
}

void FakeLevelSelectLayerLol::onForward(CCObject* object) {
    if (mPage >= LEVEL_INDEX_END + 1) {
        for (int i = LEVEL_INDEX_START; i <= LEVEL_INDEX_END + 1; i++) {
            shitcodingmenu->runAction(CCMoveBy::create(
                0.000f,
                CCPoint((CCDirector::sharedDirector()->getWinSize().width), 0.000f)
            ));
            --mPage;
        }
        return onForward(object);
    }
    //move page so
    ++mPage;
    shitcodingmenu->runAction(
        CCEaseElasticOut::create(CCMoveBy::create(0.6f,
            CCPoint(-CCDirector::sharedDirector()->getWinSize().width, 0.000f)
        ), 0.65f));
}

void FakeLevelSelectLayerLol::hopTo(CCObject* object) {
    mPage = object->getTag();
    shitcodingmenu->setPosition(CCPointZero);
    CCPoint moveToP = CCPointZero;
    //movetofirst
    for (int i = LEVEL_INDEX_START; i <= LEVEL_INDEX_END / 2; i++) {
        moveToP.x = (moveToP.x + CCDirector::sharedDirector()->getWinSize().width);
    }
    //movetotarg
    for (int i = LEVEL_INDEX_START; i < mPage; i++) {
        moveToP.x = (moveToP.x - CCDirector::sharedDirector()->getWinSize().width);
    }
    shitcodingmenu->setPositionX(moveToP.x);
}

void FakeLevelSelectLayerLol::updateButtons(CCObject* object) {
    if (shitdotingmenu) {
        for (int i = 1; i <= shitdotingmenu->getChildrenCount(); i++) {
            CCNode* thisdot = shitdotingmenu->getChildByTag(i) ? shitdotingmenu->getChildByTag(i) : CCNode::create();
            if (thisdot->getTag() == mPage) thisdot->runAction(CCTintTo::create(0.1f, 160, 160, 160));
            else thisdot->runAction(CCTintTo::create(0.1f, 255, 255, 255));
        }
    };
}

void FakeLevelSelectLayerLol::downloadSongs(CCObject* object) {
    GJDropDownLayer* songslayer = reinterpret_cast<GJDropDownLayer*(__fastcall*)()>(
                    base + 0x2513B0
                )();
    
                cocos2d::CCDirector::sharedDirector()
                    ->getRunningScene()
                    ->addChild(songslayer);
                songslayer->showLayer(false);
}

void FakeLevelSelectLayerLol::lvlinfo(CCObject* object) {
    GJGameLevel* tarlvl = GameLevelManager::sharedState()->getMainLevel(mPage, 0);
    stringstream desc;
    desc << "<cy>" << tarlvl->m_sLevelName << "</c>" << endl;
    if (tarlvl->m_sCreatorName != "") desc << "<co>By: " << tarlvl->m_sCreatorName << "</c>" << endl;
    if (to_string(tarlvl->m_nAttempts) != "0") desc << "<cr>Total Attempts: </c>" << to_string(tarlvl->m_nAttempts) << endl;
    if (to_string(tarlvl->m_nJumps) != "0") desc << "<co>Total Jumps: </c>" << to_string(tarlvl->m_nJumps) << endl;
    if (to_string(tarlvl->m_nNormalPercent) != "0") desc << "<cg>Normal: </c>" << to_string(tarlvl->m_nNormalPercent) << "%" << endl;
    if (to_string(tarlvl->m_nPracticePercent) != "0") desc << "<cl>Practice: </c>" + to_string(tarlvl->m_nPracticePercent) << "%" << endl;
    if (tarlvl->m_sPersonalBests != "") desc << "<cb>Personal Bests: </c>" + tarlvl->m_sPersonalBests << endl;
    FLAlertLayer* pop = FLAlertLayer::create(nullptr, "Level info", "OK", nullptr, desc.str());
    pop->show();
    copyLvlStrLabel = CCLabelTTF::create("copy level string to clipboard", "arial", 6.0);
    CCMenuItemLabel* copyLvlStrLabelItem = CCMenuItemLabel::create(copyLvlStrLabel, this, menu_selector(FakeLevelSelectLayerLol::copylvlstr));
    copyLvlStrLabelItem->setPositionY(-35.000f);
    copyLvlStrLabelItem->setOpacity(0);
    copyLvlStrLabelItem->runAction(CCSequence::create(CCDelayTime::create(0.5), CCFadeTo::create(0.5, 90), nullptr));
    pop->m_pButtonMenu->addChild(copyLvlStrLabelItem);
}

void FakeLevelSelectLayerLol::copylvlstr(CCObject* object) {
    ModUtils::copyToClipboard(GameLevelManager::sharedState()->getMainLevel(mPage, 0)->m_sLevelString.c_str());
    copyLvlStrLabel->setString("                copied!");
    scheduleOnce(schedule_selector(FakeLevelSelectLayerLol::copylvlstrsch), 3.0);
}

void FakeLevelSelectLayerLol::copylvlstrsch(float dt) {
    copyLvlStrLabel->setString("copy level string to clipboard");
}

void FakeLevelSelectLayerLol::schedulethingyo(float dt) {
    //ground color
    reinterpret_cast<void(__thiscall*)(GJGroundLayer*, cocos2d::_ccColor3B)>
        (base + 0x12DB40)
        (this->mGroundLayer, ccColor3B(
            mBackgroundSprite->getColor().r,
            mBackgroundSprite->getColor().g,
            mBackgroundSprite->getColor().b)
            );
}

void FakeLevelSelectLayerLol::scheduledelayed(float dt) {
    //kill me
    updateButtons(nullptr);
    //page log here brain fucks
    this->removeChildByTag(522);
    this->addChild(CCLabelTTF::create(
        ("mPage:" + to_string(mPage) + "\nLEVEL_INDEX_START:" + to_string(LEVEL_INDEX_START) + "\nLEVEL_INDEX_END:" + to_string(LEVEL_INDEX_END) + "\n \n \n \n \n").c_str(), "arial", 8.000f, { 300, 95 }, CCTextAlignment::kCCTextAlignmentRight), 123, 522)
        ;
    //setOpacity to log
    if(this->getChildByTag(522)) 
        reinterpret_cast<CCLabelTTF*>(this->getChildByTag(522))->setOpacity(6);
    //onBackwardleftTouchZone
    if (leftTouchZone->isSelected() ||
        (GetKeyState(KEY_Left) & 0x8000)) {
        onBackward(nullptr);
        leftBtn->runAction(CCTintTo::create(0.1f, 160, 160, 160));
    }
    else leftBtn->runAction(CCTintTo::create(0.1f, 255, 255, 255));
    //rightTouchZone
    if (rightTouchZone->isSelected() ||
        (GetKeyState(KEY_Right) & 0x8000)) {
        onForward(nullptr);
        rightBtn->runAction(CCTintTo::create(0.1f, 160, 160, 160));
    }
    else rightBtn->runAction(CCTintTo::create(0.1f, 255, 255, 255));
    //play
    if ((GetKeyState(KEY_Space) & 0x8000)) {
        LevelItem::create(GameLevelManager::sharedState()->getMainLevel(mPage, 0))->onPlay(nullptr);
        this->unschedule(schedule_selector(FakeLevelSelectLayerLol::scheduledelayed));
    }
    //color
    auto pageColor = GameManager::sharedState()->colorForIdx(mPage);
    this->mBackgroundSprite->runAction(CCTintTo::create(0.150f, pageColor.r, pageColor.g, pageColor.b));
}

bool FakeLevelSelectLayerLol::init(int page)
{                               //who needs it ya?
    if (!CCLayer::init())
        return false;

    mPage = LEVEL_INDEX_START;

    this->setKeypadEnabled(true);
    this->setKeyboardEnabled(true);

    this->schedule(schedule_selector(FakeLevelSelectLayerLol::schedulethingyo));
    this->schedule(schedule_selector(FakeLevelSelectLayerLol::scheduledelayed), 0.15f);

    s_didClick = false;

    // AchievementManager
    AchievementManager* pAchievementManager = AchievementManager::sharedState();
    //this->mEarnedAchievement = pAchievementManager->isAchievementEarned("geometry.ach.secret04");

    CCDirector* pDirector = CCDirector::sharedDirector();
    CCSize winSize = pDirector->getWinSize();

    mBackgroundSprite = CCSprite::create("GJ_gradientBG.png");
    mBackgroundSprite->setAnchorPoint(CCPoint(0.0f, 0.0f));
    this->addChild(mBackgroundSprite, -2);
    mBackgroundSprite->setScaleX((winSize.width + 10.0f) / mBackgroundSprite->getTextureRect().size.width);
    mBackgroundSprite->setScaleY((winSize.height + 10.0f) / mBackgroundSprite->getTextureRect().size.height);
    mBackgroundSprite->setPosition(CCPoint(-5.0f, -5.0f));
    mBackgroundSprite->setColor({ 40, 125, 255 });

    GameManager* pGameManager = GameManager::sharedState();
    
    mGroundLayer = reinterpret_cast<GJGroundLayer * (__fastcall*)(int, int)>(base + 0x12D490)(1, 1);
    this->addChild(mGroundLayer, 0);
    mGroundLayer->setPositionY(-40.000);

    CCSprite* topBar = CCSprite::createWithSpriteFrameName("GJ_topBar_001.png");
    topBar->setAnchorPoint(CCPoint(0.5f, 1.0f));
    topBar->setPosition(CCPoint(winSize.width * 0.5f, pDirector->getScreenTop() + 1.0f));
    this->addChild(topBar, 1);

    CCSprite* sideArtLeft = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    sideArtLeft->setAnchorPoint(CCPoint(0.0f, 0.0f));
    sideArtLeft->setPosition(CCPoint(pDirector->getScreenLeft() - 1.0f, pDirector->getScreenBottom() - 1.0f));
    this->addChild(sideArtLeft, 1);

    CCSprite* sideArtRight = CCSprite::createWithSpriteFrameName("GJ_sideArt_001.png");
    sideArtRight->setAnchorPoint(CCPoint(1.0f, 0.0f));
    sideArtRight->setPosition(CCPoint(pDirector->getScreenRight() + 1.0f, pDirector->getScreenBottom() - 1.0f));
    sideArtRight->setFlipX(true);
    this->addChild(sideArtRight, 1);

    //levels
    shitcodingmenu = CCMenu::create();
    shitcodingmenu->setPosition(CCPointZero);
    this->addChild(shitcodingmenu);
    //plholderos
    if (strstr(to_string(((double)LEVEL_INDEX_END / 2)).data(), ".5")) shitcodingmenu->addChild(CumingSoonItem::create());
    else ;//why i created it
    //add levels
    for (int i = LEVEL_INDEX_START; i <= LEVEL_INDEX_END; i++) {
        shitcodingmenu->addChild(LevelItem::create(GameLevelManager::sharedState()->getMainLevel(i, 0)));
    }
    shitcodingmenu->addChild(CumingSoonItem::create());//why i created it
    //moveto
    for (int i = LEVEL_INDEX_START; i <= LEVEL_INDEX_END / 2; i++) {
        shitcodingmenu->setPositionX(shitcodingmenu->getPositionX() + CCDirector::sharedDirector()->getWinSize().width);
    }
    shitcodingmenu->alignItemsHorizontallyWithPadding(0.0f);

    //nav dots
    shitdotingmenu = CCMenu::create();
    shitdotingmenu->setPosition(CCPointZero);
    this->addChild(shitdotingmenu);
    //add levels
    for (int i = LEVEL_INDEX_START; i <= LEVEL_INDEX_END; i++) {
        CCMenuItemSpriteExtra* CCMenuItemSpriteExtra_ = CCMenuItemSpriteExtra::create( 
            ModUtils::createSprite("uiDot_001.png"), this, menu_selector(FakeLevelSelectLayerLol::hopTo)
        );
        CCMenuItemSpriteExtra_->CCMenuItemSpriteExtra::setScale(1.15f);
        CCMenuItemSpriteExtra_->setSizeMult(1.5f);
        shitdotingmenu->addChild(CCMenuItemSpriteExtra_, 0, i);
    }
    shitdotingmenu->alignItemsHorizontallyWithPadding(0.0f);
    shitdotingmenu->setPosition(CCPoint(winSize.width * 0.5f, pDirector->getScreenBottom() + 16.000f));

    CCLabelBMFont* downloadTxt = CCLabelBMFont::create("Download the soundtracks", "bigFont.fnt");
    downloadTxt->setScale(0.5f);
    CCMenuItemSpriteExtra* downloadExtra = CCMenuItemSpriteExtra::create(downloadTxt, this, menu_selector(FakeLevelSelectLayerLol::downloadSongs));
    downloadExtra->setSizeMult(1.5f);

    CCMenu* downloadMenu = CCMenu::create(downloadExtra, nullptr);
    this->addChild(downloadMenu);
    downloadMenu->setPosition(CCPoint(winSize.width * 0.5f, pDirector->getScreenBottom() + 35.0f));

    CCMenu* navigationMenu = CCMenu::create();
    this->addChild(navigationMenu, 5);

    CCSprite* leftBtnSprite = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    leftBtnSprite->setFlipX(1);
    leftBtn = CCMenuItemSpriteExtra::create(leftBtnSprite, this, menu_selector(FakeLevelSelectLayerLol::onBackward));
    navigationMenu->addChild(leftBtn);
    leftBtn->setSizeMult(2.0f);
    leftBtn->setPosition(navigationMenu->convertToNodeSpace(CCPoint(pDirector->getScreenLeft() + 32.0f, winSize.height * 0.5f)));

    CCSprite* rightBtnSprite = CCSprite::createWithSpriteFrameName("navArrowBtn_001.png");
    rightBtn = CCMenuItemSpriteExtra::create(rightBtnSprite, this, menu_selector(FakeLevelSelectLayerLol::onForward));
    navigationMenu->addChild(rightBtn);
    rightBtn->setSizeMult(2.0f);
    rightBtn->setPosition(navigationMenu->convertToNodeSpace(CCPoint(pDirector->getScreenRight() - 32.0f, winSize.height * 0.5f)));

    CCSprite* backBtnSprite = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
    CCMenuItemSpriteExtra* backBtn = CCMenuItemSpriteExtra::create(backBtnSprite, this, menu_selector(FakeLevelSelectLayerLol::onBack));
    backBtn->setSizeMult(1.6f);
    CCMenu* backMenu = CCMenu::create(backBtn, nullptr);
    this->addChild(backMenu, 1);
    backMenu->setPosition(CCPoint(pDirector->getScreenLeft() + 25.0f, pDirector->getScreenTop() - 22.0f));

    CCMenu* infoMenu = CCMenu::create();
    this->addChild(infoMenu);

    CCSprite* infoBtnSprite = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
    CCMenuItemSpriteExtra* infoBtn = CCMenuItemSpriteExtra::create(infoBtnSprite, this, menu_selector(FakeLevelSelectLayerLol::lvlinfo));
    infoBtn->setSizeMult(2.0f);
    infoMenu->addChild(infoBtn);

    infoMenu->setPosition(CCPoint(pDirector->getScreenRight() - 20.0f, pDirector->getScreenTop() - 20.0f));
    
    //touchNav
    CCMenu* touchNav = CCMenu::create();
    touchNav->setTouchPriority(-1);
    this->addChild(touchNav);
    //leftTouchZone
    leftTouchZone = CCMenuItem::create();
    leftTouchZone->setContentSize({
        CCDirector::sharedDirector()->getWinSize().width / 2,
        CCDirector::sharedDirector()->getWinSize().height
        });
    touchNav->addChild(leftTouchZone);
    //rightTouchZone
    rightTouchZone = CCMenuItem::create();
    rightTouchZone->setContentSize({
        CCDirector::sharedDirector()->getWinSize().width / 2,
        CCDirector::sharedDirector()->getWinSize().height
        });
    touchNav->addChild(rightTouchZone);
    //touchnavalign content
    touchNav->alignItemsHorizontallyWithPadding(0.0f);

    // TODO: Missing GameToolbox
    //if (controller)
    //    GameToolbox::addBackButton(this, backBtn);

    return true;
}

#include "hooks.hpp"

LevelSelectLayer* (__thiscall* LevelSelectLayer_create)(int lvl);//0x185500
CCLayer* __fastcall LevelSelectLayer_create_H(int lvl) {
    return FakeLevelSelectLayerLol::create(1);
    //MenuGameLayer_create();
}

inline void(__thiscall* MenuLayer_onPlay)(MenuLayer*, cocos2d::CCObject*);//0x191b50
void __fastcall MenuLayer_onPlay_H(MenuLayer* self, void*, cocos2d::CCObject* pSender) {
    MenuLayer_onPlay(self, pSender);
    //this->willClose();
    //GameManager::sharedState()->mUnknownInt1 = 8;
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCScene* levelSelect = CCScene::create();
    levelSelect->addChild(LevelSelectLayer::create(1));
    CCTransitionFade* fade = CCTransitionFade::create(0.5f, levelSelect);
    pDirector->pushScene(fade);
}

void FakeLevelSelectLayerLol::makeHooks() {
    HOOK(base + 0x185500, LevelSelectLayer_create, false);
}
