#pragma once

#include "../../Utils/Utils.h"

#include "LoopbackPacketSender.h"
#include "MoveInputHandler.h"
#include "MinecraftGame.h"
#include "Player.h"
#include "GuiData.h"
#include "Actor.h"

class ClientInstance {
private:
	uintptr_t** VTable;
public:
	auto getLocalPlayer(void) -> class Player* {
		using GetLocalPlayer = Player * (__thiscall*)(ClientInstance*);
		GetLocalPlayer _GetLocalPlayer = (GetLocalPlayer)(this->VTable[27]);
		return _GetLocalPlayer(this);
	};

	auto getMoveTurnInput() -> class MoveInputHandler* {
		auto* player = this->getLocalPlayer();
		using MoveInputComponent_try_get = class MoveInputHandler* (__cdecl*)(void*, EntityId*);
		static MoveInputComponent_try_get MoveInputComponent_try_getFunc = reinterpret_cast<MoveInputComponent_try_get>(Utils::findSig("40 53 48 83 EC 20 48 8B DA BA 2E CD 8B 46"));//dont mind shit sig :heart:
		auto registryBase = *reinterpret_cast<void**>(player->entityContext.registry);
		EntityId entityId = player->entityContext.id;
		return MoveInputComponent_try_getFunc(registryBase, &entityId);
	}
public:
	BUILD_ACCESS(class LoopbackPacketSender*, LoopbackPacketSender, 0xF0);//Good as of 1.20
	BUILD_ACCESS(class MinecraftGame*, MinecraftGame, 0xC8); //Good as of 1.20
	BUILD_ACCESS(class GuiData*, GuiData, 0x510);//Good as of 1.20
public:
	AS_FIELD(class Player*, LocalPlayer, getLocalPlayer);
	AS_FIELD(class MoveInputHandler*, getMoveInputHandler, getMoveTurnInput);
};