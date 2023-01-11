#include "Module.h"
#include "../Category.h"

Module::Module(Category* c, std::string n, std::string d) {

	this->category = c;
	this->name = n;
	this->description = d;

	this->category->modules.push_back(this);

};

auto Module::baseTick(void) -> void {

	if (this->wasEnabled != this->isEnabled) {

		this->wasEnabled = this->isEnabled;

		if (this->debugState)
			Utils::debugOutput("[ " + this->category->name + " : " + this->name + " ] " + (this->isEnabled ? "Enabled" : "Disabled"));

		if (this->isEnabled)
			this->onEnable();
		else
			this->onDisable();

	};

	if (this->isEnabled)
		this->onTick();

};