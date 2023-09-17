#pragma once

#include "../../Module.h"

class RainbowText : public Module {
public:
	RainbowText(Category* c) : Module(c, "RainbowText", "Makes text rainbow") {
		
		this->isEnabled = true;

	};
public:
	auto onDrawText(MinecraftUIRenderContext* ctx, Font* font, float* pos, std::string* text, float* color, float alpha, unsigned int textAlignment, const TextMeasureData* textMeasureData, const CaretMeasureData* caretMeasureData) -> void {
		if (rcolors[3] < 1) {

			rcolors[0] = 0.2f;
			rcolors[1] = 0.2f;
			rcolors[2] = 1.f;
			rcolors[3] = 1;

		};

		Utils::ApplyRainbow(rcolors, 0.00015f);

		for (auto I = 0; I < 4; I++)
			color[I] = rcolors[I];
	};
public:
	float rcolors[4];
};