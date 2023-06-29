#include "HookLoopbackPacketSender.h"

#include "../../../Category/Module/Module.h"

#include "../../../Manager.h"
#include "../../../../Client.h"

Manager* lpMgr = nullptr;

typedef void(__thiscall* Send)(LoopbackPacketSender*, Packet*);
Send _Send;

auto SendCallback(LoopbackPacketSender* _this, Packet* packet) -> void {

	bool cancel = false;
	
	if (lpMgr != nullptr) {

		for (auto category : lpMgr->categories) {

			for (auto mod : category->modules) {

				if (mod->isEnabled)
					mod->onPacket(_this, packet, &cancel);

			};

		};

	};

	if(!cancel)
		_Send(_this, packet);

};

auto Hook_LoopbackPacketSender::init(void) -> StatusData {

	lpMgr = this->mgr;
	auto sig = Utils::findSig("48 8D 05 C1 A9 F2 02 48 8B 5C 24 30 48 89 06 33 C0 48 89 7E 20 48 89 46 28 48 89 46 30 48 89 46 38 48 89 46 40 48 89 46 48 48 89 46 50 48 89 46 58 48 8B C6 48 8B 74 24 38 48 83 C4 20 5F C3 CC 48 89 5C 24 08 57 48 83 EC 20 48 8B D9 8B FA");

	if(!addr)
            return StatusData(MethodStatus::Error, "[LoopbackPacketSender Hook] Cannot retrieve the LoopbackPacketSender vtable!");

	int offset = *reinterpret_cast<int*>(sig + 3);
	uintptr_t** VTable = addr + offset + 7;

	if(MH_CreateHook((void*)VTable[1], &SendCallback, reinterpret_cast<LPVOID*>(&_Send)) != MH_OK)
		return StatusData(MethodStatus::Error, "[LoopbackPacketSender::send Hook] Failed to create hook!");

	if (MH_EnableHook((void*)VTable[1]) != MH_OK)
		return StatusData(MethodStatus::Error, "[LoopbackPacketSender::send Hook] Failed to enable hook!");

	return StatusData(MethodStatus::Success, "[LoopbackPacketSender::send Hook] Successfully hooked!");

};
