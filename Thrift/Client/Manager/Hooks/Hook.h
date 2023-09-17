#pragma once

#include "../../Utils/Utils.h"
#include "../../SDK/Minecraft.h"

class Manager;

class Hook {
public:
	Manager* mgr;
public:
	Hook(Manager*);
public:
	virtual auto init(void) -> StatusData { return StatusData(MethodStatus::Error, "No override!"); };
};