#pragma once
#include "22_PC_GDPS_MAIN.h"

class LevelEditor {
public:
	inline static GameObject* lastSelectedObj;
	inline static LevelEditorLayer* LevelEditorLayer_;
};

void CreateLevelEditorHooks();