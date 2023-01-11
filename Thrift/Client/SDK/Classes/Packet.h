#pragma once

#include "../../Utils/Utils.h"
#include "TextHolder.h"

class Packet {
public:
	uintptr_t** VTable;
private:
	char pad_0x28[0x28];
public:
    template<typename P>
    auto setVTable(unsigned long long) -> void;
};

class TextPacket : public Packet {
public:
	TextPacket() {
		SetVTable();
		messageType = 1;  // TYPE_CHAT
	}
	void SetVTable();

	unsigned __int8 messageType;  // 0x28
private:
	char pad1[0x7];
public:
	TextHolder sourceName;           // 0x30
	TextHolder message;              // 0x50
private:
	char pad2[0x18];  // 0x70
public:
	bool translationNeeded = false;  // 0x88
private:
	char pad3[0x7];  // 0x89
public:
	TextHolder xboxUserId;
	TextHolder platformChatId;
};