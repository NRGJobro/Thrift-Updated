#pragma once

#include "../../Module.h"

class AirJump : public Module {
public:
	AirJump(Category* c) : Module(c, "AirJump", "Allows the player to jump on air") {
		this->key = 'R';
	};
	
	auto onTick(void) -> void {
		auto instance = Minecraft::getClientInstance();
		auto player = (instance != nullptr ? instance->LocalPlayer : nullptr);

		if (player != nullptr);
			//	player->getMovementProxy()->setOnGround(true); we dont have movement proxy rn, and i dont wanna give entt out yet, so nrg will have to add a sig
	}
};