#pragma once

#include "../../Hook.h"

class Hook_SwapChain : public Hook {
public:
	Hook_SwapChain(Manager* mgr) : Hook(mgr) {};
public:
	auto init(void)->StatusData override;
};