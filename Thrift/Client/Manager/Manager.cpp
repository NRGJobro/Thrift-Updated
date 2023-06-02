#include "Manager.h"
#include "../Client.h"

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
#include "Hook/Hooks/LoopbackPacketSender/HookLoopbackPacketSender.h"
#include "Hook/Hooks/ClientInstance/HookClientInstance.h"
#include "Hook/Hooks/SwapChain/HookSwapChain.h"
#include "Hook/Hooks/MouseButton/HookMouse.h"
#include "Hook/Hooks/Key/HookKey.h"

auto Manager::initHooks(void) -> StatusData {

	if (MH_Initialize() != MH_OK)
		return StatusData(MethodStatus::Error, "Failed to Initialize MinHook");

	new Hook_LoopbackPacketSender(this);
	new Hook_ClientInstance(this);
	new Hook_SwapChain(this);
	new Hook_Mouse(this);
	new Hook_Key(this);

	for (auto hook : this->hooks) {

		auto data = hook->init();
		Utils::debugOutput(data.second);

	};

	return StatusData(MethodStatus::Success, "Finished initializing hooks!");

};

//Include Modules

/*Movement*/
#include "Category/Module/Modules/Movement/AirJump.h"
#include "Category/Module/Modules/Movement/AutoSprint.h"

/*Visuals*/
#include "Category/Module/Modules/Visual/TabGui.h"
#include "Category/Module/Modules/Visual/RainbowText.h"

/*Misc*/
#include "Category/Module/Modules/Other/TestModule.h"

auto Manager::initCategories(void) -> void {
	
	/* Combat */
	auto combat = new Category(this, "Combat");

	/* Movement */
	auto move = new Category(this, "Move");
	new AirJump(move);
	new AutoSprint(move);

	/* Player */
	auto player = new Category(this, "Player");


	/* Visuals */
	auto visuals = new Category(this, "Visuals");
	new TabGui(visuals);
	new RainbowText(visuals);

	/* World */
	auto world = new Category(this, "World");

	/* Other */
	auto other = new Category(this, "Misc");
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