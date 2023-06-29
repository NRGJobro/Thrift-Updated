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
	auto loopbackPacketSender = Minecraft::getClientInstance()->LoopbackPacketSender;

	if(!loopbackPacketSender)
		return StatusData(MethodStatus::Error, "[LoopbackPacketSender::send Hook] ClientInstance was NULL!");

	uintptr_t** VTable = reinterpret_cast<uintptr_t**>(*(uintptr_t*)loopbackPacketSender);

	if(MH_CreateHook((void*)VTable[1], &SendCallback, reinterpret_cast<LPVOID*>(&_Send)) != MH_OK)
		return StatusData(MethodStatus::Error, "[LoopbackPacketSender::send Hook] Failed to create hook!");

	if (MH_EnableHook((void*)VTable[1]) != MH_OK)
		return StatusData(MethodStatus::Error, "[LoopbackPacketSender::send Hook] Failed to enable hook!");

	return StatusData(MethodStatus::Success, "[LoopbackPacketSender::send Hook] Successfully hooked!");

};