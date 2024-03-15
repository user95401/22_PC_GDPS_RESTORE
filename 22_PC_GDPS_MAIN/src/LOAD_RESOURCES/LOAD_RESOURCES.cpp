#include "ModUtils.hpp"
#include "HooksUtils.hpp"
using namespace cocos2d;
using namespace extension;
using namespace gd;

inline void(__thiscall* LoadingLayer_loadAssets)(LoadingLayer*);
void __fastcall LoadingLayer_loadAssets_H(LoadingLayer* self, void*) {
    LoadingLayer_loadAssets(self);
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
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;
    MH_Initialize();
    HOOK(base + 0x18C8E0, LoadingLayer_loadAssets, false);
    return TRUE;
}