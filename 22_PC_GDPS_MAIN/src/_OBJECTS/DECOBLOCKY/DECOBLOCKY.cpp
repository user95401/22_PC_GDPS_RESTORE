#include "ModUtils.hpp"
#include "HooksUtils.hpp"
#include "gd.h"
using namespace gd;
using namespace cocos2d;

void(__thiscall* customSetup)(GameObject*);
void __fastcall customSetup_H(GameObject* self, int) {
    customSetup(self);
    if (self->m_sTextureName.find("pixelart_") != self->m_sTextureName.npos) {//any pixel art
        self->m_nObjectType = kGameObjectTypeDecoration;
    }
    if (self->m_sTextureName.find("blockPiece_") != self->m_sTextureName.npos) {//any blockPiece
        self->m_nObjectType = kGameObjectTypeDecoration;
    }
}

void(__thiscall* EditorUI_setupCreateMenu)(EditorUI*);
void __fastcall EditorUI_setupCreateMenu_H(EditorUI* self, void*) {
    EditorUI_setupCreateMenu(self);
    //tab11
    if (auto tab11 = (EditButtonBar*)(self->m_pCreateButtonBars->objectAtIndex(11))) {
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1964, 4));//"blockPiece_001_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1965, 4));//"blockPiece_002_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1966, 4));//"blockPiece_003_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1967, 4));//"blockPiece_004_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1968, 4));//"blockPiece_005_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1969, 4));//"blockPiece_006_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1970, 4));//"blockPiece_007_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1971, 4));//"blockPiece_008_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1972, 4));//"blockPiece_009_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1973, 4));//"blockPiece_010_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1974, 4));//"blockPiece_011_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1975, 4));//"blockPiece_012_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1976, 4));//"blockPiece_013_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1977, 4));//"blockPiece_014_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1978, 4));//"blockPiece_015_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1979, 4));//"blockPiece_016_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1980, 4));//"blockPiece_017_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1981, 4));//"blockPiece_018_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1982, 4));//"blockPiece_019_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1983, 4));//"blockPiece_020_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1984, 4));//"blockPiece_021_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1985, 4));//"blockPiece_022_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1986, 4));//"blockPiece_023_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1987, 4));//"blockPiece_024_001.png");

        tab11->m_pButtonArray->addObject(self->getCreateBtn(1988, 4));//"blockPiece_small_001_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1989, 4));//"blockPiece_small_002_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1990, 4));//"blockPiece_small_003_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1991, 4));//"blockPiece_small_004_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1992, 4));//"blockPiece_small_005_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1993, 4));//"blockPiece_small_006_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1994, 4));//"blockPiece_small_007_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1995, 4));//"blockPiece_small_008_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1996, 4));//"blockPiece_small_009_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1997, 4));//"blockPiece_small_010_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1998, 4));//"blockPiece_small_011_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(1999, 4));//"blockPiece_small_012_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2000, 4));//"blockPiece_small_013_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2001, 4));//"blockPiece_small_014_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2002, 4));//"blockPiece_small_015_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2003, 4));//"blockPiece_small_016_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2004, 4));//"blockPiece_small_017_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2005, 4));//"blockPiece_small_018_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2006, 4));//"blockPiece_small_019_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2007, 4));//"blockPiece_small_020_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2008, 4));//"blockPiece_small_021_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2009, 4));//"blockPiece_small_022_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2010, 4));//"blockPiece_small_023_001.png");
        tab11->m_pButtonArray->addObject(self->getCreateBtn(2011, 4));//"blockPiece_small_024_001.png");
        tab11->reloadItemsInNormalSize();
    }
    return;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;

    MH_Initialize(); 
    HOOK(base + 0xd1c10, customSetup);
    HOOK(base + 0x7CAF0, EditorUI_setupCreateMenu);//huh

    ObjectToolbox::sharedState()->addObject(1964, "blockPiece_001_001.png");
    ObjectToolbox::sharedState()->addObject(1965, "blockPiece_002_001.png");
    ObjectToolbox::sharedState()->addObject(1966, "blockPiece_003_001.png");
    ObjectToolbox::sharedState()->addObject(1967, "blockPiece_004_001.png");
    ObjectToolbox::sharedState()->addObject(1968, "blockPiece_005_001.png");
    ObjectToolbox::sharedState()->addObject(1969, "blockPiece_006_001.png");
    ObjectToolbox::sharedState()->addObject(1970, "blockPiece_007_001.png");
    ObjectToolbox::sharedState()->addObject(1971, "blockPiece_008_001.png");
    ObjectToolbox::sharedState()->addObject(1972, "blockPiece_009_001.png");
    ObjectToolbox::sharedState()->addObject(1973, "blockPiece_010_001.png");
    ObjectToolbox::sharedState()->addObject(1974, "blockPiece_011_001.png");
    ObjectToolbox::sharedState()->addObject(1975, "blockPiece_012_001.png");
    ObjectToolbox::sharedState()->addObject(1976, "blockPiece_013_001.png");
    ObjectToolbox::sharedState()->addObject(1977, "blockPiece_014_001.png");
    ObjectToolbox::sharedState()->addObject(1978, "blockPiece_015_001.png");
    ObjectToolbox::sharedState()->addObject(1979, "blockPiece_016_001.png");
    ObjectToolbox::sharedState()->addObject(1980, "blockPiece_017_001.png");
    ObjectToolbox::sharedState()->addObject(1981, "blockPiece_018_001.png");
    ObjectToolbox::sharedState()->addObject(1982, "blockPiece_019_001.png");
    ObjectToolbox::sharedState()->addObject(1983, "blockPiece_020_001.png");
    ObjectToolbox::sharedState()->addObject(1984, "blockPiece_021_001.png");
    ObjectToolbox::sharedState()->addObject(1985, "blockPiece_022_001.png");
    ObjectToolbox::sharedState()->addObject(1986, "blockPiece_023_001.png");
    ObjectToolbox::sharedState()->addObject(1987, "blockPiece_024_001.png");

    ObjectToolbox::sharedState()->addObject(1988, "blockPiece_small_001_001.png");
    ObjectToolbox::sharedState()->addObject(1989, "blockPiece_small_002_001.png");
    ObjectToolbox::sharedState()->addObject(1990, "blockPiece_small_003_001.png");
    ObjectToolbox::sharedState()->addObject(1991, "blockPiece_small_004_001.png");
    ObjectToolbox::sharedState()->addObject(1992, "blockPiece_small_005_001.png");
    ObjectToolbox::sharedState()->addObject(1993, "blockPiece_small_006_001.png");
    ObjectToolbox::sharedState()->addObject(1994, "blockPiece_small_007_001.png");
    ObjectToolbox::sharedState()->addObject(1995, "blockPiece_small_008_001.png");
    ObjectToolbox::sharedState()->addObject(1996, "blockPiece_small_009_001.png");
    ObjectToolbox::sharedState()->addObject(1997, "blockPiece_small_010_001.png");
    ObjectToolbox::sharedState()->addObject(1998, "blockPiece_small_011_001.png");
    ObjectToolbox::sharedState()->addObject(1999, "blockPiece_small_012_001.png");
    ObjectToolbox::sharedState()->addObject(2000, "blockPiece_small_013_001.png");
    ObjectToolbox::sharedState()->addObject(2001, "blockPiece_small_014_001.png");
    ObjectToolbox::sharedState()->addObject(2002, "blockPiece_small_015_001.png");
    ObjectToolbox::sharedState()->addObject(2003, "blockPiece_small_016_001.png");
    ObjectToolbox::sharedState()->addObject(2004, "blockPiece_small_017_001.png");
    ObjectToolbox::sharedState()->addObject(2005, "blockPiece_small_018_001.png");
    ObjectToolbox::sharedState()->addObject(2006, "blockPiece_small_019_001.png");
    ObjectToolbox::sharedState()->addObject(2007, "blockPiece_small_020_001.png");
    ObjectToolbox::sharedState()->addObject(2008, "blockPiece_small_021_001.png");
    ObjectToolbox::sharedState()->addObject(2009, "blockPiece_small_022_001.png");
    ObjectToolbox::sharedState()->addObject(2010, "blockPiece_small_023_001.png");
    ObjectToolbox::sharedState()->addObject(2011, "blockPiece_small_024_001.png");

    return TRUE;
}