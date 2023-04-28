#pragma once

#include "../../Utils/Utils.h"

#include "LoopbackPacketSender.h"
#include "MoveInputHandler.h"
#include "MinecraftGame.h"
#include "Player.h"

class ClientInstance {
private:
	uintptr_t** VTable;
public:
	auto getLocalPlayer(void) -> class Player* {
		using GetLocalPlayer = Player * (__thiscall*)(ClientInstance*);
		GetLocalPlayer _GetLocalPlayer = (GetLocalPlayer)(this->VTable[25]);
		return _GetLocalPlayer(this);
	};
public:
	BUILD_ACCESS(class LoopbackPacketSender*, LoopbackPacketSender, 0xD0);//Not sure but should be it (I hope)
	BUILD_ACCESS(class MinecraftGame*, MinecraftGame, 0xB0);
	BUILD_ACCESS(class MoveInputHandler*, MoveInputHandler, 0x108);
public:
	AS_FIELD(class Player*, LocalPlayer, getLocalPlayer);
};