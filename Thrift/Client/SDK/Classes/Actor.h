#pragma once

#include "../../Utils/Utils.h"
#include "../Components/AABBShapeComponent.h"
#include "../Components/RenderPositionComponent.h"
#include "../Components/StateVectorComponent.h"
#include "Level.h"
#include "Player.h"
#include "MoveInputHandler.h"
#include "ActorFlags.h"
#include "BlockActor.h"
#include "BlockSource.h"
#include "ActorCollision.h"
#include "ActorType.h"
#include "EntityContext.h"

// testing i am still connected?

// Classes/ Structs
class DirectPlayerMovementProxy;
//class EntityRegistry;
class ItemStack;
class ItemStackBase;
class CompoundTag;//
class ActorInitializationMethod;//
class VariantParameterList;//
struct ActorDamageSource;//
class ActorDamageCause;//
struct ArmorSlot;//
class ActorEvent;//
class ActorUniqueID;//
class IConstBlockSource;//
class NewInteractionModel;//
class InputMode;//
class Options;//
class ActorInteraction;//
struct ItemUseMethod;//
class MobEffectInstance;//
class PlayerMovementSettings;//
class ChangeDimensionPacket;//
class AutomaticID;//
struct DataLoadHelper;//
struct RenderParams;//
class Tick;//
class ChalkboardBlockActor;//
class ResolvedTextObject;//
struct TextObjectRoot;//
class SubChunkPos;//
class ChunkSource;//
class LayeredAbilities;//

class EntityLocation {
public:
	Vec3<float> posPrev;
	Vec3<float> pos;
	Vec3<float> velocity;
};


struct MobBodyRotationComponent {
	float bodyRot;
	float prevBodyRot;
};

template<typename T>
class FlagComponent {};

struct OnGroundFlag {};
struct OnGroundFlagComponent {};
struct JumpFromGroundRequestFlag {};
struct PlayerComponentFlag {};

