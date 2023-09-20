#pragma once

#include "../../Module.h"

class Arraylist : public Module {
public:
	Arraylist(Category* c) : Module(c, "Arraylist", "See all enabled module") {

		this->isEnabled = true;

	};
public:
	std::vector<class Module*> moduless2;
public:
	auto onEnable() -> void override;
	auto onRender(MinecraftUIRenderContext*) -> void override;
	auto onDisable() -> void override;
};