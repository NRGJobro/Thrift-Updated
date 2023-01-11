#pragma once

#include "../../Hook.h"

class Hook_LoopbackPacketSender : public Hook {
public:
	Hook_LoopbackPacketSender(Manager* mgr) : Hook(mgr) {};
public:
	auto init(void)->StatusData override;
};