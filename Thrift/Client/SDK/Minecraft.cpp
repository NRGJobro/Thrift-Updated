#include "Minecraft.h"

ClientInstance* Minecraft::ci = nullptr;

auto Minecraft::getClientInstance(void) -> ClientInstance* {

	return Minecraft::ci;

};

auto Minecraft::setClientInstance(ClientInstance* ptr) -> void {

	if (ptr == nullptr)
		return;

	Minecraft::ci = ptr;

};