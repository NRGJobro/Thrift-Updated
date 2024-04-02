#pragma once

#include "../../Utils/Utils.h"

#include "LoopbackPacketSender.h"
#include "MoveInputHandler.h"
#include "MinecraftGame.h"
#include "Player.h"
#include "GuiData.h"
#include "Actor.h"

#define getLocalPlayerIndex 28 // Good as of 1.20.51

class ClientInstance {
private:
	uintptr_t** VTable;
public:

	auto getLocalPlayer() -> class Player* {
		return (class Player*)Utils::CallVFunc<getLocalPlayerIndex, Player*>(this);
	}

	auto setDisableInput(bool disable) -> void {
		Utils::CallVFunc<325, __int64>(this, disable); // Good as of 1.20.51
	}

	auto releaseMouse() -> void {
		Utils::CallVFunc<326, __int64>(this); // Good as of 1.20.51
	}

	auto grabMouse() -> void {
		Utils::CallVFunc<327, __int64>(this); // Good as of 1.20.51
	}

	auto getMoveTurnInput() -> class MoveInputHandler* {
		auto* player = this->getLocalPlayer();
		using MoveInputComponent_try_get = class MoveInputHandler* (__cdecl*)(void*, EntityId*);
		static MoveInputComponent_try_get MoveInputComponent_try_getFunc = reinterpret_cast<MoveInputComponent_try_get>(Utils::findSig("40 53 48 83 EC 20 48 8B DA BA 2E CD 8B 46"));//dont mind shit sig :heart:
		auto registryBase = *reinterpret_cast<void**>(player->entityContext.registry);
		EntityId entityId = player->entityContext.id;
		return MoveInputComponent_try_getFunc(registryBase, &entityId);
	}
public:
	BUILD_ACCESS(class LoopbackPacketSender*, LoopbackPacketSender, 0xF0); // Good as of 1.20.51
	BUILD_ACCESS(class MinecraftGame*, MinecraftGame, 0xC8); // Good as of 1.20.51
	BUILD_ACCESS(class GuiData*, GuiData, 0x560); // Good as of 1.20.51
public:
	AS_FIELD(class Player*, LocalPlayer, getLocalPlayer); // Good as of 1.20.51
	AS_FIELD(class MoveInputHandler*, getMoveInputHandler, getMoveTurnInput);
};