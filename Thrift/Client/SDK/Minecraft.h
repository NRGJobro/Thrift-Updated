#pragma once

#include "Classes/MinecraftUIRenderContext.h"

class Minecraft {
private:
	static ClientInstance* ci;
	static MinecraftUIRenderContext* renderCtx;
public:
	static auto getClientInstance(void)->ClientInstance*;
	static auto setClientInstance(ClientInstance*)->void;
	static auto getRenderContext(void) -> MinecraftUIRenderContext*;
	static auto setRenderContext(MinecraftUIRenderContext*) -> void;
};