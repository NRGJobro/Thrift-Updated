#pragma once

#include "../../Module.h"

class ClickGui : public Module {
public:
    ClickGui(Category* c) : Module(c, "ClickGui", "For testing shiz") {
        this->key = VK_INSERT;
    };

    auto onImGuiRender() -> void override;
    auto onDisable() -> void override;
    auto onEnable() -> void override;
};