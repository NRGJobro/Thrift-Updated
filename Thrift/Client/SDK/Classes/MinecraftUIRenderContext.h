#pragma once

#include "ClientInstance.h"
#include "../../Utils/Utils.h"

class TextMeasureData {
public:
    float scale;
public:
    TextMeasureData(float scale = 1.f) {
        this->scale = scale;
    };
};

class CaretMeasureData {
public:
    int a;
    int b;
public:
    CaretMeasureData(int paramA = 0xFFFFFFFF, bool paramB = false) {
        this->a = paramA;
        this->b = paramB;
    };
};

class Rect : public Vec4<float> {
public:
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;
    float w = 0.f;
public:
    Rect(float top = 0.f, float left = 0.f, float right = 0.f, float bottom = 0.f) {
        this->x = top;
        this->y = left;
        this->z = right;
        this->w = bottom;
    };
public:
    auto get(void) -> float* {
        float v[] = { this->x, this->y, this->z, this->w };
        return v;
    };
};

class Color {
public:
    float r = 255.f;
    float g = 255.f;
    float b = 255.f;
    float a = 1.f;
public:
    Color(float r = 255.f, float g = 255.f, float b = 255.f, float a = 1.f) {
        this->r = r / 255.f;
        this->g = g / 255.f;
        this->b = b / 255.f;
        this->a = a;
    };
public:
    auto get(void) -> float* {
        float v[] = { this->r, this->g, this->b, this->a };
        return v;
    };
};

class MinecraftUIRenderContext {
public:
	ClientInstance* clientInstance;
private:
    virtual ~MinecraftUIRenderContext();
public:
    virtual auto getLineLength(class Font*, std::string*, float, bool) -> float;
    virtual auto getTextAlpha(void) -> float;
    virtual auto setTextAlpha(float) -> void;
    virtual auto drawDebugText(const float*, std::string*, const float*, float, unsigned int, float*, void*) -> __int64;
    virtual auto drawText(Font*, const float*, std::string*, const float*, float, unsigned int, const TextMeasureData*, const CaretMeasureData*) -> __int64;
    virtual auto flushText(float) -> void;
    virtual auto drawImage(std::string*, Vec2<float>*, Vec2<float>*, Vec2<float>*, Vec2<float>*, bool, const float*, float) -> __int64;
private:
    //virtual auto Function7(void) -> void;
    virtual auto Function8(void) -> void;
    virtual auto Function9(void) -> void;
    virtual auto Function10(void) -> void;
    virtual auto Function11(void) -> void;
public:
    virtual auto drawRectangle(const float*, const float*, float, int) -> void;
    virtual auto fillRectangle(const float*, const float*, float) -> void;
public:
    auto drawText(Font*, Vec2<float>, std::string, Color, float) -> void;
    auto getTextLen(Font*, std::string, float) -> float;
public:
    auto drawRectangle(Rect, Color, int) -> void;
    auto fillRectangle(Rect, Color) -> void;
};