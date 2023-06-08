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
	auto sig = Utils::findSig("48 8D 05 ? ? ? ? 48 89 01 48 8B C3 48 89 51");//Idk the new one

	if(!sig)
		return StatusData(MethodStatus::Error, "[LoopbackPacketSender::send Hook] Failed to find Signature!");

	auto offset = *(int*)(sig + 3);
	auto VTable = reinterpret_cast<uintptr_t**>(sig + offset + 7);

	if(MH_CreateHook((void*)VTable[1], &SendCallback, reinterpret_cast<LPVOID*>(&_Send)) != MH_OK)
		return StatusData(MethodStatus::Error, "[LoopbackPacketSender::send Hook] Failed to create hook!");

	if (MH_EnableHook((void*)VTable[1]) != MH_OK)
		return StatusData(MethodStatus::Error, "[LoopbackPacketSender::send Hook] Failed to enable hook!");

	return StatusData(MethodStatus::Success, "[LoopbackPacketSender::send Hook] Successfully hooked!");

};