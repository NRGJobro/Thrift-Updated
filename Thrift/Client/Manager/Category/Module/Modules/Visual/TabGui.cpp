#include "TabGui.h"
#include "../../../../Manager.h"
#include "../../../../../Client.h"
#include "../../../../../Utils/Render/RenderUtils.h"

auto TabGui::onRender(MinecraftUIRenderContext* ctx) -> void {

	auto logoTextColor = Color(52.f, 152.f, 235.f, this->alpha);
	auto logoBgColor = Color(69.f, 119.f, 204.f, (this->alpha > 0.2 > this->alpha ? this->alpha - .2 : this->alpha));

	auto textColor = Color(5.f, 97.f, 163.f, this->alpha);
	auto bgColor = Color(21.f, 21.f, 21.f, (this->alpha > 0.2 > this->alpha ? this->alpha - .2 : this->alpha));
	
	auto mgr = this->category->mgr;
	auto client = mgr->client;

	Module* rainbowText = nullptr;

	if (!this->rainbowText) {

		for (auto category : mgr->categories)
			for (auto mod : category->modules)
				if ((mod->name.rfind("RainbowText") != std::string::npos) && mod->isEnabled)
					rainbowText = mod;

		if (rainbowText != nullptr)
			rainbowText->isEnabled = false;

	};

	auto logoText = client->name;
	auto fontSize = 1.f;

	auto xStretch = renderUtils->getTextLen(nullptr, logoText, fontSize);

	for (auto category : mgr->categories) {

		auto name = category->name;
		auto currLen = renderUtils->getTextLen(nullptr, name, fontSize);

		if (currLen > xStretch)
			xStretch = currLen;

	};

	auto startPos = Vec2<float>(4.f, 4.f);
	auto logoRect = Rect(startPos.x - 2.f, startPos.y - 2.f, (startPos.x + 2.f) + xStretch, startPos.y + (fontSize * 10));

	renderUtils->drawText(nullptr, startPos, logoText, logoTextColor, fontSize);
	renderUtils->fillRectangle(logoRect, logoBgColor);

	auto I = 0;
	for (auto category : mgr->categories) {

		renderUtils->drawText(nullptr, Vec2<float>(startPos.x, startPos.y + (I * 10) + 10.f), category->name, textColor, fontSize);
		I++;

	};

	auto bgRect = Rect(logoRect.x, logoRect.w, logoRect.z, logoRect.w + (mgr->categories.size() * 10));
	
	renderUtils->fillRectangle(bgRect, bgColor);

	if (selectedCat) {

		if (this->catAnimOff <= 0.f)
			this->catAnimOff = bgRect.x + 2.f;

		this->reachOff(&this->catAnimOff, (bgRect.z - 2.f), this->animModifier);
		renderUtils->fillRectangle(Rect(bgRect.x + 2.f, bgRect.y + (indexCat * 10) + 9.f, this->catAnimOff, bgRect.y + (indexCat * 10) + 10.f), logoBgColor);

		auto category = mgr->categories.at(this->indexCat);
		auto modules = category->modules;

		auto modsXStretch = 0.f;

		for (auto mod : modules) {

			auto currLen = renderUtils->getTextLen(nullptr, mod->name, fontSize);

			if (currLen > modsXStretch)
				modsXStretch = currLen;

		};

		auto startY = bgRect.y + (indexCat * 10);
		auto modsRect = Rect(bgRect.z, startY, (bgRect.z + modsXStretch) + 4.f, startY + (modules.size() * 10));

		I = 0;
		for (auto mod : modules) {

			renderUtils->drawText(nullptr, Vec2<float>(modsRect.x + 2.f, modsRect.y + (I * 10)), mod->name, ((mod->isEnabled || rainbowText != nullptr && rainbowText == mod) ? Color(30.f, 230.f, 120.f, this->alpha) : textColor), fontSize);
			I++;

		};

		renderUtils->fillRectangle(modsRect, bgColor);

		if (this->selectedMod) {

			if (this->modAnimOff <= 0.f)
				this->modAnimOff = modsRect.x + 2.f;

			this->reachOff(&this->modAnimOff, (modsRect.z - 2.f), this->animModifier);
			renderUtils->fillRectangle(Rect(modsRect.x + 2.f, modsRect.y + (indexMod * 10) + 9.f, this->modAnimOff, modsRect.y + (indexMod * 10) + 10.f), logoBgColor);

		};

	};

	if (rainbowText != nullptr)
		rainbowText->isEnabled = true;
	
	renderUtils->flush();
};

auto TabGui::onKey(uint64_t key, bool isDown, bool* cancelSend) -> void {

	if (!isDown)
		return;

	if (key != VK_LEFT && key != VK_RIGHT && key != VK_UP && key != VK_DOWN)
		return;

	*cancelSend = true;

	auto mgr = this->category->mgr;
	auto category = mgr->categories.at(this->indexCat);
	auto mod = (category->modules.size() > 0 ? category->modules.at(this->indexMod) : nullptr);

	switch (key) {

		case VK_RIGHT:
			
			if (!this->selectedCat && !this->selectedMod)
				this->selectedCat = true;
			else
				if (!this->selectedMod)
					this->selectedMod = true;
				else {
					if (mod != nullptr)
						mod->isEnabled = !mod->isEnabled;
				};

		break;

		case VK_LEFT:

			if (this->selectedMod) {

				this->selectedMod = false;
				this->modAnimOff = 0.f;
				this->indexMod = 0;

			}

			else
				if (this->selectedCat) {

					this->selectedCat = false;
					this->catAnimOff = 0.f;

				};

		break;

		case VK_DOWN:

			if (this->selectedCat && !this->selectedMod) {

				this->indexCat++;
				this->catAnimOff = 0.f;
				
				if (this->indexCat >= mgr->categories.size())
					this->indexCat = 0;

			}
			else if (this->selectedMod) {

				this->indexMod++;
				this->modAnimOff = 0.f;

				if (this->indexMod >= category->modules.size())
					this->indexMod = 0;

			};

		break;

		case VK_UP:

			if (this->selectedMod && this->selectedCat) {

				if (this->indexMod <= 0)
					this->indexMod = category->modules.size();

				this->indexMod--;
				this->modAnimOff = 0.f;

			}
			else if (this->selectedCat) {

				if (this->indexCat <= 0)
					this->indexCat = mgr->categories.size();

				this->indexCat--;
				this->catAnimOff = 0.f;

			};

		break;

	};

};

auto TabGui::reachOff(float* x, float xOff, float modifier) -> void {

	if (*x < xOff) {

		if (*x < (xOff - modifier))
			*x += modifier;
		else
			*x = xOff;

	}
	else if (*x > xOff) {

		if (*x > (xOff + modifier))
			*x -= modifier;
		else
			*x = xOff;

	};

};