class Actor { // 1.20.81
public:
	virtual void Destructor(); // ~Actor(); // Actor Destructor
public:
	virtual bool getStatusFlag(ActorFlags);
	virtual void setStatusFlag(ActorFlags, bool);
	virtual void outOfWorld(void);
	virtual void reloadHardcoded(ActorInitializationMethod, VariantParameterList const&);
	virtual void reloadHardcodedClient(ActorInitializationMethod, VariantParameterList const&);
	virtual void initializeComponents(ActorInitializationMethod, VariantParameterList const&);
	virtual void reloadComponents(ActorInitializationMethod, VariantParameterList const&);
	virtual void _serverInitItemStackIds(void);
	virtual void _doInitialMove(void);
	virtual bool hasComponent();
	virtual void resetUserPos(bool);
	virtual void getOwnerEntityType(void);
	virtual void remove(void);
	virtual void getFiringPos(void);
	virtual void getInterpolatedBodyRot(float);
	virtual void getInterpolatedHeadRot(float);
	virtual void getInterpolatedBodyYaw(float);
	virtual void getYawSpeedInDegreesPerSecond(void);
	virtual void getInterpolatedRidingOffset(float, int);
	virtual bool isFireImmune(void);
	virtual void blockedByShield(ActorDamageSource const&, Actor&);
	virtual bool canDisableShield(void);
	virtual void teleportTo(Vec3<float> const&, bool, int, int, bool);
	virtual void lerpMotion(Vec3<float> const&);
	virtual void tryCreateAddActorPacket(void);
	virtual void normalTick(void);
	virtual void baseTick(void);
	virtual void passengerTick(void);
	virtual void startRiding(Actor&);
	virtual void addPassenger(Actor&);
	virtual void getExitTip(std::string const&, InputMode, NewInteractionModel);
	virtual void getEntityLocNameString(void);
	virtual bool isInWall(void);
	virtual bool isInvisible(void);
	virtual bool canShowNameTag(void);
	virtual void getFormattedNameTag(void);
	virtual void getNameTagTextColor(void);
	virtual void getShadowRadius(void);
	virtual void getHeadLookVector(float);
	virtual bool canInteractWithOtherEntitiesInGame(void);
	virtual void getBrightness(float, IConstBlockSource const&);
	virtual void playerTouch(void);
	virtual bool isImmobile(void);
	virtual bool isSilentObserver(void);
	virtual bool isSleeping(void);
	virtual void setSleeping(bool);
	virtual void setSneaking(bool);
	virtual bool isBlocking(void);
	virtual bool isDamageBlocked(ActorDamageSource const&);
	virtual bool isAlive(void);
	virtual bool isOnFire(void);
	virtual bool isSurfaceMob(void);
	virtual bool isTargetable(void);
	virtual bool canAttack(Actor*, bool);
	virtual void setTarget(Actor*);
	virtual bool isValidTarget(Actor*);
	virtual void attack(Actor&, ActorDamageCause const&);
	virtual void performRangedAttack(Actor&, float);
	virtual void setOwner(ActorUniqueID);
	virtual void setSitting(bool);
	virtual void onTame(void);
	virtual void onFailedTame(void);
	virtual void setStanding(bool);
	virtual bool canPowerJump(void);
	virtual bool isEnchanted(void);
	virtual void shouldRender(void);
	virtual void playAmbientSound(void);
	virtual void getAmbientSound(void);
	virtual bool isInvulnerableTo(ActorDamageSource const&);
	virtual void getBlockDamageCause(Block const&);
	virtual void doFireHurt(int);
	virtual void onLightningHit(void);
	virtual void feed(int);
	virtual void handleEntityEvent(ActorEvent, int);
	virtual void getActorRendererId(void);
	virtual void despawn(void);
	virtual void setArmor(ArmorSlot, ItemStack const&);
	virtual void getArmorMaterialTypeInSlot(ArmorSlot);
	virtual void getArmorTextureIndexInSlot(ArmorSlot);
	virtual void getArmorColorInSlot(ArmorSlot, int);
	virtual void setEquippedSlot(int, ItemStack const&);
	virtual void setCarriedItem(ItemStack const&);
	virtual void getCarriedItem(void);
	virtual void setOffhandSlot(ItemStack const&);
	virtual void getEquippedTotem(void);
	virtual void consumeTotem(void);
	virtual void save(CompoundTag&);
	virtual void load(CompoundTag const&, DataLoadHelper&);
	virtual void queryEntityRenderer(void);
	virtual void getSourceUniqueID(void);
	virtual bool canFreeze(void);
	virtual void getLiquidAABB(void);
	virtual void handleInsidePortal(Vec3<int> const&);
	virtual bool canChangeDimensionsUsingPortal(void);
	virtual void changeDimension(int);
	virtual void changeDimension(ChangeDimensionPacket const&);
	virtual void getControllingPlayer(void);
	virtual void causeFallDamageToActor(float, float, ActorDamageSource);
	virtual void onSynchedDataUpdate(int);
	virtual bool canAddPassenger(Actor&);
	virtual bool canPickupItem(ItemStack const&);
	virtual bool canBePulledIntoVehicle(void);
	virtual void inCaravan(void);
	virtual void sendMotionPacketIfNeeded(PlayerMovementSettings const&);
	virtual bool canSynchronizeNewEntity(void);
	virtual void startSwimming(void);
	virtual void stopSwimming(void);
	virtual void buildDebugInfo(std::string&);
	virtual void getCommandPermissionLevel(void);
	virtual void getDeathTime(void);
	virtual bool canBeAffected(int);
	virtual bool canBeAffectedByArrow(MobEffectInstance const&);
	virtual void onEffectRemoved(MobEffectInstance&);
	virtual bool canObstructSpawningAndBlockPlacement(void);
	virtual void getAnimationComponent(void);
	virtual void openContainerComponent(void);
	virtual void swing(void);
	virtual void useItem(ItemStackBase&, ItemUseMethod, bool);
	virtual void getDebugText(std::vector<std::string>&);
	virtual void getMapDecorationRotation(void);
	virtual void getPassengerYRotation(Actor const&);
	virtual void add(ItemStack&);
	virtual void drop(ItemStack const&, bool);
	virtual void getInteraction(ActorInteraction&, Vec3<float> const&);
	virtual bool canDestroyBlock(Block const&);
	virtual void setAuxValue(int);
	virtual void startSpinAttack(void);
	virtual void stopSpinAttack(void);
	virtual void renderDebugServerState(Options const&);
	virtual void kill(void);
	virtual void die(ActorDamageSource const&);
	virtual void shouldDropDeathLoot(void);
	virtual void applySnapshot(void);
	virtual void getNextStep(float);
	virtual void onPush(Actor&);
	virtual void getLastDeathPos(void);
	virtual void getLastDeathDimension(void);
	virtual bool hasDiedBefore(void);
	virtual void doEnterWaterSplashEffect(void);
	virtual void doExitWaterSplashEffect(void);
	virtual void doWaterSplashEffect(void);
	virtual void _shouldProvideFeedbackOnHandContainerItemSet(int, ItemStack const&);
	virtual void _shouldProvideFeedbackOnArmorSet(ArmorSlot, ItemStack const&);
	virtual void updateEntitySpecificMolangVariables(RenderParams&);
	virtual void shouldTryMakeStepSound(void);
	virtual void _hurt(ActorDamageSource const&, float, bool, bool);
	virtual void readAdditionalSaveData(CompoundTag const&, DataLoadHelper&);
	virtual void addAdditionalSaveData(CompoundTag&);
	virtual void _playStepSound(Vec3<int> const&, Block const&);
	virtual void _doAutoAttackOnTouch(Actor&);


