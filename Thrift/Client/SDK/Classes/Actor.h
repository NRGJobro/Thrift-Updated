#pragma once

#include "../../Utils/Utils.h"
#include "DirectPlayerMovementProxy.h"
#include "../Components/AABBShapeComponent.h"
#include "../Components/RenderPositionComponent.h"

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

class EntityLocation {
public:
	Vec3<float> posPrev;
	Vec3<float> pos;
	Vec3<float> velocity;
};

class Actor {
public:
	virtual int getStatusFlag(__int64);
	virtual void setStatusFlag(__int64, bool);
	virtual int getLastHurtByEntity(void);
	virtual void setLastHurtByEntity(Actor*);
	virtual int getLastHurtByPlayer(void);
	virtual void setLastHurtByPlayer(class Player*);
	virtual int getLastHurtEntity(void);
	virtual void setLastHurtEntity(Actor*);
	virtual void outOfWorld(void);
	virtual void reloadHardcoded(__int64, __int64 const&);
	virtual void reloadHardcodedClient(__int64, __int64 const&);
	virtual void initializeComponents(__int64, __int64 const&);
	virtual void reloadComponents(__int64, __int64 const&);
	virtual void _serverInitItemStackIds(void);
	virtual void _doInitialMove(void);
	virtual void hasComponent();//HashedString const&
	virtual void Destructor();
	virtual void resetUserPos(bool);
	virtual int getOwnerEntityType(void);
	virtual void remove(void);
	virtual bool isRuntimePredictedMovementEnabled(void);
	virtual int getPredictedMovementValues(void);
	virtual Vec3<float>* getPos(void);
	virtual Vec3<float>* getPosOld(void);
	virtual float getPosExtrapolated(float);
	virtual float getAttachPos(__int64, float);
	virtual int getFiringPos(void);
	virtual void move(Vec3<float> const&);
	virtual void move(__int64&, Vec3<float> const&);
	virtual float getInterpolatedRidingPosition(float);
	virtual float getInterpolatedBodyRot(float);
	virtual float getInterpolatedHeadRot(float);
	virtual float getInterpolatedBodyYaw(float);
	virtual int getYawSpeedInDegreesPerSecond(void);
	virtual float getInterpolatedWalkAnimSpeed(float);
	virtual float getInterpolatedRidingOffset(float, int);
	virtual void resetInterpolated(void);
	virtual void updateEntityInside(AABB const&);
	virtual void updateEntityInside(void);
	virtual bool isFireImmune(void);
	virtual void breaksFallingBlocks(void);
	virtual void blockedByShield(__int64 const&, Actor&);
	virtual void canDisableShield(void);
	virtual void teleportTo(Vec3<float> const&, bool, int, int, bool);
	virtual void tryTeleportTo(Vec3<float> const&, bool, bool, int, int);
	virtual void chorusFruitTeleport(Vec3<float> const&);
	virtual void lerpMotion(Vec3<float> const&);
	virtual void tryCreateAddEntityPacket(void);
	virtual void normalTick(void);
	virtual void baseTick(void);
	virtual void passengerTick(void);
	virtual void positionPassenger(Actor&, float);
	virtual void startRiding(Actor&);
	virtual void addPassenger(Actor&);
	virtual void flagPassengerToRemove(Actor&);
	virtual int getExitTip(std::string const&, __int64, __int64);
	virtual int getEntityLocNameString(void);
	virtual void intersects(Vec3<float> const&, Vec3<float> const&);
	virtual bool isInWall(void);
	virtual bool isInvisible(void);
	virtual bool canShowNameTag(void);
	virtual void canExistInPeaceful(void);
	virtual void setNameTagVisible(bool);
	virtual TextHolder* getNameTag(void);
	virtual int getNameTagAsHash(void);
	virtual TextHolder* getFormattedNameTag(void);
	virtual void filterFormattedNameTag(__int64 const&);
	virtual void setNameTag(std::string const&);
	virtual int getAlwaysShowNameTag(void);
	virtual void setScoreTag(std::string const&);
	virtual int getScoreTag(void);
	virtual bool isInWater(void);
public:
    DirectPlayerMovementProxy* getMovementProxy() {
        using MovementProxyFunction = void(__fastcall*)(Actor*, std::shared_ptr<void>*);
        static MovementProxyFunction originalFunction = (MovementProxyFunction)Utils::findSig("40 53 48 83 ec ? 8b 41 ? 48 8b da 48 8b 49 ? 48 8d 54 24 ? 89 44 24 ? 48 8b 09 e8 ? ? ? ? 45 33 c9");
        std::shared_ptr<void> movementProxyPointer;
        originalFunction(this, &movementProxyPointer);
        return (DirectPlayerMovementProxy*)movementProxyPointer.get();
    }
	RenderPositionComponent* getRenderPositionComponent() {
		using getRenderPositionComponent = RenderPositionComponent * (__cdecl*)(void*, EntityId*);
		static auto func = reinterpret_cast<getRenderPositionComponent>(Utils::findSig("40 53 48 83 EC ? 48 8B DA BA 6E F3 E8 D4"));
		auto registryBase = *reinterpret_cast<void**>(this->entityContext.registry);
		auto id = this->entityContext.id;
		return func(registryBase, &id);
	}
	AABBShapeComponent* getAABBShapeComponent() {
		using getAABBShapeComponent = AABBShapeComponent * (__cdecl*)(void*, EntityId*);
		static auto func = reinterpret_cast<getAABBShapeComponent>(Utils::findSig("40 53 48 83 EC ? 48 8B DA BA F2 C9 10 1B"));
		auto registryBase = *reinterpret_cast<void**>(this->entityContext.registry);
		auto id = this->entityContext.id;
		return func(registryBase, &id);
	}
public:
    BUILD_ACCESS(struct EntityContext, entityContext, 0x8);
	BUILD_ACCESS(class EntityLocation*, location, 0x2A0);
};