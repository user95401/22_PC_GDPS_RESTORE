#include "ModUtils.hpp"
#include "HooksUtils.hpp"
#include "gd.h"
using namespace gd;
using namespace cocos2d;

void(__thiscall* customSetup)(GameObject*);
void __fastcall customSetup_H(GameObject* self, int) {
    customSetup(self);
    if (self->m_nObjectID == 3004) {//spider ring
        //main setups
        self->m_nObjectType = kGameObjectTypePinkJumpRing;
        self->m_pBaseColor->defaultColorID = 1011;
    }
    if (self->m_nObjectID == 3005) {//spider pad
        //main setups
        self->m_nObjectType = kGameObjectTypePinkJumpPad;//type
        self->m_pBaseColor->defaultColorID = 1011;//defaultColor
        //box setups
        self->setAnchorPoint(CCPoint(self->getAnchorPoint().x, 1.4));// totally :smiling_face_with_tear:
        auto frame = cocos2d::CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(self->m_sTextureName.c_str());
        self->m_obObjectSize = cocos2d::CCSizeMake(frame->getRect().size.width, frame->getRect().size.height);
        self->m_obBoxOffset = CCPoint(0, -10);
        self->m_obBoxOffset2 = CCPoint(0, -10);
    }
}

void(__thiscall* ringJump)(PlayerObject*, GameObject*);
void __fastcall ringJump_H(gd::PlayerObject* self, int, gd::GameObject* ring) {
    ringJump(self, ring);
    if (ring->m_nObjectID == 3004 && self->m_canRobotJump && self->m_isHolding) {
        self->spiderTestJump(true);
    }
}

void(__thiscall* bumpPlayer)(GJBaseGameLayer*, PlayerObject*, GameObject*);
void __fastcall bumpPlayer_H(GJBaseGameLayer* self, int, gd::PlayerObject* Player, gd::GameObject* bumper) {
    bumpPlayer(self, Player, bumper);
    if (bumper->m_nObjectID == 3005) {
        Player->spiderTestJump(true);
    }
}

void(__thiscall* EditorUI_setupCreateMenu)(EditorUI*);
void __fastcall EditorUI_setupCreateMenu_H(EditorUI* self, void*) {
    EditorUI_setupCreateMenu(self);
    //tab6
    auto tab6 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(6));
    tab6->m_pButtonArray->insertObject(self->getCreateBtn(3005, 4), 4);//spider pad
    tab6->m_pButtonArray->insertObject(self->getCreateBtn(3004, 4), 13);//spider orb
    tab6->reloadItemsInNormalSize();

    return;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;
    MH_Initialize(); 
    HOOK(base + 0xd1c10, customSetup);
    HOOK(base + 0x1f4ff0, ringJump);
    HOOK(base + 0x10ed50, bumpPlayer);
    HOOK(base + 0x7CAF0, EditorUI_setupCreateMenu);//huh
    ObjectToolbox::sharedState()->addObject(3004, "spiderRing_001.png");
    ObjectToolbox::sharedState()->addObject(3005, "spiderBump_001.png");
    return TRUE;
}