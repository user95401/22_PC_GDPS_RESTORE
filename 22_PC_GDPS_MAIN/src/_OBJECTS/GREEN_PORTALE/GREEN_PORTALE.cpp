#include "ModUtils.hpp"
#include "HooksUtils.hpp"
#include "gd.h"
using namespace gd;
using namespace cocos2d;

void(__thiscall* customSetup)(GameObject*);
void __fastcall customSetup_H(GameObject* self, int) {
    customSetup(self);

    if (self->m_nObjectID == 2926) {//green portal
        self->m_nObjectType = GameObjectType::kGameObjectTypeGreenRing;
        self->setAnchorPoint(CCPoint(self->getAnchorPoint().x - 0.1, self->getAnchorPoint().y - 0.001));// totally :smiling_face_with_tear:
        self->m_obObjectSize.setSize(25.000000, 75.000000);
        self->m_bIsEffectObject = true;
    }
    if (self->m_sTextureName.find("portal_19") != self->m_sTextureName.npos && self->m_bEditor) {
        self->setDisplayFrame(cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
            "portal_19_front_001.png"));
    }
}

void(__thiscall* ringJump)(PlayerObject*, GameObject*);
void __fastcall ringJump_H(gd::PlayerObject* self, int, gd::GameObject* ring) {
    ringJump(self, ring);
    //green portale
    if (ring->m_nObjectID == 2926) {
        if (!ring->m_bHasBeenActivated) {
            if (self->m_isInPlayLayer) GameManager::sharedState()->getPlayLayer()->playGravityEffect(!self->m_isUpsideDown);
            self->flipGravity(!self->m_isUpsideDown, true);
        }
        if (!ring->m_bRandomisedAnimStart)
            ring->m_bHasBeenActivated = true;
    }
}

void(__thiscall* bumpPlayer)(GJBaseGameLayer*, PlayerObject*, GameObject*);
void __fastcall bumpPlayer_H(GJBaseGameLayer* self, int, gd::PlayerObject* Player, gd::GameObject* bumper) {
    bumpPlayer(self, Player, bumper);
}

void(__thiscall* EditorUI_setupCreateMenu)(EditorUI*);
void __fastcall EditorUI_setupCreateMenu_H(EditorUI* self, void*) {
    EditorUI_setupCreateMenu(self);
    //tab6
    if (auto tab6 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(6))) {
        tab6->m_pButtonArray->insertObject(self->getCreateBtn(2926, 4), 15);//green portal
        tab6->reloadItemsInNormalSize();
    }
    return;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;
    MH_Initialize(); 
    HOOK(base + 0xd1c10, customSetup);
    HOOK(base + 0x1f4ff0, ringJump);
    HOOK(base + 0x10ed50, bumpPlayer);
    HOOK(base + 0x7CAF0, EditorUI_setupCreateMenu);//huh
    ObjectToolbox::sharedState()->addObject(2926, "portal_19_unity_001.png");
    return TRUE;
}