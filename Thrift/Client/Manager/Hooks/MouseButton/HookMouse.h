#pragma once

#include "../Hook.h"

class Hook_Mouse : public Hook {
public:
	Hook_Mouse(Manager* mgr) : Hook(mgr) {};
public:
	auto init(void) -> StatusData override;
};