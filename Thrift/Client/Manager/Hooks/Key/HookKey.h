#pragma once

#include "../Hook.h"

class Hook_Key : public Hook {
public:
	Hook_Key(Manager* mgr) : Hook(mgr) {};
public:
	auto init(void)->StatusData override;
};