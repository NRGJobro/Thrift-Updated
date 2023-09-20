#include "Arraylist.h"
#include "../../Manager.h"
#include "../../Client.h"
#include "../../../Utils/Render/ImGuiUtils.h"

auto Arraylist::onEnable() -> void {
    auto mgr = this->category->mgr;
        for (auto cata : mgr ->categories)
            for (auto module : cata->modules)
            {
                moduless2.push_back(module);
            }
        std::sort(moduless2.begin(), moduless2.end(), [](const Module* a, const Module* b) {
            return a->name.size() > b->name.size();
            });
        moduless2.erase(std::unique(moduless2.begin(), moduless2.end()), moduless2.end());
}

auto Arraylist::onRender(MinecraftUIRenderContext* ctx) -> void {
    auto fontSize = 1.f;
    float the100 = 0.f;

    auto data = Minecraft::getClientInstance()->getGuiData();

    auto i = 0;

    for (auto mod2 : moduless2) {
        if (mod2->isEnabled) {
            the100 = the100 + 10.f;
            auto currLen = renderUtils->getTextLen(nullptr, mod2->name, fontSize);
            auto rightCorner = data->res.x - 100.f + (96.f - currLen);

            renderUtils->drawText(nullptr, Vec2<float>(rightCorner, (i * 10) + 4.f), mod2->name, Color(30.f, 230.f, 120.f, 1.f), fontSize);
            i++;
        };
    }
}

auto Arraylist::onDisable() -> void {
    moduless2.clear();
}