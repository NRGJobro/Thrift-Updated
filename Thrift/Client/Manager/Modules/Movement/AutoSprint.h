#pragma once

#include "../../Module.h"

class AutoSprint : public Module {
public:
	AutoSprint(Category* c) : Module(c, "AutoSprint", "Automaticly makes player sprint") {
		this->isEnabled = true;
	};

	auto onTick(void) -> void {
		auto instance = Minecraft::getClientInstance();
		auto player = (instance != nullptr ? instance->LocalPlayer : nullptr);
		if (player == nullptr) return;
		auto input = instance->getMoveInputHandler;
		if (instance->getMoveInputHandler->isSneakDown) return;
		
		if ((input->forwardMovement > 0 || ((input->forwardMovement || input->sideMovement))))
			player->getMovementProxy()->setSprinting(true);
	};
};