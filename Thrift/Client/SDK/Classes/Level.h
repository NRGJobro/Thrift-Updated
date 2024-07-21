#pragma once
#include "../../Utils/Utils.h"
#include "EntityContext.h"

class Actor;
class Block;

enum class HitResultType : int {
	Tile = 0x0,
	Entity = 0x1,
	EntityOutOfRange = 0x2,
	NoHit = 0x3,
};

struct WeakEntityRef {
private:
	uint8_t pad[0x10]{};

public:
	//int id23{};

private:
	uint8_t pad2[0x4]{};
};

class HitResult {
public:
	Vec3<float>     startPos;     // this+0x0
	Vec3<float>     rayDir;       // this+0xC
	HitResultType   type;         // this+0x18
	unsigned char	facing;       // this+0x1C
	Vec3<int>       blockPos;     // this+0x20
	Vec3<float>     Pos;          // this+0x2C
	WeakEntityRef	entity;       // this+0x38
	bool			isHitLiquid;  // this+0x50
	unsigned char	liquidFacing; // this+0x51
	Vec3<int>		liquid;       // this+0x54
	Vec3<float>     liquidPos;    // this+0x60
	bool			indirectHit;  // this+0x6C
};

class BlockPalette {
public:
	Block* getBlock(unsigned int* runtimeId) {
		using getblock_t = Block*(__fastcall*)(BlockPalette*, unsigned int*);
		static getblock_t getblock = reinterpret_cast<getblock_t>(Utils::findSig("40 ? 48 81 EC ? ? ? ? 48 8B ? ? ? ? ? 48 33 ? 48 89 ? ? ? ? ? ? 48 8B ? C7 44 24 20"));
		return getblock(this, runtimeId);
	}
};

class Level {
public:
	BUILD_ACCESS(BlockPalette*, blockPalette, 0x0AC8);

	std::vector<Actor*> getRuntimeActorList() {
		std::vector<Actor*> listOut;
		Utils::CallVFunc<278, decltype(&listOut)>(this, &listOut); // Updated to 1.20.80
		return listOut;
	}
	
	HitResult* getHitResult() {
		return (HitResult*)Utils::CallVFunc<288, HitResult*>(this);
	}

	BlockPalette* getBlockPalette() {
		return Utils::CallVFunc<70, BlockPalette*>(this);
	}
	/*std::vector<Actor*> getRuntimeActorList() {
		static uintptr_t sig = Utils::findSig("40 53 48 83 EC 30 48 81 C1 E0 1C 00 00"); // Updated to 1.20.71
		static auto getRuntimeActorList = *(decltype(&Level::getRuntimeActorList)*)&sig;
		return (this->*getRuntimeActorList)();
	}*/

	/*
private:
	char pad_0x0000[0xC48]; //0x0000
public:
	Vec3<float> Origin; //0x0BD8 
	Vec3<float> RelativeRayEnd;
	HitResultType HitType;
	int BlockFace;
	Vec3<int> IBlockPos; //0x0BF8 
	Vec3<float> AbsoluteHitPos;
	*/
};
