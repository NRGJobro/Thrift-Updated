#include "Packet.h"

template<typename P>
auto Packet::setVTable(uintptr_t sig) -> void {
    
    if (sig == NULL)
        return;

    memset(this, 0, sizeof(P));
    int offset = *(int*)(sig + 3);
    this->VTable = (uintptr_t**)(sig + offset + 7);

};

auto Packet::getId() -> int {
    return Utils::CallVFunc<1, int>(this);
}

auto Packet::getName() -> TextHolder* {
    return Utils::CallVFunc<2, TextHolder*>(this, new TextHolder());
}

void TextPacket::SetVTable() {
    static auto sig = (uintptr_t)NULL;

    if (!sig)
        sig = Utils::findSig("48 8d 05 ? ? ? ? 48 89 44 24 ? 48 8d 4d ? e8 ? ? ? ? 48 8d 4d ? e8 ? ? ? ? 48 8d 4d ? e8 ? ? ? ? 48 8d 4d ? e8 ? ? ? ? 48 8d 4d");

    this->setVTable<TextPacket>(sig);
};