#pragma once

#include "../../Utils/Utils.h"

class Packet {
public:
	uintptr_t** VTable;
public:
    template<typename P>
    auto setVTable(unsigned long long) -> void;
};

class TextPacket : public Packet {
public:
    TextPacket(void);
};