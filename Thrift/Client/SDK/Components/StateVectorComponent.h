#pragma once
#include "../../Utils/Utils.h"

class StateVectorComponent
{
public:
	Vec3<float> currentPos; //0x0000
	Vec3<float> oldPos; //0x000C
	Vec3<float> velocity; //0x0018
	char pad_0024[116]; //0x0024
}; //Size: 0x0098