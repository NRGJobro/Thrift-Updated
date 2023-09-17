#include "HookMouse.h"

#include "../../Module.h"
#include "../../Manager.h"
#include "../SwapChain/ImGui/imgui.h"

Manager* mouseMgr = nullptr;

typedef __int64(__fastcall* Mouse)(__int64 a1, char mouseButton, char isDown, __int16 mouseX, __int16 mouseY, __int16 relativeMovementX, __int16 relativeMovementY, char a8);
Mouse _Mouse;

__int64 getMouseCallback(__int64 a1, char mouseButton, char isDown, __int16 mouseX, __int16 mouseY, __int16 relativeMovementX, __int16 relativeMovementY, char a8) {
	if (ImGui::GetCurrentContext() != nullptr) {
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent(mouseX, mouseY);
		switch (mouseButton) {
		case 1:
			io.MouseDown[0] = isDown;
			break;
		case 2:
			io.MouseDown[1] = isDown;
			break;
		case 3:
			io.MouseDown[2] = isDown;
			break;
		case 4:
			io.MouseWheel = isDown < 0 ? -0.5f : 0.5f; //For scrolling
			break;
		default:
			break;
		}
		if (!io.WantCaptureMouse) return _Mouse(a1, mouseButton, isDown, mouseX, mouseY, relativeMovementX, relativeMovementY, a8);

	} else return _Mouse(a1, mouseButton, isDown, mouseX, mouseY, relativeMovementX, relativeMovementY, a8);
}

auto Hook_Mouse::init(void) -> StatusData {

	mouseMgr = this->mgr;
	auto sig = Utils::findSig("48 8b c4 48 89 58 ? 48 89 68 ? 48 89 70 ? 57 41 54 41 55 41 56 41 57 48 83 ec ? 44 0f b7 bc 24");

	if (!sig)
		return StatusData(MethodStatus::Error, "[Mouse Hook] Failed to find Signature!");

	if (MH_CreateHook((void*)sig, &getMouseCallback, reinterpret_cast<LPVOID*>(&_Mouse)) != MH_OK)
		return StatusData(MethodStatus::Error, "[Mouse Hook] Failed to create hook!");

	if (MH_EnableHook((void*)sig) != MH_OK)
		return StatusData(MethodStatus::Error, "[Mouse Hook] Failed to enable hook!");

	return StatusData(MethodStatus::Success, "[Mouse Hook] Successfully hooked Mouse Hook!");

};