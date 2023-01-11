#include "Utils.h"

std::string Utils::debugPath = Utils::getRoamPath();

auto Utils::getDll(void) -> HMODULE {

	MEMORY_BASIC_INFORMATION info;
	size_t len = VirtualQueryEx(GetCurrentProcess(), (void*)getDll, &info, sizeof(info));
	assert(len == sizeof(info));
	return len ? (HMODULE)info.AllocationBase : NULL;

};

auto Utils::findSig(const char* szSignature) -> unsigned long long {
	const char* pattern = szSignature;
	unsigned long long firstMatch = 0;

	static const unsigned long long rangeStart = (unsigned long long)GetModuleHandleA("Minecraft.Windows.exe");

	MODULEINFO miModInfo;
	static bool init = false;

	if (!init) {
		init = true;
		GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	};

	static const unsigned long long rangeEnd = rangeStart + miModInfo.SizeOfImage;

	BYTE patByte = GET_BYTE(pattern);
	const char* oldPat = pattern;

	for (unsigned long long pCur = rangeStart; pCur < rangeEnd; pCur++) {

		if (!*pattern)
			return firstMatch;

		while (*(PBYTE)pattern == ' ')
			pattern++;

		if (!*pattern)
			return firstMatch;

		if (oldPat != pattern) {
			oldPat = pattern;
			if (*(PBYTE)pattern != '\?')
				patByte = GET_BYTE(pattern);
		};

		if (*(PBYTE)pattern == '\?' || *(BYTE*)pCur == patByte) {

			if (!firstMatch)
				firstMatch = pCur;

			if (!pattern[2])
				return firstMatch;

			pattern += 2;

		}

		else {

			pattern = szSignature;
			firstMatch = 0;

		};
	};

	return NULL;

};

auto Utils::findMultiLvlPtr(uintptr_t baseAddr, std::vector<unsigned int> offsets) -> uintptr_t* {

	auto hwnd = GetModuleHandle(L"Minecraft.Windows.exe");

	auto ptr = (uintptr_t)(hwnd)+baseAddr;
	auto i = 0;

	do {

		if (*(uintptr_t*)ptr + offsets[i] == offsets[i] || *(uintptr_t*)ptr + offsets[i] > 0xFFFFFFFFFFFF)
			break;

		ptr = *(uintptr_t*)ptr + offsets[i];

		if (ptr == NULL)
			break;

		i++;

	} while (i < offsets.size());

	return (i == offsets.size() ? (uintptr_t*)ptr : nullptr);

};

auto Utils::getRoamPath(void) -> std::string {

	char* path = NULL;
	size_t length;

	_dupenv_s(&path, &length, "appdata");

	return std::string(path) + "\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState";

};

auto Utils::getDebugPath(void) -> std::string {

	auto f = std::filesystem::path(Utils::debugPath);

	if (!std::filesystem::exists(f))
		std::filesystem::create_directories(f);

	return Utils::debugPath;

};

auto Utils::setDebugPath(std::string path) -> void {

	Utils::debugPath = std::string(Utils::getRoamPath() + "\\" + path);

};

auto Utils::debugOutput(std::string output) -> void {

	static bool init = false;
	static auto path = Utils::getDebugPath();

	auto file = std::string(path + "\\Output.txt");

	if (!init) {
		auto f = std::filesystem::path(file);

		if (std::filesystem::exists(f))
			std::filesystem::remove(f);

		init = true;
	};

	CloseHandle(CreateFileA(file.c_str(), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL));

	std::ofstream fStream;
	fStream.open(file.c_str(), std::ios::app);

	if (fStream.is_open())
		fStream << output << "\n" << std::endl;

	return fStream.close();

};

auto Utils::ColorConvertRGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v) -> void {

	float K = 0.f;
	if (g < b) {
		auto tmp = g;
		g = b;
		b = tmp;

		K = -1.f;
	}
	if (r < g) {
		auto tmp = r;
		r = g;
		g = tmp;

		K = -2.f / 6.f - K;
	}

	const float chroma = r - (g < b ? g : b);
	out_h = fabsf(K + (g - b) / (6.f * chroma + 1e-20f));
	out_s = chroma / (r + 1e-20f);
	out_v = r;

};

auto Utils::ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b) -> void {

	if (s == 0.0f) {
		// gray
		out_r = out_g = out_b = v;
		return;
	}

	h = fmodf(h, 1.0f) / (60.0f / 360.0f);
	int i = (int)h;
	float f = h - (float)i;
	float p = v * (1.0f - s);
	float q = v * (1.0f - s * f);
	float t = v * (1.0f - s * (1.0f - f));

	switch (i) {
		
		case 0:
			
			out_r = v;
			out_g = t;
			out_b = p;

		break;
	
		case 1:
			
			out_r = q;
			out_g = v;
			out_b = p;

		break;
	
		case 2:
			
			out_r = p;
			out_g = v;
			out_b = t;

		break;
		
		case 3:
			
			out_r = p;
			out_g = q;
			out_b = v;

		break;
		
		case 4:
			
			out_r = t;
			out_g = p;
			out_b = v;

		break;
	
		case 5:
	
		default:
			
			out_r = v;
			out_g = p;
			out_b = q;
		
		break;
	}

};

auto Utils::ApplyRainbow(float* rcolors, float modifier = 0.003f) -> void {

	if (rcolors[3] < 1) {
		
		rcolors[0] = 1;
		rcolors[1] = 0.6f;
		rcolors[2] = 0.6f;
		rcolors[3] = 1;

	};

	Utils::ColorConvertRGBtoHSV(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);

	rcolors[0] += modifier;
	
	if (rcolors[0] >= 1)
		rcolors[0] = 0;

	Utils::ColorConvertHSVtoRGB(rcolors[0], rcolors[1], rcolors[2], rcolors[0], rcolors[1], rcolors[2]);

};