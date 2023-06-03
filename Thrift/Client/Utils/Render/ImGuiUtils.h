#pragma once
#include "../Utils.h"
#include "../../Manager/Hook/Hooks/SwapChain/ImGui/imgui.h"
#include "RenderUtils.h"

class ImGuiUtils {
public:
	
	static __forceinline void drawText(ImFont* font, Vec2<float> textPos, std::string text, Color color, float fontSize, bool drawShadow) {
		if (!ImGui::GetCurrentContext()) return;
		const auto d = ImGui::GetBackgroundDrawList();
		if (drawShadow)
			d->AddText(font, fontSize * 22.f * (ImGui::GetIO().DisplaySize.x / RenderUtils::getScreenResolution().x), RenderUtils::scaledResToReal(Vec2<float>(textPos.x + 1.f, textPos.y + 1.f)), ImColor(50, 50, 50, (int)(color.a * 255)), text.c_str());
		d->AddText(font, fontSize * 22.f * (ImGui::GetIO().DisplaySize.x / RenderUtils::getScreenResolution().x), RenderUtils::scaledResToReal(textPos), ImColor(color.r, color.g, color.b, color.a), text.c_str());
	}
	
	static __forceinline void renderOutlinedText(std::string text, Vec2<float> textPos, Color fillColor, Color outlineColor, float textSize, ImFont* font) {
		// Calculate how much to go forward/backwards based on text size
		float backwards = -0.25f * textSize;
		float forwards = 0.5f * textSize;
		// Get rid of formatting
		std::string rt = text;
		int formatPos = rt.find("§");
		while (formatPos != std::string::npos) {
			if (rt.size() > formatPos + 2) {
				if (rt.at(formatPos + 2) != 'l') { // Don't get rid of bold
					rt.erase(formatPos - 1, 3);
				}
			}
			formatPos = rt.find("§", formatPos + 1);
		}
		// Outline the text
		ImGuiUtils::drawText(font, textPos + Vec2<float>(backwards, backwards), rt, outlineColor, textSize, false);
		ImGuiUtils::drawText(font, textPos + Vec2<float>(forwards, forwards), rt, outlineColor, textSize, false);
		ImGuiUtils::drawText(font, textPos + Vec2<float>(backwards, forwards), rt, outlineColor, textSize, false);
		ImGuiUtils::drawText(font, textPos + Vec2<float>(forwards, backwards), rt, outlineColor, textSize, false);

		// Draw text
		ImGuiUtils::drawText(font, textPos, text, fillColor, textSize, false);
	}

	static __forceinline float getTextLen(ImFont* font, std::string textStr, float textSize) {
		if (font == nullptr) font = ImGui::GetFont();
		if (!ImGui::GetCurrentContext() || !font) return 0.f;
		auto size = font->CalcTextSizeA(textSize * 22.f * (ImGui::GetIO().DisplaySize.x / RenderUtils::getScreenResolution().x), 5000.f, -1.f, textStr.c_str());
		return RenderUtils::realResToScaled(size).x;
	}

	static __forceinline float getTextHeight(std::string textStr, float textSize) {
		if (!ImGui::GetCurrentContext()) return 0.f;
		auto font = ImGui::GetFont();
		auto size = font->CalcTextSizeA(textSize * 22.f * (ImGui::GetIO().DisplaySize.x / RenderUtils::getScreenResolution().x), 5000.f, -1.f, textStr.c_str());
		return RenderUtils::realResToScaled(size).y;
	}

	static __forceinline void drawRect(Rect position, Color color, float alpha, float lineWidth) {
		if (!ImGui::GetCurrentContext()) return;
		const auto d = ImGui::GetBackgroundDrawList();
		d->AddRect(RenderUtils::scaledResToReal(Vec2<float>(position.x, position.y)), (RenderUtils::scaledResToReal(Vec2<float>(position.z, position.w))), ImColor(color.r, color.g, color.b, alpha), 0.f, 0, lineWidth);
	}

	static __forceinline void fillRectangle(Rect position, Color color) {
		if (!ImGui::GetCurrentContext()) return;
		const auto d = ImGui::GetBackgroundDrawList();
		d->AddRectFilled(RenderUtils::scaledResToReal(Vec2<float>(position.x, position.y)), (RenderUtils::scaledResToReal(Vec2<float>(position.z, position.w))), ImColor(color.r, color.g, color.b, color.a));
	}

	static __forceinline void drawLine(Vec2<float> start, Vec2<float> end, Color color, float lineWidth) {
		if (!ImGui::GetCurrentContext()) return;
		const auto d = ImGui::GetBackgroundDrawList();
		d->AddLine(RenderUtils::scaledResToReal(start), RenderUtils::scaledResToReal(end), ImColor(color.r, color.g, color.b, color.a), lineWidth);
	}
};
extern ImGuiUtils* imGuiUtils;