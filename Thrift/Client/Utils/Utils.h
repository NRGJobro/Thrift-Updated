#pragma once

#include <Windows.h>
#include <filesystem>
#include <MinHook.h>
#include <assert.h>
#include <Psapi.h>
#include <ostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <chrono>
#include <sysinfoapi.h>
#include <type_traits>

#include "Math.h"
#include "TimeUtils.h"

template <typename F> auto IIFE(F f) { return f(); }

template <class T> struct remove_cvref { typedef std::remove_cv_t<std::remove_reference_t<T>> type; };

template <class T> using remove_cvref_t = typename remove_cvref<T>::type;

template <typename Ret, typename Type> Ret& direct_access(Type* type, size_t offset) {
	union {
		size_t raw;
		Type* source;
		Ret* target;
	} u;
	u.source = type;
	u.raw += offset;
	return *u.target;
}

#define AS_FIELD(type, name, fn) __declspec(property(get = fn, put = set##name)) type name
#define DEF_FIELD_RW(type, name) __declspec(property(get = get##name, put = set##name)) type name

#define FAKE_FIELD(type, name)                                                                                       \
AS_FIELD(type, name, get##name);                                                                                     \
type get##name()

#define BUILD_ACCESS(type, name, offset)                                                                             \
AS_FIELD(type, name, get##name);                                                                                     \
type get##name() const { return direct_access<type>(this, offset); }												 \
void set##name(type v) const { direct_access<type>(this, offset) = v; }

#include <wrl.h>
#include <dxgi.h>
#include <d3d11.h>
#include <d3d12.h>
#include <d2d1_3.h>
#include <dxgi1_4.h>
#include <dwrite_3.h>
#include <initguid.h>
#include <d3d11on12.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dwrite.lib")

#include "../Kiero/Kiero.h"

#define INRANGE(x,a,b)   (x >= a && x <= b)
#define GET_BYTE( x )    (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))

#define StatusData std::pair<MethodStatus, std::string>

enum MethodStatus {
	Success = 0,
	Failed = 1,
	Error = 2
};

class Utils {
private:
	static std::string debugPath;
public:
	static auto getDll(void)->HMODULE;
	static auto findSig(const char* szSignature)->unsigned long long;
	static auto findMultiLvlPtr(uintptr_t, std::vector<unsigned int>)->uintptr_t*;
public:
	static auto getRoamPath(void)->std::string;
public:
	static auto getDebugPath(void)->std::string;
	static auto setDebugPath(std::string)->void;
public:
	static auto debugOutput(std::string)->void;
public:
	template<typename T>
	static auto genRndNum(T min = 0, T max = 1)->T {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<>dis(min, max);
		return dis(gen);
	};
public:
	static auto ColorConvertRGBtoHSV(float, float, float, float&, float&, float&) -> void;
	static auto ColorConvertHSVtoRGB(float, float, float, float&, float&, float&) -> void;
	static auto ApplyRainbow(float*, float) -> void;
	static Color getGoodRainbow(float, float, float, long);
	template <unsigned int IIdx, typename TRet, typename... TArgs>
	static auto CallVFunc(void* thisptr, TArgs... argList) -> TRet {
		using Fn = TRet(__thiscall*)(void*, decltype(argList)...);
		return (*static_cast<Fn**>(thisptr))[IIdx](thisptr, argList...);
	}
};