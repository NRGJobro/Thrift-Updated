#pragma once

#include <string>
#include "../SDK/Classes/MinecraftUIRenderContext.h"

class Category;

class Module {
public:
	std::string name;
	std::string description;
	Category* category;
public:
	Module(Category*, std::string, std::string);
public:
	bool isEnabled = false, wasEnabled = false;
	uint64_t key = NULL;
public:
	bool debugState = false;
public:
	auto baseTick(void) -> void;
public:
	virtual auto onTick(void) -> void {};
	virtual auto onEnable(void) -> void {};
	virtual auto onDisable(void) -> void {};
public:
	virtual auto onImGuiRender() -> void {};
	virtual auto onRender(MinecraftUIRenderContext*) -> void {};
	virtual auto onDrawText(MinecraftUIRenderContext*, Font*, float*, std::string*, float*, float, unsigned int, const TextMeasureData*, const CaretMeasureData*) -> void {};
public:
	virtual auto onKey(uint64_t, bool, bool*) -> void {};
public:
	virtual auto onPacket(LoopbackPacketSender*, Packet*, bool*) -> void {};
};