#pragma once

#include "../../Module.h"

class TestModule : public Module {
public:
	TestModule(Category* c) : Module(c, "Test Module", "For testing shiz") {

		this->isEnabled = false;
		this->debugState = true;
		this->key = 'G';

	};
public:
	auto onTick(void) -> void override;
	auto onEnable(void) -> void override;
	auto onDisable(void) -> void override;
public:
	auto onRender(MinecraftUIRenderContext*) -> void override;
	auto onImGuiRender() -> void override;
	auto onKey(uint64_t, bool, bool*) -> void override;
public:
	auto onPacket(LoopbackPacketSender*, Packet*, bool*) -> void override;
};