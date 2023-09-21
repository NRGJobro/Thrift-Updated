#pragma once

#include "../../Module.h"

class Blink : public Module {
public:
	Blink(Category* c) : Module(c, "Blink", "Makes the player teleport a short distance forward") {
		this->key = 'B';
	};

private:
	float blinkDistance = 5.0f;
	long lastBlinkTime = 0;

public:
	auto onTick(void) -> void {
		auto instance = Minecraft::getClientInstance();
		auto player = (instance != nullptr ? instance->LocalPlayer : nullptr);

		if (player != nullptr) {
			// Check if the player has pressed the key and it has been at least 1 second since the last blink
			if (player->isInputActive(this->key) && GetTickCount() - lastBlinkTime >= 1000) {
				// Calculate the new player position
				Vector3 newPosition = player->getPosition() + player->getForwardVector() * blinkDistance;

				// Teleport the player to the new position
				player->setPosition(newPosition, true);

				// Update the last blink time
				lastBlinkTime = GetTickCount();
			}
		}
	};
};
