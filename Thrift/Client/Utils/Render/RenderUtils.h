#pragma once
#include "../Utils.h"
#include "../../Manager/Hooks/SwapChain/ImGui/imgui.h"
#include "../../SDK/Classes/MinecraftUIRenderContext.h"
#include "../../SDK/Minecraft.h"
#include "../Math.h"




class RenderUtils {
public:
	static class MinecraftUIRenderContext* context;
	static class ScreenContext* screenContext2D;
	static class ScreenContext* screenContext3D;
	static class Tessellator* Tessellator2D;
	static class Tessellator* Tessellator3D;
	static float* colorHolder;

	/* Default colors */
	static Color white;
	static Color black;
	static Color red;
	static Color lime;
	static Color blue;
	static Color yellow;
	static Color cyan;
	static Color purple;

	static __forceinline void flush() {
		context->flushText(0);
	}



	static __forceinline float getTextWidth(std::string text, float textSize, class Font* font) {
		return context->getLineLength(font, text, textSize, false);
	}

	static __forceinline float getTextHeight(class Font* font) {
		return font->getLineHeight();
	}

	static __forceinline void drawText(Font* font, Vec2<float> textPos, std::string text, Color color, float fontSize, bool shadow = false) {
		if (font == nullptr) {

			auto instance = context->clientInstance;
			auto mcgame = (instance != nullptr ? instance->MinecraftGame : nullptr);
			//font = (mcgame != nullptr ? mcgame->mcfont : nullptr);
			//font = (instance->getMinecraft() != nullptr ? instance->getMinecraft()->getFont() : nullptr);
			font = Minecraft::getFont();

		};

		if (font == nullptr)
			return;

		TextMeasureData textMeasureData = TextMeasureData(fontSize, shadow);
		CaretMeasureData caretMeasureData = CaretMeasureData();

		auto textRect = Rect(textPos.x, textPos.x + (textPos.x * fontSize), textPos.y, textPos.y + (textPos.y * fontSize / 2));
		context->drawText(font, textRect.get(), text, color.get(), color.a, 0, &textMeasureData, &caretMeasureData);
	}

	template <typename T> // not related to memory LOL
	static std::string combine(T t)
	{
		std::stringstream ss;
		ss << t;
		return ss.str();
	}

	template <typename T, typename... Args> // not related to memory LOL
	static std::string combine(T t, Args... args)
	{
		std::stringstream ss;
		ss << t << combine(args...);
		return ss.str();
	}

	static __forceinline void drawGradientText(Vec2<float> pos, std::string text, float size, float alpha, bool shadow, float speed, float saturation, float brightness, int index) {
		TextHolder str(text);
		int ind = 0;

		for (char c : std::string(str.getText()))
		{
			std::string string = combine(c, "");

			// Current color index
			int colorIndex = ind * index;

			// Get each char's width and draw
			float charWidth = getTextLen(nullptr, string, size);

			drawText(nullptr, Vec2<float>(pos.x, pos.y), string, Utils::getGoodRainbow(speed, saturation, brightness, colorIndex), size, shadow);

			// Increment the color and pos index
			pos.x += charWidth;
			++ind;
		}
	}

	static __forceinline float getTextLen(Font* font, std::string text, float fontSize) {
		if (font == nullptr) {

			auto instance = context->clientInstance;
			auto mcgame = (instance != nullptr ? instance->MinecraftGame : nullptr);
			//font = (mcgame != nullptr ? mcgame->mcfont : nullptr);
			//font = (instance->getMinecraft() != nullptr ? instance->getMinecraft()->getFont() : nullptr);
			font = Minecraft::getFont();

		};

		if (font == nullptr)
			return 0.f;

		return context->getLineLength(font, text, fontSize, false);
	}

	static __forceinline void drawRectangle(Rect rect, Color color, int lineWidth) {
		rect = Rect(rect.x, rect.z, rect.y, rect.w);
		context->drawRectangle(rect.get(), color.get(), color.a, lineWidth);
	}

	static __forceinline void fillRectangle(Rect rect, Color color, float alpha = 1.f) {
		rect = Rect(rect.x, rect.z, rect.y, rect.w);
		context->fillRectangle(rect, color.get(), alpha);
	}

	static __forceinline void renderOutlinedText(std::string text, Vec2<float> textPos, Color fillColor, Color outlineColor, float textSize, Font* font = nullptr) {
		// Calculate how much to go forward/backwards based on text size
		float backwards = -0.25f * textSize;
		float forwards = 0.5f * textSize;
		// Get rid of formatting
		std::string rt = text;
		int formatPos = (int)rt.find("�");
		while (formatPos != std::string::npos) {
			if (rt.size() > formatPos + 2) {
				if (rt.at(formatPos + 2) != 'l') { // Don't get rid of bold
					rt.erase(formatPos - 1, 3);
				}
			}
			formatPos = (int)rt.find("�", formatPos + 1);
		}
		// Outline the text
		RenderUtils::drawText(font, textPos + Vec2<float>(backwards, backwards), rt, outlineColor, textSize);
		RenderUtils::drawText(font, textPos + Vec2<float>(forwards, forwards), rt, outlineColor, textSize);
		RenderUtils::drawText(font, textPos + Vec2<float>(backwards, forwards), rt, outlineColor, textSize);
		RenderUtils::drawText(font, textPos + Vec2<float>(forwards, backwards), rt, outlineColor, textSize);
		RenderUtils::flush();

		// Draw text
		RenderUtils::drawText(font, textPos, text, fillColor, textSize);
		RenderUtils::flush();
	}

	static ImVec2 scaledResToReal(Vec2<float> scaledRes) {
		float scaledSize = *Minecraft::getClientInstance()->getGuiData()->getScale();

		return ImVec2(scaledRes.x * scaledSize, scaledRes.y * scaledSize);
	}

	static Vec2<float> realResToScaled(ImVec2 realRes) {
		auto data = Minecraft::getClientInstance()->getGuiData();
		ImVec2 actualRes = ImVec2(data->actualRes.x, data->actualRes.y);
		ImVec2 res = ImVec2(data->res.x, data->res.y);
		return Vec2<float>(realRes.x * (res.x / actualRes.x), realRes.y * (res.y / actualRes.y));
	}

	static Vec2<float> getScreenResolution() {
		RECT desktop;
		const HWND hDesktop = GetDesktopWindow();
		GetWindowRect(hDesktop, &desktop);
		return Vec2<float>((float)desktop.right, (float)desktop.bottom);
	}


};
extern RenderUtils* renderUtils;
