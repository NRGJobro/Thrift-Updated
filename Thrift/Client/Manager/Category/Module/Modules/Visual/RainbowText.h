#pragma once

#include "../../Module.h"

class RainbowText : public Module {
public:
	RainbowText(Category* c) : Module(c, "RainbowText") {
		
		this->isEnabled = true;

	};
public:
	auto onDrawText(MinecraftUIRenderContext*, Font*, float*, std::string*, float*, float, unsigned int, const TextMeasureData*, const CaretMeasureData*) -> void override;
public:
	float rcolors[4];
};