#pragma once

class MoveInputHandler {
public:
	float sideMovement;
	float forwardMovement;
private:
	char _pad1[57];
public:
	bool isSneakKeyDown;
private:
	char _pad2[5];
public:
	bool isJumping;
	bool autoJumpInWater;
private:
	char _pad3[14];
public:
	bool forwardKey;
	bool backwardKey;
	bool leftKey;
	bool rightKey;

public:
	virtual ~MoveInputHandler();
	virtual void tick(unsigned __int64 IPlayerMovementProxy);
	virtual void render(float);
	virtual void setKey(int, bool);
	virtual void clearInputState(void);
	virtual void clearMovementState(void);
	virtual void allowPicking(float, float);
	virtual void setJumping(bool);
	virtual void setAutoJumpingInWater(bool);
	virtual bool isChangeHeight(void);
	virtual void setSneakDown(bool);
	virtual bool isPlayerMoving(void);
	virtual int getGazeDirection(void);
	virtual void extractInputComponent(void);
	virtual void fillInputPacket(unsigned __int64 PlayerAuthInputPacket);
private:
	virtual void _pure_virtual();
public:
	virtual void createSnapshot(void);
};