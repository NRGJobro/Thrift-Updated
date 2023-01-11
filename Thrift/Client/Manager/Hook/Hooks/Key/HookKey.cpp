#include "HookKey.h"

#include "../../../Category/Module/Module.h"
#include "../../../Manager.h"

Manager* kMgr = nullptr;

typedef void(__thiscall* Key) (uint64_t, bool);
Key _Key;

auto KeyHookCallback(uint64_t key, bool isDown) -> void {

	bool cancel = false;

	if (kMgr != nullptr) {

		auto instance = Minecraft::getClientInstance();
		auto mcgame = (instance != nullptr ? instance->MinecraftGame : nullptr);

		if (key == VK_END) kMgr->isRunning = false;

		for (auto category : kMgr->categories) {

			for (auto mod : category->modules) {

				if (isDown && mcgame != nullptr && mcgame->canUseKeys)
					if (mod->key == key)
						mod->isEnabled = !mod->isEnabled;

				if (mod->isEnabled)
					mod->onKey(key, isDown, &cancel);

			};

		};

	};

	if(!cancel)
		_Key(key, isDown);

};

auto Hook_Key::init(void) -> StatusData {

	kMgr = this->mgr;
	auto sig = Utils::findSig("48 ? ? 48 ? ? ? 4C 8D 05 ? ? ? ? 89");

	if (!sig)
		return StatusData(MethodStatus::Error, "[Key Hook] Failed to find Signature!");

	if(MH_CreateHook((void*)sig, &KeyHookCallback, reinterpret_cast<LPVOID*>(&_Key)) != MH_OK)
		return StatusData(MethodStatus::Error, "[Key Hook] Failed to create hook!");

	if (MH_EnableHook((void*)sig) != MH_OK)
		return StatusData(MethodStatus::Error, "[Key Hook] Failed to enable hook!");

	return StatusData(MethodStatus::Success, "[Key Hook] Successfully hooked Key Hook!");

};