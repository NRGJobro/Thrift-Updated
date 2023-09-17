#pragma once

#include "../../Module.h"

class ClickGui : public Module {
public:
    ClickGui(Category* c) : Module(c, "ClickGui", "For testing shiz") {
        this->key = 'K';
    };

    auto onImGuiRender() -> void override;
};