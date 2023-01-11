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
		GetLocalPlayer _GetLocalPlayer = (GetLocalPlayer)(this->VTable[24]);
		return _GetLocalPlayer(this);
	};
public:
	BUILD_ACCESS(class LoopbackPacketSender*, LoopbackPacketSender, 0xE0);
	BUILD_ACCESS(class MinecraftGame*, MinecraftGame, 0xB8);
	BUILD_ACCESS(class MoveInputHandler*, MoveInputHandler, 0xF8);
public:
	AS_FIELD(class Player*, LocalPlayer, getLocalPlayer);
};