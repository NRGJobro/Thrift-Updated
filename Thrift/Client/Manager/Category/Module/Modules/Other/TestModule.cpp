#include "TestModule.h"
#include "../../../../Manager.h"
#include "../../../../../Client.h"

auto TestModule::onTick(void) -> void {

    /* Execute Every Thread Tick */

};

auto TestModule::onEnable(void) -> void {

	/* Execute Upon Enable */

};

auto TestModule::onDisable(void) -> void {

    /* Execute Upon Disable */

};


auto TestModule::onRender(MinecraftUIRenderContext* ctx) -> void {

    /* Execute Every MinecraftUIRenderContext Tick */

};

auto TestModule::onKey(uint64_t key, bool isDown, bool* cancelSend) -> void {

    /* Execute Upon Keyboard Press */

};

auto TestModule::onPacket(LoopbackPacketSender* _this, Packet* packet, bool* cancel) -> void {

    /*std::ostringstream o;
    o << std::hex << (uintptr_t)packet->VTable - (uintptr_t)(GetModuleHandleA("Minecraft.Windows.exe"));

    Utils::debugOutput("Minecraft.Windows.exe+" + o.str());*/

    if (packet->VTable == TextPacket().VTable)
        Utils::debugOutput("Text Packet!");

};