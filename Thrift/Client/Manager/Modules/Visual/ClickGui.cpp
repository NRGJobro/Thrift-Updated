#include "ClickGui.h"
#include "../../Manager.h"
#include "../../Client.h"
#include "../../Hooks/SwapChain/ImGui/imgui.h"
#include "../../../Utils/Render/ImGuiUtils.h"
#include "../../../Utils/Render/RenderUtils.h"
#include "../../Hooks/SwapChain/ImGui/imgui_internal.h"


//giving this clickgui to the public much love from epic uwu
//i have a fix for the category pos but im lazy to add it lol


bool colorPickerOpen = false;
ImVec4 guiBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.95f);

void ClickGui::onImGuiRender() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 18.0f;

    style.Colors[ImGuiCol_WindowBg] = guiBackgroundColor;
    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_Button] = guiBackgroundColor;
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(guiBackgroundColor.x + 0.1f, guiBackgroundColor.y + 0.1f, guiBackgroundColor.z + 0.1f, guiBackgroundColor.w);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(guiBackgroundColor.x + 0.05f, guiBackgroundColor.y + 0.05f, guiBackgroundColor.z + 0.05f, guiBackgroundColor.w);

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
    style.WindowPadding = ImVec2(10, 10);

    ImGui::End();

    for (size_t i = 0; i < this->category->mgr->categories.size(); i++) {
        Category* category = this->category->mgr->categories[i];

        ImGui::SetNextWindowSize(ImVec2(200, 500));
        ImGui::Begin(category->name.c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

        ImGui::SetWindowFontScale(1.2f);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10.0f);

        /*    CATEGORY SHIT     */
        float textWidth = ImGui::CalcTextSize(category->name.c_str()).x;
        float windowWidth = ImGui::GetWindowSize().x;
        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::Text(category->name.c_str());

        ImGui::SetWindowFontScale(1.1f);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.0f);

        for (Module* module : category->modules) {
            bool isEnabled = module->isEnabled;
            ImVec4 buttonColor = isEnabled ? ImVec4(0.3f, 0.3f, 0.3f, 0.85f) : ImVec4(0.0f, 0.0f, 0.0f, 0.85f);
            ImVec4 hoverColor = isEnabled ? ImVec4(0.25f, 0.25f, 0.25f, 0.85f) : ImVec4(0.1f, 0.1f, 0.1f, 0.85f);
            ImVec4 activeColor = isEnabled ? ImVec4(0.2f, 0.2f, 0.2f, 0.85f) : ImVec4(0.1f, 0.1f, 0.1f, 0.85f);

            ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeColor);

            if (ImGui::Button(module->name.c_str(), ImVec2(-1, 30))) {
                module->isEnabled = !module->isEnabled;
                if (module->isEnabled) {
                    module->onEnable();
                }
                else {
                    module->onDisable();
                }
            }

            ImGui::PopStyleColor(3);
        }


        ImGui::End();
    }


    /*    COLORPICKER SHIT     */
    ImGui::SetNextWindowSize(ImVec2(200, 50));
    ImGui::Begin("Color", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

    if (ImGui::Button("Pick Color", ImVec2(-1, 30))) {
        colorPickerOpen = true;
    }

    if (colorPickerOpen) {
        ImGui::Begin("Pick a Color", &colorPickerOpen, ImGuiWindowFlags_NoCollapse);

        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowPadding = ImVec2(20, 20); 

        static ImVec4 pickedColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        bool colorChanged = ImGui::ColorPicker3("##ColorPicker", (float*)&pickedColor);

        static float rainbowSpeed = 0.1f; 
        ImGui::SliderFloat("Rainbow Speed", &rainbowSpeed, 0.01f, 2.0f); 
        static bool useRainbowColors = false; // Checkbox state
        ImGui::Checkbox("Use Rainbow Colors", &useRainbowColors);

        static float rainbowHue = 0.0f;
        rainbowHue += rainbowSpeed * ImGui::GetIO().DeltaTime;
        if (rainbowHue > 1.0f)
            rainbowHue -= 1.0f;

        ImVec4 rainbowColor = ImColor::HSV(rainbowHue, 0.7f, 0.7f);

        ImVec4 targetColor = useRainbowColors ? rainbowColor : (colorChanged ? pickedColor : guiBackgroundColor);

        guiBackgroundColor = targetColor;
        style.Colors[ImGuiCol_WindowBg] = guiBackgroundColor;

        ImGui::End();
    }
    else {

        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowPadding = ImVec2(10, 10);  

        style.Colors[ImGuiCol_WindowBg] = guiBackgroundColor;
        style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_Button] = guiBackgroundColor;
        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(guiBackgroundColor.x + 0.1f, guiBackgroundColor.y + 0.1f, guiBackgroundColor.z + 0.1f, guiBackgroundColor.w);
        style.Colors[ImGuiCol_ButtonActive] = ImVec4(guiBackgroundColor.x + 0.05f, guiBackgroundColor.y + 0.05f, guiBackgroundColor.z + 0.05f, guiBackgroundColor.w);

        ImGui::End();

    }

}