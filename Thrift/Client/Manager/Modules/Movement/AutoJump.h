#pragma once

#include "../../Module.h"

class AutoJump : public Module {
public:
	AutoJump(Category* c) : Module(c, "AutoJump", "Makes the player jump automaticly") {
		this->key = 'I';
	};

	auto onTick(void) -> void {
		auto instance = Minecraft::getClientInstance();
		auto player = (instance != nullptr ? instance->LocalPlayer : nullptr);

		if (player != nullptr)
			player->getMovementProxy()->setJumping(true);
	};
};