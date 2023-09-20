#include "ClickGui.h"
#include "../../Manager.h"
#include "../../Client.h"
#include "../../Hooks/SwapChain/ImGui/imgui.h"
#include "../../../Utils/Render/ImGuiUtils.h"
#include "../../../Utils/Render/RenderUtils.h"
#include "../../Hooks/SwapChain/ImGui/imgui_internal.h"
#include "../../Hooks/SwapChain/ImGui/Animations/dotMatrix.h"

bool colorPickerOpen = false;
ImVec4 guiBackgroundColor = ImVec4(0.0f, 0.0f, 0.0f, 0.70f);
std::vector<Particle> dots;

/*  dumbed down ghetto clickgui from epic uwu */

static ImVec2 getScreenResolution() {
    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    return ImVec2(desktop.right, desktop.bottom);
}

void ClickGui::onEnable() {
    auto instance = Minecraft::getClientInstance();
    if (instance->getMinecraftGame()->canUseKeys) {
        instance->grabMouse();
    }
}

bool madeMatrix = false;

void ClickGui::onImGuiRender() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 10.0f;

    ImVec2 displaySize = ImGui::GetIO().DisplaySize;
    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    drawList->AddRectFilled(ImVec2(0, 0), displaySize, ImColor(0.f, 0.f, 0.f, 0.30f));
    if (!madeMatrix) {
		madeMatrix = true;
        dots = createDotMatrix({ getScreenResolution().x,getScreenResolution().y }, { 40,40 }, getScreenResolution().x * getScreenResolution().y / 7500);
    }
    updateDotMatrix({ getScreenResolution().x,getScreenResolution().y }, dots);
    drawDotMatrix(dots, 50, 0.05, true);

    style.Colors[ImGuiCol_WindowBg] = guiBackgroundColor;
    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_Button] = guiBackgroundColor;
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(guiBackgroundColor.x + 0.1f, guiBackgroundColor.y + 0.1f, guiBackgroundColor.z + 0.1f, guiBackgroundColor.w);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(guiBackgroundColor.x + 0.05f, guiBackgroundColor.y + 0.05f, guiBackgroundColor.z + 0.05f, guiBackgroundColor.w);

    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
    style.WindowPadding = ImVec2(10, 10);

    ImGui::SetNextWindowSize(ImVec2(200, 50));
    ImGui::Begin("Color", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

    if (ImGui::Button("Pick Color", ImVec2(-1, 30))) {
        colorPickerOpen = true;
    }

    ImGui::End();

    float categoryWindowWidth = 200.0f; 
    float categoryWindowHeight = 500.0f;
    float horizontalSpacing = 60.0f;     
    float xPos = displaySize.x;

    for (size_t i = 0; i < this->category->mgr->categories.size(); i++) {
        Category* category = this->category->mgr->categories[i];
        xPos = displaySize.x / (this->category->mgr->categories.size() + 1) * (i + 1);

        /*   CATEGORY SHIT   */
      
        ImGui::SetNextWindowSize(ImVec2(categoryWindowWidth, categoryWindowHeight));
        ImGui::SetNextWindowPos(ImVec2(xPos, 115.0f), ImGuiCond_FirstUseEver);
        ImGui::Begin(category->name.c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
        ImGui::SetWindowFontScale(1.3f);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.0f);
        float textWidth = ImGui::CalcTextSize(category->name.c_str()).x;
        float windowWidth = ImGui::GetWindowSize().x;
        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::Text(category->name.c_str());
        ImGui::SetWindowFontScale(1.1f);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.0f);


        for (Module* module : category->modules) {
            bool isEnabled = module->isEnabled;
            ImVec4 buttonColor = isEnabled ? ImVec4(0.3f, 0.3f, 0.3f, 0.70f) : ImVec4(0.0f, 0.0f, 0.0f, 0.70f);
            ImVec4 hoverColor = isEnabled ? ImVec4(0.25f, 0.25f, 0.25f, 0.70f) : ImVec4(0.1f, 0.1f, 0.1f, 0.70f);
            ImVec4 activeColor = isEnabled ? ImVec4(0.2f, 0.2f, 0.2f, 0.70f) : ImVec4(0.1f, 0.1f, 0.1f, 0.70f);


            ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeColor);

            /*   MODULE SHIT   */

            if (ImGui::Button(module->name.c_str(), ImVec2(-1, 30))) {
                module->isEnabled = !module->isEnabled;
                if (module->isEnabled) module->onEnable(); else module->onDisable();
            }
            ImGui::PopStyleColor(3);

            if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) {
                ImGui::SetTooltip(module->description.c_str());
            }
        }
        ImGui::End();
    }



    /*   COLORPICKER SHIT   */
    if (colorPickerOpen) {
        ImGui::Begin("Pick a Color", &colorPickerOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
        float textWidth = ImGui::CalcTextSize("Pick a Color").x;
        float windowWidth = ImGui::GetWindowSize().x;
        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::SetWindowFontScale(1.2f);
        ImGui::Text("Pick a Color");
        ImGui::SetWindowFontScale(1.f);

        style.WindowPadding = ImVec2(20, 20);  

        static ImVec4 pickedColor = ImVec4(1.0f, 1.0f, 1.0f, 0.70f);
        bool colorChanged = ImGui::ColorPicker3("##ColorPicker", (float*)&pickedColor);

        static float rainbowSpeed = 0.1f;
        ImGui::SliderFloat("Rainbow Speed", &rainbowSpeed, 0.01f, 2.0f); 

        static bool useRainbowColors = false; 
        ImGui::Checkbox("Use Rainbow Colors", &useRainbowColors);

     
        static float rainbowHue = 0.0f;
        rainbowHue += rainbowSpeed * ImGui::GetIO().DeltaTime;
        if (rainbowHue > 1.0f)
            rainbowHue -= 1.0f;

        ImVec4 rainbowColor = ImColor::HSV(rainbowHue, 0.7f, 0.7f, 0.70f);

        ImVec4 targetColor = useRainbowColors ? rainbowColor : (colorChanged ? pickedColor : guiBackgroundColor);

  
        guiBackgroundColor = targetColor;
        style.Colors[ImGuiCol_WindowBg] = guiBackgroundColor;
        style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        style.Colors[ImGuiCol_FrameBg] = guiBackgroundColor;
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(guiBackgroundColor.x + 0.1f, guiBackgroundColor.y + 0.1f, guiBackgroundColor.z + 0.1f, guiBackgroundColor.w);
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(guiBackgroundColor.x + 0.05f, guiBackgroundColor.y + 0.05f, guiBackgroundColor.z + 0.05f, guiBackgroundColor.w);

        ImGui::End();
        return;
    }
 
    style.WindowPadding = ImVec2(10, 10);

    style.Colors[ImGuiCol_WindowBg] = guiBackgroundColor;
    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    style.Colors[ImGuiCol_Button] = guiBackgroundColor;
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(guiBackgroundColor.x + 0.1f, guiBackgroundColor.y + 0.1f, guiBackgroundColor.z + 0.1f, guiBackgroundColor.w);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(guiBackgroundColor.x + 0.05f, guiBackgroundColor.y + 0.05f, guiBackgroundColor.z + 0.05f, guiBackgroundColor.w);

    ImGui::End();
}

void ClickGui::onDisable() {
    auto instance = Minecraft::getClientInstance();
    instance->releaseMouse();
}