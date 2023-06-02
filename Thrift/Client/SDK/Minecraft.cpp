#include "Minecraft.h"
#include "../Utils/Render/RenderUtils.h"

ClientInstance* Minecraft::ci = nullptr;
MinecraftUIRenderContext* Minecraft::renderCtx = nullptr;

auto Minecraft::getClientInstance(void) -> ClientInstance* {

	return Minecraft::ci;

};

auto Minecraft::setClientInstance(ClientInstance* ptr) -> void {

	if (ptr == nullptr)
		return;

	Minecraft::ci = ptr;

};

auto Minecraft::getRenderContext(void) -> MinecraftUIRenderContext* {

	return Minecraft::renderCtx;

};

auto Minecraft::setRenderContext(MinecraftUIRenderContext* ptr) -> void {

	if (ptr == nullptr)
		return;

	Minecraft::renderCtx = ptr;
	RenderUtils::context = ptr;
};