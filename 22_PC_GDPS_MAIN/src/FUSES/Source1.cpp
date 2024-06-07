#include "ModUtils.hpp"
#include "HooksUtils.hpp"
#include "gd.h"
using namespace cocos2d;
using namespace extension;
using namespace gd;

CCSprite* (__cdecl* CCSprite_create)(const char*);
CCSprite* (__cdecl* CCSprite_createWithSpriteFrameName)(const char*);

CCSprite* CCSprite_create_H(const char* name) {
    auto rtn = CCSprite_create(name);
    bool isSaiModPackResourceTest = strstr(name, "streak_");
    if (!rtn and not isSaiModPackResourceTest) {
        ModUtils::log(std::format("{} was pPlaceholderSpriteD", name));
        auto pPlaceholderSprite = CCSprite_createWithSpriteFrameName("d_sign_img_04_001.png");
        return pPlaceholderSprite;
    };
    return rtn;
}
CCSprite* CCSprite_createWithSpriteFrameName_H(const char* name) {
    auto rtn = CCSprite_createWithSpriteFrameName(name);
    bool isSaiModPackResourceTest = { (
        strstr(name, "player_")
        or strstr(name, "ship_")
        or strstr(name, "bird_")
        or strstr(name, "dart_")
        or strstr(name, "robot_")
        or strstr(name, "spider_")
        ) };
    if (!rtn and not isSaiModPackResourceTest) {
        ModUtils::log(std::format("{} was pPlaceholderSpriteD", name));
        auto pPlaceholderSprite = CCSprite_createWithSpriteFrameName("d_sign_img_04_001.png");
        return pPlaceholderSprite;
    };
    return rtn;
}

long __stdcall VectoredExceptionHandler(_EXCEPTION_POINTERS* pExceptInfo) {
    //what
    std::stringstream buffer;
    DWORD exc_code = pExceptInfo->ExceptionRecord->ExceptionCode;
    bool dontfuckingcare = false;
    switch (exc_code) {
    case EXCEPTION_ACCESS_VIOLATION:
        buffer << "EXCEPTION_ACCESS_VIOLATION...";
        break;
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
        buffer << "EXCEPTION_ARRAY_BOUNDS_EXCEEDED";
        break;
    case EXCEPTION_BREAKPOINT:
        buffer << "EXCEPTION_BREAKPOINT";
        dontfuckingcare = true;
        break;
    case EXCEPTION_DATATYPE_MISALIGNMENT:
        buffer << "EXCEPTION_DATATYPE_MISALIGNMENT";
        break;
    case EXCEPTION_FLT_DENORMAL_OPERAND:
        buffer << "EXCEPTION_FLT_DENORMAL_OPERAND";
        break;
    case EXCEPTION_FLT_DIVIDE_BY_ZERO:
        buffer << "EXCEPTION_FLT_DIVIDE_BY_ZERO";
        break;
    case EXCEPTION_FLT_INEXACT_RESULT:
        buffer << "EXCEPTION_FLT_INEXACT_RESULT";
        break;
    case EXCEPTION_FLT_INVALID_OPERATION:
        buffer << "EXCEPTION_FLT_INVALID_OPERATION";
        break;
    case EXCEPTION_FLT_OVERFLOW:
        buffer << "EXCEPTION_FLT_OVERFLOW";
        break;
    case EXCEPTION_FLT_STACK_CHECK:
        buffer << "EXCEPTION_FLT_STACK_CHECK";
        break;
    case EXCEPTION_FLT_UNDERFLOW:
        buffer << "EXCEPTION_FLT_UNDERFLOW";
        break;
    case EXCEPTION_ILLEGAL_INSTRUCTION:
        buffer << "EXCEPTION_ILLEGAL_INSTRUCTION";
        break;
    case EXCEPTION_IN_PAGE_ERROR:
        buffer << "EXCEPTION_IN_PAGE_ERROR";
        break;
    case EXCEPTION_INT_DIVIDE_BY_ZERO:
        buffer << "EXCEPTION_INT_DIVIDE_BY_ZERO";
        break;
    case EXCEPTION_INT_OVERFLOW:
        buffer << "EXCEPTION_INT_OVERFLOW";
        break;
    case EXCEPTION_INVALID_DISPOSITION:
        buffer << "EXCEPTION_INVALID_DISPOSITION";
        break;
    case EXCEPTION_NONCONTINUABLE_EXCEPTION:
        buffer << "EXCEPTION_NONCONTINUABLE_EXCEPTION";
        break;
    case EXCEPTION_PRIV_INSTRUCTION:
        buffer << "EXCEPTION_PRIV_INSTRUCTION";
        break;
    case EXCEPTION_SINGLE_STEP:
        buffer << "EXCEPTION_SINGLE_STEP";
        break;
    case EXCEPTION_STACK_OVERFLOW:
        buffer << "EXCEPTION_STACK_OVERFLOW";
        break;
    case DBG_PRINTEXCEPTION_WIDE_C:
        buffer << "DBG_PRINTEXCEPTION_WIDE_C";
        dontfuckingcare = true;
        break;
    case DBG_PRINTEXCEPTION_C:
        buffer << "DBG_PRINTEXCEPTION_C";
        dontfuckingcare = true;
        break;
    case 0xe06d7363:
        buffer << "0xe06d7363";
        dontfuckingcare = true;
        break;
    default:
        buffer << "0x" << std::hex << exc_code;
        break;
    }
    //ModUtils::log(buffer.str());
    if (not dontfuckingcare) {
        auto msg = std::format( "OH SHED U GOT {} :3", buffer.str() );
        ModUtils::log(msg);
        SetGameWindowTitle(msg.c_str());
        //save game?
        GameManager::sharedState()->save();
        //level editor tries
        auto pLevelEditorLayer = GameManager::sharedState()->getEditorLayer();
        if (pLevelEditorLayer) EditorPauseLayer::create(pLevelEditorLayer)->saveLevel();
    };
    //rtn
    return EXCEPTION_EXECUTE_HANDLER;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call != DLL_PROCESS_ATTACH) return TRUE;
    AddVectoredExceptionHandler(0, VectoredExceptionHandler);//:3
    MH_Initialize();
    CC_HOOK("?create@CCSprite@cocos2d@@SAPAV12@PBD@Z", CCSprite_create);
    CC_HOOK("?createWithSpriteFrameName@CCSprite@cocos2d@@SAPAV12@PBD@Z", CCSprite_createWithSpriteFrameName);
    return TRUE;
}