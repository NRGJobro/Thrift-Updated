#pragma once

#include "../../Hook.h"

class Hook_ClientInstance : public Hook {
public:
	Hook_ClientInstance(Manager* mgr) : Hook(mgr) {};
public:
	auto init(void)->StatusData override;
};