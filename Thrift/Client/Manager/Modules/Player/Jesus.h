#pragma once

#include "../../Module.h"

class Jesus : public Module {
public:
	Jesus(Category* c) : Module(c, "Jesus", "Allows the player to walk on water") {
		this->key = 'V';
	};

	auto onTick(void) -> void {
		auto instance = Minecraft::getClientInstance();
		auto player = (instance != nullptr ? instance->LocalPlayer : nullptr);
		if (player == nullptr) return;
		//Later
	}
};