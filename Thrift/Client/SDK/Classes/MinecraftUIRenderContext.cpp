#include "MinecraftUIRenderContext.h"

auto MinecraftUIRenderContext::drawText(Font* font, Vec2<float> textPos, std::string text, Color color, float fontSize) -> void {

	if (font == nullptr) {

		auto instance = this->clientInstance;
		auto mcgame = (instance != nullptr ? instance->MinecraftGame : nullptr);
		font = (mcgame != nullptr ? mcgame->mcfont : nullptr);

	};

	if (font == nullptr)
		return;

	TextMeasureData textMeasureData = TextMeasureData(fontSize);
	CaretMeasureData caretMeasureData = CaretMeasureData();
	
	auto textRect = Rect(textPos.x, textPos.x + (textPos.x * fontSize), textPos.y, textPos.y + (textPos.y * fontSize / 2));
	this->drawText(font, textRect.get(), &text, color.get(), color.a, 0, &textMeasureData, &caretMeasureData);

};

auto MinecraftUIRenderContext::getTextLen(Font* font, std::string text, float fontSize) -> float {

	if (font == nullptr) {

		auto instance = this->clientInstance;
		auto mcgame = (instance != nullptr ? instance->MinecraftGame : nullptr);
		font = (mcgame != nullptr ? mcgame->mcfont : nullptr);

	};

	if (font == nullptr)
		return 0.f;

	return this->getLineLength(font, &text, fontSize, false);

};

auto MinecraftUIRenderContext::drawRectangle(Rect rect, Color color, int lineWidth) -> void {

	rect = Rect(rect.x, rect.z, rect.y, rect.w);
	this->drawRectangle(rect.get(), color.get(), color.a, lineWidth);

};

auto MinecraftUIRenderContext::fillRectangle(Rect rect, Color color) -> void {

	rect = Rect(rect.x, rect.z, rect.y, rect.w);
	this->fillRectangle(rect.get(), color.get(), color.a);

};