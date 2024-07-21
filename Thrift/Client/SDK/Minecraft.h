#pragma once

#include "Classes/MinecraftUIRenderContext.h"

class Minecraft {
private:
	static ClientInstance* ci;
	static MinecraftUIRenderContext* renderCtx;
public:

	static inline Font* MinecraftFont = nullptr;
	static auto getClientInstance(void)->ClientInstance*;
	static auto setClientInstance(ClientInstance*)->void;
	static auto getRenderContext(void) -> MinecraftUIRenderContext*;
	static auto setRenderContext(MinecraftUIRenderContext*) -> void;

	static Font* getFont() {
		return MinecraftFont;
	}
};