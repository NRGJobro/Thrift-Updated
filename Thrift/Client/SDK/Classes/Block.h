#pragma once

class Block
{
public:
	/*/
	BlockLegacy* GetBlockLegacy() {
		return *reinterpret_cast<BlockLegacy**>((uintptr_t)this + 0x30); // 1.20.71
	}

	TextHolder* GetTileName()
	{
		return GetBlockLegacy()->GetTileName();
	}

	Material* GetMaterial()
	{
		return GetBlockLegacy()->GetMaterial();
	}

	MaterialType GetMaterialType()
	{
		return GetBlockLegacy()->GetMaterial()->type;
	}
we are too homeless sorry	/*/
public:
	class TextHolder tileName;  //0x0008
private:
	char pad_0028[8];  //0x0028
public:
	class TextHolder name;  //0x0030
};