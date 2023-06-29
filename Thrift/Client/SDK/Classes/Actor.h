#pragma once

#include "../../Utils/Utils.h"
#include "DirectPlayerMovementProxy.h"

// Classes/ Structs
class DirectPlayerMovementProxy;
class EntityRegistry;

struct EntityId {
    uint32_t id;
};

struct EntityContext {
    EntityRegistry* registry;
    EntityId id;
};

class Actor {
public:
    DirectPlayerMovementProxy* getMovementProxy() {
        using MovementProxyFunction = void(__fastcall*)(Actor*, std::shared_ptr<void>*);
        static MovementProxyFunction originalFunction = (MovementProxyFunction)Utils::findSig("40 53 48 83 ec ? 8b 41 ? 48 8b da 48 8b 49 ? 48 8d 54 24 ? 89 44 24 ? 48 8b 09 e8 ? ? ? ? 45 33 c9");
        std::shared_ptr<void> movementProxyPointer;
        originalFunction(this, &movementProxyPointer);
        return (DirectPlayerMovementProxy*)movementProxyPointer.get();
    }
public:
    BUILD_ACCESS(struct EntityContext, entityContext, 0x8);
    BUILD_ACCESS(uint32_t, entityIdentifier, 0x10);
};