	bool isPlayer()
	{
		
		if (isAlive() && !isImmobile() && getNametag() != nullptr && !getNametag()->empty())
			return true;

		return false; // sorry about this homelessness but tozic would MURDER me if i added entt and components to this :pray:
	}

	std::string* getNametag() {
		static uintptr_t sig;
		if (sig == NULL) {
			sig = Utils::findSig("48 83 EC ? 48 8B 81 ? ? ? ? 48 85 C0 74 3B 48 8B 08 BA ? ? ? ? 48 8B 40 ? 48 2B C1 48 C1 F8 ? 66 3B D0 73 17");
		}

		auto fn = reinterpret_cast<std::string * (__thiscall*)(Actor*)>(sig);
		return fn(this);
	}

	float getTicksPerSecond() {
		if (this != nullptr) {
			Vec3<float> targetPos = this->stateVector->currentPos;
			Vec3<float> targetPosOld = this->stateVector->oldPos;
			float hVel = sqrtf(((targetPos.x - targetPosOld.x) * (targetPos.x - targetPosOld.x)) + ((targetPos.z - targetPosOld.z) * (targetPos.z - targetPosOld.z)));
			return hVel;
		}
		return -1.f;
	}

	float getBlocksPerSecond() {
		return getTicksPerSecond() * 20;
	}

	/*/
	bool isOnGround() { // ActorCollision::isOnGround
		return hasComponent<OnGroundFlagComponent>();
	}

	void setIsOnGround(bool state) {
		if (state) {
			getOrEmplaceComponent<OnGroundFlagComponent>();
		}
		else {
			removeComponent<OnGroundFlagComponent>();
		}
	};


	void jumpFromGround() {
		getOrEmplaceComponent<FlagComponent<JumpFromGroundRequestFlag>>();
	}

	Vec2<float>* getRotation() {
		__int64* v2 = (__int64*)*((__int64*)this + 0x55);
		if (v2 == nullptr)
			return nullptr;
		return (Vec2<float>*)v2;
	}

	void setRotations(Vec2<float>* a2)
	{
		__int64* v2 = (__int64*)*((__int64*)this + 0x55);
		if (v2 == nullptr) return;
		*v2 = *(__int64*)a2;
	}

	bool isPlayer()
	{
		return hasComponent<FlagComponent<PlayerComponentFlag>>();

	}
	/*/
public:
	// Level Actor::getLevel(void)
	BUILD_ACCESS(Level*, level, 0x250); // 1.20.81
	// Unknown
	BUILD_ACCESS(int16_t, hurtTime, 0x638); // 1.20.81
	// StateVector Actor::getPosition(void);
	BUILD_ACCESS(StateVectorComponent*, stateVector, 0x290); // 1.20.81
	// AABBShape (StateVector + 8) or Actor::getAABB(void)
	BUILD_ACCESS(AABBShapeComponent*, aabbShape, 0x298); // 1.20.81
};
