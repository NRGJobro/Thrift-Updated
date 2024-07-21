#pragma once
//Include like this to avoid over riding
#include "Block.h"

class BlockSource {
public:
	Block* getBlock(Vec3<int> blockPos)
	{
		return Utils::CallVFunc<2, Block*, Vec3<int>&>(this, blockPos);
	}
};