#pragma once
#include "22_PC_GDPS_MAIN.h"

class PlayLayerExt : public PlayLayer {
public:
    static void updateByGamePlayOptins(PlayLayer* self);
    void schNoResstartFix(float);//im crying watching this old code
    void schFreeModeCameraShit(float);//im crying watching this old code
    void schFreeModeCameraSync(float);//im crying watching this old code

    inline static PlayLayerExt* PlayLayerFromINit;
    inline static bool freeMode = false;
    CCNode* cameraleadshit;
    inline static bool isSwingCopterMode = false;
};

void CreatePlayLayerHooks();
void CreatePlayerObjectHooks();