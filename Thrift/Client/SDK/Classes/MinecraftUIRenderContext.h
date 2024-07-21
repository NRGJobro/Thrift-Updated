#pragma once

#include "ClientInstance.h"
#include "../../Utils/Utils.h"
#include "../../Utils/Math.h"


class TextMeasureData {
public:
    float scale;
    int idk;
    bool displayShadow;
public:
    TextMeasureData(float scale = 1.f, bool shaddow = true) {
        this->scale = scale;
        this->displayShadow = shaddow;
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

class FilePath {//I pasted
private:
    char pad_0x0[0x18];
public:
    std::string filePathStr;
};

class TexturePtr {
private:
    char pad_0x0[0x18];
public:
    FilePath* filePath;
};

enum class ResourceFileSystem : int { //nrg sent me
    UserPackage = 0x0,
    AppPackage = 0x1,
    Raw = 0x2,
    RawPersistent = 0x3,
    SettingsDir = 0x4,
    ExternalDir = 0x5,
    ServerPackage = 0x6,
    DataDir = 0x7,
    UserDir = 0x8,
    ScreenshotsDir = 0x9,
    StoreCache = 0xA,
    Invalid = 0xB,
};

class ResourceLocation
{
public:
    ResourceFileSystem type; //0x0
private:
    char fill[0x4];
public:
    std::string path; //0x8
    __int64 pathHash;
    __int64 fullHash;
public:
    ResourceLocation(ResourceFileSystem type, std::string path) {
        this->type = type;
        this->path = path;
    }

};

class MinecraftUIRenderContext {
public:
    ClientInstance* clientInstance;

private:
    virtual ~MinecraftUIRenderContext();
public:
    virtual auto getLineLength(class Font*, const std::string&, float, bool) -> float;
    virtual auto getTextAlpha(void) -> float;
    virtual auto setTextAlpha(float) -> void;
    virtual auto drawDebugText(const float*, const std::string&, const float*, float, unsigned int, float*, void*) -> __int64;
    virtual auto drawText(Font*, const float*, const std::string&, const float*, float, unsigned int, const TextMeasureData*, const CaretMeasureData*) -> __int64;
    virtual auto flushText(float) -> void;
    virtual auto drawImage(TexturePtr*, Vec2<float>*, Vec2<float>*, Vec2<float>*, Vec2<float>*) -> __int64;
private:
    //virtual auto Function7(void) -> void;
    virtual auto Function8(void) -> void;

private:
    virtual auto Function10(void) -> void;
    virtual auto Function11(void) -> void;
public:
    virtual auto drawRectangle(const float*, const float*, float, int) -> void;
    virtual auto fillRectangle(const Rect, const float*, float) -> void;
};