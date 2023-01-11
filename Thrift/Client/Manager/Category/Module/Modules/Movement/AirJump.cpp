#include "AirJump.h"

auto AirJump::onTick(void) -> void {

	auto instance = Minecraft::getClientInstance();
	auto player = (instance != nullptr ? instance->LocalPlayer : nullptr);

	if (player != nullptr)
		player->isOnGround = true;
}