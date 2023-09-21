#pragma once

#include "../../Module.h"

class Antivoid : public Module {
public:
Antivoid(Category* c) : Module(c, "Antivoid", "Teleports the player back to spawn if they fall into the void") {
this->key = 'V';
};

auto onTick(void) -> void {
	auto instance = Minecraft::getClientInstance();
	auto player = (instance != nullptr ? instance->LocalPlayer : nullptr);

	if (player != nullptr) {
		// Check if the player is falling into the void
		if (player->getY() < 0.0f) {
			// Teleport the player back to spawn
			player->setPosition(instance->getServer()->getSpawnPoint(), true);
		}
	}
};
};
