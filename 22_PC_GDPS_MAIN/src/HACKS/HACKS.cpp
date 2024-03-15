#include "ModUtils.hpp"
#include "HooksUtils.hpp"
using namespace cocos2d;
using namespace extension;
using namespace gd;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;
    //cant fuck dlux
        // Address	Length	Original bytes	Patched bytes
            /*100C5711	0x1	A1 	B8
            100C5716	0x1	05 	B8
            100C5718	0x2	55 18 	00 00*/

            // Level Completion
    ModUtils::WriteProcMem(base + 0x1FD557, { 0xEB, 0x0C, }, "Level Completion 1");
    ModUtils::WriteProcMem(base + 0x1FD742, { 0xC7, 0x87, 0xE0, 0x02, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xC7, 0x87, 0xE4, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }, "Correction");
    ModUtils::WriteProcMem(base + 0x1FD756, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }, "Level Completion 2");
    ModUtils::WriteProcMem(base + 0x1FD79A, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }, "Level Completion 3");
    ModUtils::WriteProcMem(base + 0x1FD7AF, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }, "Level Completion 4");
    // Load Failed
    ModUtils::WriteProcMem(base + 0x18B2B4, { 0xB0 , 0x01 }, "Load Failed");
    //Rotation Hack
    ModUtils::WriteProcMem(base + 0x85CBC, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 }, "Rotation Hack 1");
    ModUtils::WriteProcMem(base + 0x8BDDD, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 }, "Rotation Hack 2");
    ModUtils::WriteProcMem(base + 0x8BE16, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 }, "Rotation Hack 3");
    ModUtils::WriteProcMem(base + 0xECA3D, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 }, "Rotation Hack 4");
    ModUtils::WriteProcMem(base + 0xEE5A9, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 }, "Rotation Hack 5");
    ModUtils::WriteProcMem(base + 0x20181E, { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90 }, "Rotation Hack 6");
    //DefaultSongBypass
    ModUtils::WriteProcMem(base + 0x174407, { 0x90, 0x90 }, "DefaultSongBypass 1");
    ModUtils::WriteProcMem(base + 0x174411, { 0x90, 0x90, 0x90 }, "DefaultSongBypass 2");
    ModUtils::WriteProcMem(base + 0x174456, { 0x90, 0x90 }, "DefaultSongBypass 3");
    ModUtils::WriteProcMem(base + 0x174460, { 0x90, 0x90, 0x90 }, "DefaultSongBypass 4");
    //Allows you to scroll out the editor
    ModUtils::WriteProcMem(base + 0x8FAAC, { 0xEB }, "scroll out editor 1");
    ModUtils::WriteProcMem(base + 0x8FA95, { 0xEB }, "scroll out editor 2");
    ModUtils::WriteProcMem(base + 0x8FAC5, { 0xEB }, "scroll out editor 3");
    ModUtils::WriteProcMem(base + 0x8FADC, { 0xEB }, "scroll out editor 4");
    //ZoomInBypass
    ModUtils::WriteProcMem(base + 0x87801, { 0x90, 0x90, 0x90 }, "ZoomInBypass 1");
    ModUtils::WriteProcMem(base + 0x87806, { 0x90, 0x90, 0x90 }, "ZoomInBypass 2");
    //SmoothEditorTrail
    ModUtils::WriteProcMem(base + 0x16AB0D, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }, "SmoothEditorTrail");
    //Music Sync Correction
    ModUtils::WriteProcMem(base + 0x208808, { 0xEB, 0x08 }, "Music Sync Correction");
    return TRUE;
}