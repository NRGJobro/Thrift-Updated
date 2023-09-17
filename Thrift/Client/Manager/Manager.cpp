#include "Manager.h"
#include "Client.h"

Manager::Manager(Client* c) {

	this->client = c;
	this->isRunning = true;

	auto hooksData = this->initHooks();
	
	switch (hooksData.first) {

		case MethodStatus::Success:
			
			this->initCategories();

		break;

		case MethodStatus::Error:
			
			Utils::debugOutput(hooksData.second);
			this->isRunning = false;

		break;

		case MethodStatus::Failed:
			
			this->isRunning = false;
			this->uninjectDLL();

		break;
	}

	while (this->isRunning) {

		for (auto category : this->categories) {

			category->baseTick();

		};

	};

	this->uninjectDLL();

};

//Hook Includes
#include "Hooks/LoopbackPacketSender/HookLoopbackPacketSender.h"
#include "Hooks/ClientInstance/HookClientInstance.h"
#include "Hooks/SwapChain/HookSwapChain.h"
#include "Hooks/MouseButton/HookMouse.h"
#include "Hooks/Key/HookKey.h"

auto Manager::initHooks(void) -> StatusData {

	if (MH_Initialize() != MH_OK)
		return StatusData(MethodStatus::Error, "Failed to Initialize MinHook");

	new Hook_ClientInstance(this);
	new Hook_SwapChain(this);
	new Hook_Mouse(this);
	new Hook_Key(this);
	new Hook_LoopbackPacketSender(this);

	for (auto hook : this->hooks) {

		auto data = hook->init();
		Utils::debugOutput(data.second);

	};

	return StatusData(MethodStatus::Success, "Finished initializing hooks!");

};

//Include Modules

/*Movement*/
#include "Modules/Movement/AirJump.h"
#include "Modules/Movement/AutoSprint.h"
#include "Modules/Movement/AutoJump.h"

/*Player*/
#include "Modules/Player/Jesus.h"

/*Visuals*/
#include "Modules/Visual/TabGui.h"
#include "Modules/Visual/RainbowText.h"
#include "Modules/Visual/ClickGui.h"

/*Misc*/
#include "Modules/Other/TestModule.h"
auto Manager::initCategories(void) -> void {
	/* Combat */
	auto combat = new Category(this, "Combat");
	combat->index = 0;

	/* Movement */
	auto move = new Category(this, "Move");
	move->index = 1;
	new AirJump(move);
	new AutoSprint(move);
	new AutoJump(move);

	/* Player */
	auto player = new Category(this, "Player");
	player->index = 2;
	new Jesus(player);

	/* Visuals */
	auto visuals = new Category(this, "Visuals");
	visuals->index = 3;
	new TabGui(visuals);
	new RainbowText(visuals);
	new ClickGui(visuals);

	/* World */
	auto world = new Category(this, "World");
	world->index = 4;

	/* Other */
	auto other = new Category(this, "Misc");
	other->index = 5;
	new TestModule(other);
};

auto Manager::uninjectDLL(void) -> void {
	DisableThreadLibraryCalls(Utils::getDll());
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	FreeLibraryAndExitThread(Utils::getDll(), 0);
	Sleep(1000);
	MH_Uninitialize();
};