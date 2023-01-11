#pragma once

#include "Classes/MinecraftUIRenderContext.h"

class Minecraft {
private:
	static ClientInstance* ci;
public:
	static auto getClientInstance(void)->ClientInstance*;
	static auto setClientInstance(ClientInstance*)->void;
};