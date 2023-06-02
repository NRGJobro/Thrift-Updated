#pragma once
#include "../../Utils/Math.h"

class GuiData {
	char pad_0000[0x28]; //0x0000
public:
	struct Vec2<float> actualRes; //0x0030
private:
	char pad_0020[0x8]; //0x0038
public:
	struct Vec2<float> res;

	virtual void Constructor();

	float* getScale() {
		return reinterpret_cast<float*>((__int64)this + 0x4C);
	};
};