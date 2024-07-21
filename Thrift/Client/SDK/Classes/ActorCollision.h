#pragma once

class ActorCollision {
public:
    bool isOnGround() {
        auto isOnGroundFunc = Utils::findSig("4C 8B 41 ? 4C 8B D1 48 8B 41 ? 4C 8B 49 ? 49 2B C0 48 C1 F8 ? 48 FF C8 25 ? ? ? ? 49 8B 0C C0 48 83 F9 ? 74 ? 0F 1F 84 00 ? ? ? ? 48 C1 E1 ? 42 81 7C 09 ? ? ? ? ? 4A 8D 04 09 74 ? 48 8B 08 48 83 F9 ? 75 ? 49 8B 42 ? 49 3B 42 ? 74 ? 48 8B 48 ? 48 85 C9 74 ? 4C 8B 49 ? 8B 02 8B D0 48 8B 49 ? 81 E2 ? ? ? ? 49 2B C9 44 8B C2 49 C1 E8 ? 48 C1 F9 ? 4C 3B C1 73 ? 4B 8B 0C C1 48 85 C9 74 ? 81 E2 ? ? ? ? 4C 8D 04 91 4D 85 C0 74 ? 25 ? ? ? ? 41 33 00 3D ? ? ? ? 73 ? B0 ? C3 32 C0 C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC 4C 8B 41 ? 41 BB ? ? ? ? 48 8B 41 ? 4C 8B D1 4C 8B 49 ? 49 2B C0 48 C1 F8 ? 48 FF C8 49 23 C3 49 8B 04 C0 48 83 F8 ? 74 ? 0F 1F 40 ? 48 C1 E0 ? 46 39 5C 08 ? 4A 8D 0C 08 74 ? 48 8B 01 48 83 F8 ? 75 ? 49 8B 4A ? 49 3B 4A ? 74 ? 48 8B 49 ? 48 85 C9 74 ? 4C 8B 49 ? 8B 02 8B D0 48 8B 49 ? 81 E2 ? ? ? ? 49 2B C9 44 8B C2 49 C1 E8 ? 48 C1 F9 ? 4C 3B C1 73 ? 4B 8B 0C C1 48 85 C9 74 ? 81 E2 ? ? ? ? 4C 8D 04 91 4D 85 C0 74 ? 25 ? ? ? ? 41 33 00 3D ? ? ? ? 73 ? B0 ? C3 32 C0 C3 CC CC CC 4C 8B 41 ? 4C 8B D1 48 8B 41 ? 4C 8B 49 ? 49 2B C0 48 C1 F8 ? 48 FF C8 25 ? ? ? ? 49 8B 0C C0 48 83 F9 ? 74 ? 0F 1F 84 00 ? ? ? ? 48 C1 E1 ? 42 81 7C 09 ? ? ? ? ? 4A 8D 04 09 74 ? 48 8B 08 48 83 F9 ? 75 ? 49 8B 42 ? 49 3B 42 ? 74 ? 48 8B 48 ? 48 85 C9 74 ? 4C 8B 49 ? 8B 02 8B D0 48 8B 49 ? 81 E2 ? ? ? ? 49 2B C9 44 8B C2 49 C1 E8 ? 48 C1 F9 ? 4C 3B C1 73 ? 4B 8B 0C C1 48 85 C9 74 ? 81 E2 ? ? ? ? 4C 8D 04 91 4D 85 C0 74 ? 25 ? ? ? ? 41 33 00 3D ? ? ? ? 73 ? B0 ? C3 32 C0 C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC 4C 8B 41 ? 41 BB");
        //void* rcx = *(void**)((__int64)this + 0x10);
        int rda = *(int*)((__int64)this + 0x8); // was 0x18 on actor
        return Utils::CallFunc<bool, void*, int*>((void*)isOnGroundFunc, this, &rda);
    }
};