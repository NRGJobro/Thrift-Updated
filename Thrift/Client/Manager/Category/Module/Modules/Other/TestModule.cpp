#include "TestModule.h"
#include "../../../../Manager.h"
#include "../../../../../Client.h"
#include "../../../../Hook/Hooks/SwapChain/ImGui/imgui.h"
#include "../../../../../Utils/Render/ImGuiUtils.h"

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

auto TestModule::onImGuiRender() -> void {

    /* Execute Every MinecraftUIRenderContext Tick */

    ImGuiStyle* style = &ImGui::GetStyle();

    style->WindowPadding = ImVec2(15, 15);
    style->WindowRounding = 10.f;
    style->FramePadding = ImVec2(5, 5);
    style->FrameRounding = 6.f;
    style->ItemSpacing = ImVec2(12, 8);
    style->ItemInnerSpacing = ImVec2(8, 6);
    style->IndentSpacing = 25.0f;
    style->ScrollbarSize = 15.0f;
    style->ScrollbarRounding = 9.0f;
    style->GrabMinSize = 5.0f;
    style->GrabRounding = 3.0f;
    style->WindowTitleAlign = ImVec2(0.5, 0.5);
    style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
    style->Colors[ImGuiCol_Separator] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
    ImGuiWindowFlags TargetFlags;
    TargetFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
    if (ImGui::Begin(("TestGui"), 0, TargetFlags)) {
        ImGui::SetWindowSize(ImVec2(360.f, 430.f));
        if (ImGui::CollapsingHeader("Visuals")) {
            ImGui::Spacing();
            if (ImGui::Button("Test")) {
            }
            ImGui::Spacing();
        }
        if (ImGui::CollapsingHeader(("Aura"))) {
            ImGui::Spacing();
            if (ImGui::Button("Test")) {
            }
            ImGui::Spacing();
        }
        if (ImGui::CollapsingHeader(("Client"))) {
            ImGui::Spacing();
            if (ImGui::Button("Test")) {
            }
            ImGui::Spacing();
        }
        if (ImGui::CollapsingHeader(("Exploits"))) {
            ImGui::Spacing();
            if (ImGui::Button("Test")) {
            }
            ImGui::Spacing();
        }
    }
    ImGui::End();
    ImFont* font = ImGui::GetFont();

    ImGuiUtils::drawText(font, Vec2<float>(100,100), "Balls lmfao", Color(0.f, 0.f, 255.f, 1.f), 1.f, true);
    ImGuiUtils::renderOutlinedText("Outlined Balls lmfao", Vec2<float>(200,200), Color(255.f, 0.f, 0.f, 1.f), Color(0.f, 0.f, 0.f, 1.f), 1.f, font);
    ImGuiUtils::drawRect(Rect(100, 100, 200, 200), Color(255.f, 0.f, 255.f), 1.f, 1.f);
};

auto TestModule::onKey(uint64_t key, bool isDown, bool* cancelSend) -> void {

    /* Execute Upon Keyboard Press */

};

auto TestModule::onPacket(LoopbackPacketSender* _this, Packet* packet, bool* cancel) -> void {

    /*std::ostringstream o;
    o << std::hex << (uintptr_t)packet->VTable - (uintptr_t)(GetModuleHandleA("Minecraft.Windows.exe"));

    Utils::debugOutput("Minecraft.Windows.exe+" + o.str());*/

    if (packet->isInstanceOf<TextPacket>()) {
        auto textpacket = reinterpret_cast<TextPacket*>(packet);
    	std::string message = textpacket->message.getText();
        Utils::debugOutput("Text Packet: " + message);
    }

    //std::string name = (packet)->getName()->getText();
   // Utils::debugOutput(name);

};