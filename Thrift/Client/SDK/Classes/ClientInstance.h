#pragma once

#include "../../Utils/Utils.h"

#include "LoopbackPacketSender.h"
#include "MoveInputHandler.h"
#include "MinecraftGame.h"
#include "Player.h"
#include "GuiData.h"
#include "Actor.h"

#define disableInputIndex 331 // Updated to 1.20.81
#define getLocalPlayerIndex 29

class ClientInstance {
private:
	uintptr_t** VTable;

public:
	Player* getLocalPlayer() {
		return (Player*)Utils::CallVFunc<getLocalPlayerIndex, Player*>(this); // 1.20.80
	}


	BlockSource* getBlockSource() {
		return Utils::CallVFunc<28, BlockSource*>(this); // 1.20.71
	}

	auto setDisableInput(bool disable) -> void {
		Utils::CallVFunc<disableInputIndex, __int64>(this, disable); //maybe bad // Updated to 1.20.81
	}


	auto grabMouse() -> void {
		Utils::CallVFunc<332, __int64>(this); //326 // BROKEN in 1.21
	}

	auto releaseMouse() -> void {
		Utils::CallVFunc<333, __int64>(this); //327 BROKEN in 1.21
	}




public:
	BUILD_ACCESS(class LoopbackPacketSender*, LoopbackPacketSender, 0xF0); // Updated to 1.20.71 
	BUILD_ACCESS(class MinecraftGame*, MinecraftGame, 0xC8); // Updated to 1.20.71
	BUILD_ACCESS(class GuiData*, GuiData, 0x558); // Updated to 1.20.81 
public:
	AS_FIELD(class Player*, LocalPlayer, getLocalPlayer);
};