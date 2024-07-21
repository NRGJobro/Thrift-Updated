#pragma once
#include "../../Utils/Math.h"

class GuiData {
	char pad_0000[0x30]; //0x0000
public:
	Vec2<float> actualRes; //0x0030
private:
	char pad_0020[0x10]; //0x0040
public:
	Vec2<float> resOLD;
	BUILD_ACCESS(Vec2<float>, res, 0x0040);

	virtual void Constructor();

	float* getScale() {
		return reinterpret_cast<float*>((__int64)this + 0x4C);//Good as of 1.20
	};
private:
	char pad_0x0050[0x1A]; //0x0050
public:
	Vec2<short> MousePos; //0x006A 
};