#pragma once
#include "../../Utils/Utils.h"

class DirectPlayerMovementProxy {
public:
    bool isOnGround() {
        return Utils::CallVFunc<43, bool>(this);
    }

    auto setOnGround(bool onGround) -> void {
        return Utils::CallVFunc<44, void, bool>(this, onGround);
    };
};