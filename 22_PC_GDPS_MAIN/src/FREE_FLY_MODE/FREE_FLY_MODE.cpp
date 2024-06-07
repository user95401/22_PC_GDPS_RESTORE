#include "ModUtils.hpp"
#include "HooksUtils.hpp"
#include "customLayerxd.hpp"
using namespace cocos2d;
using namespace extension;
#include "gd.h"
using namespace gd;

class FreeFlyNode : public CCNode {
public:
    inline static int uniqueTag = 9123;
    bool m_freeModeEnabled = false;
    PlayLayer* m_pPlayLayer = GameManager::sharedState()->getPlayLayer();
    void update(float) {
        if (!m_pPlayLayer or !this) return;
        m_freeModeEnabled = true;///TESTING TEMP
        auto winSize = CCDirector::sharedDirector()->getWinSize();
        if (m_freeModeEnabled) {
            //0x2071d0
            //m_pPlayLayer->m_bIsDualMode = true;
            //m_pPlayLayer->m_cameraY = m_pPlayLayer->m_pPlayer1->m_position.y - winSize.height / 2;
        };
    }
    static auto create(PlayLayer* pPlayLayer) {
        auto __this = new FreeFlyNode;
        __this->init();
        __this->setTag(uniqueTag);
        __this->m_pPlayLayer = pPlayLayer;
        __this->schedule(schedule_selector(FreeFlyNode::update));
        return __this;
    }
    static void tryAddMe(PlayLayer* pPlayLayer) {
        if (pPlayLayer->getChildByTag(uniqueTag)) return;
        else pPlayLayer->addChild(create(pPlayLayer));
    }
};

bool __fastcall PlayLayer_init(PlayLayer* self, int edx, GJGameLevel* level) {
    auto rtn = MappedHooks::getOriginal(PlayLayer_init)(self, edx, level);
    FreeFlyNode::tryAddMe(self);
    //shit
    /*if (PlayLayerExt::freeMode && self->isRunning() && !self->m_isDead) {
        if (!self->m_bIsDualMode) self->m_bIsDualMode = true;
        self->m_pPlayer2->m_position = CCPoint(-999999, self->m_pPlayer1->m_position.y + 5);
    }*/
    return rtn;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;
    MH_Initialize();
    MappedHooks::registerHook(gd::base + 0x1FB780, PlayLayer_init);
    return TRUE;
}