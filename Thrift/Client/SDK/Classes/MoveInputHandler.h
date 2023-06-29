#pragma once
#include "../../Utils/Utils.h"

class MoveInputHandler {
public:
	BUILD_ACCESS(bool, isSneakDownPrev, 0x0);
	BUILD_ACCESS(bool, isJumpingPrev, 0x6);
	BUILD_ACCESS(bool, isSprintingPrev, 0x7);
	BUILD_ACCESS(bool, forwardPrev, 0xA);
	BUILD_ACCESS(bool, backwardPrev, 0xB);
	BUILD_ACCESS(bool, leftPrev, 0xC);
	BUILD_ACCESS(bool, rightPrev, 0xD);
	BUILD_ACCESS(bool, isSneakDown, 0x20);
	BUILD_ACCESS(bool, isJumping, 0x26);
	BUILD_ACCESS(bool, isSprinting, 0x27);
	BUILD_ACCESS(bool, forward, 0x2A);
	BUILD_ACCESS(bool, backward, 0x2B);
	BUILD_ACCESS(bool, left, 0x2C);
	BUILD_ACCESS(bool, right, 0x2D);
	BUILD_ACCESS(float, sideMovement, 0x48);
	BUILD_ACCESS(float, forwardMovement, 0x4C);

	bool isPressed() {
		return forward || backward || left || right;
	};
};