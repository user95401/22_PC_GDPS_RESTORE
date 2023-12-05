#include "hooks.hpp"

#include <iostream>
#include <cstdio>
#include <string>
#include <format>
bool hook::create(LPVOID target, LPVOID hook, LPVOID* original, bool immediately) {

	if(immediately==false){
		std::random_device os_seed;
		const unsigned int seed = os_seed();
		std::mt19937 generator(seed);
		std::uniform_int_distribution<int> distribute(250, 1000);
		int sleepMs = distribute(generator);
		Sleep(sleepMs);
	}

	MH_STATUS hook_status = MH_CreateHook(target, hook, original);

	printf((std::format("{:x}", ((DWORD)target - reinterpret_cast<uintptr_t>(GetModuleHandle(0)))) + std::string(" [hook]: ") + MH_StatusToString(hook_status) + "\n").c_str());

	if (hook_status != MH_STATUS::MH_OK) {
		MessageBoxA(nullptr, "something went wrong when attempting to hook function...", "MinHook", MB_ICONERROR | MB_OK);
		return false;
	}

	return MH_EnableHook(target) == MH_STATUS::MH_OK;
}

const char* Made_with_curly_eureka_by_user666 = "Made with curly-eureka by user666. :>";