#include "ModUtils.hpp"
#include "HooksUtils.hpp"
#include "customLayerxd.hpp"
using namespace cocos2d;
using namespace extension;

class ButtonSprite : public gd::ButtonSprite {};
class CreatedLabelController : public CCLabelBMFont {
public:
    void labelCustomSetups(float) {
        if (!dynamic_cast<CCLabelBMFont*>(this)) return;
        if (std::string(this->getString()) == "Help") {
            if (auto pButtonSprite = dynamic_cast<ButtonSprite*>(this->getParent()); pButtonSprite) {
                pButtonSprite->runAction(CCRepeatForever::create(
                    CCSequence::create(
                        CCEaseSineInOut::create(CCScaleTo::create(1.f, pButtonSprite->getScale() + 0.03f)),
                        CCEaseSineInOut::create(CCScaleTo::create(1.f, pButtonSprite->getScale()/* + 0.1f*/)),
                        nullptr
                    )
                ));
            }
        }
    }
};
CCLabelBMFont* (__cdecl* CCLabelBMFont_create)(const char*, const char*);
CCLabelBMFont* CCLabelBMFont_create_H(const char* str, const char* fntFile) {
    auto rtn = CCLabelBMFont_create(str, fntFile);
    if (rtn) rtn->scheduleOnce(schedule_selector(CreatedLabelController::labelCustomSetups), 0.001f);
    return rtn;
}

inline gd::GJDropDownLayer* (__cdecl* SupportLayer_customSetup)(gd::GJDropDownLayer*);
void __fastcall SupportLayer_customSetup_H(gd::GJDropDownLayer* self) {
    SupportLayer_customSetup(self);

    self->m_pLayer->removeChild((CCSprite*)self->m_pLayer->getChildren()->objectAtIndex(6), false);//developedBy
    self->m_pLayer->removeChild((CCSprite*)self->m_pLayer->getChildren()->objectAtIndex(6), false);//poweredBy

    CCMenu* menu = (CCMenu*)self->m_pLayer->getChildren()->objectAtIndex(8);
    menu->removeAllChildren();

    auto developersLabel = gd::CCMenuItemSpriteExtra::create(ModUtils::createSprite("developersLabel.png"), self, menu_selector(customLayerxd::switchcustomLayerxdbtn));
    developersLabel->m_bAnimationEnabled = false;
    developersLabel->m_bColorEnabled = true;//yo
    developersLabel->setPosition({ 0, -20 });
    menu->addChild(developersLabel);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;
    MH_Initialize();
    HOOK(gd::base + 0x25C7B0, SupportLayer_customSetup);
    CC_HOOK("?create@CCLabelBMFont@cocos2d@@SAPAV12@PBD0@Z", CCLabelBMFont_create);
    return TRUE;
}