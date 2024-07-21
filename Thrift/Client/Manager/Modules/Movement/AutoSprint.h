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
	//	auto input = instance->getMoveInputHandler;    moveinputhandler has been broken since forever.
	//	if (instance->getMoveInputHandler->isSneakDown) return;       moveinputhandler has been broken since forever.
		
	//	if ((input->forwardMovement > 0 || ((input->forwardMovement || input->sideMovement))))
		//	player->getMovementProxy()->setSprinting(true); 		// we dont have movement proxy rn, and i dont wanna give entt out yet, so nrg will have to add a sig
	};
};