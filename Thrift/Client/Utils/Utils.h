#pragma once

#include <filesystem>
#include <MinHook.h>
#include <Windows.h>
#include <assert.h>
#include <Psapi.h>
#include <ostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>

#include <type_traits>

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
};

template<typename T>
class Vec2 {
public:
	T x = 0;
	T y = 0;
public:
	Vec2(T x = 0, T y = 0) {
		this->x = x;
		this->y = y;
	};
public:
	Vec2<T>& operator = (const Vec2<T>& v) {
		x = v.x;
		y = v.y;
		return *this;
	};
public:
	bool operator == (const Vec2<T>& v) {
		return (
			this->x == v.x && 
			this->y == v.y
		);
	};
	bool operator != (const Vec2<T>& v) {
		return (
			this->x != v.x || 
			this->y != v.y
		);
	};
public:
	Vec2<T> div(T v) {
		return Vec2<T>(x / v, y / v);
	};
	Vec2<T> div(T vX, T vY) {
		return Vec2<T>(x / vX, y / vY);
	};
	Vec2<T> div(Vec2<T>& v) {
		return Vec2<T>(x / v.x, y / v.y);
	};
public:
	Vec2<T> mul(T v) {
		return Vec2<T>(x * v, y * v);
	};
	Vec2<T> mul(T vX, T vY) {
		return Vec2<T>(x * vX, y * vY);
	};
	Vec2<T> mul(Vec2<T>& v) {
		return Vec2<T>(x * v.x, y * v.y);
	};
public:
	Vec2<T> add(T v) {
		return Vec2<T>(x + v, y + v);
	};
	Vec2<T> add(T vX, T vY) {
		return Vec2<T>(x + vX, y + vY);
	};
	Vec2<T> add(Vec2<T>& v) {
		return Vec2<T>(x + v.x, y + v.y);
	};
public:
	Vec2<T> sub(T v) {
		return Vec2<T>(x - v, y - v);
	};
	Vec2<T> sub(T vX, T vY) {
		return Vec2<T>(x - vX, y - vY);
	};
	Vec2<T> sub(Vec2<T>& v) {
		return Vec2<T>(x - v.x, y - v.y);
	};
};

template<typename T>
class Vec3 : public Vec2<T> {
public:
	T x = 0;
	T y = 0;
	T z = 0;
public:
	Vec3(T x = 0, T y = 0, T z = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
	};
public:
	Vec3<T>& operator = (const Vec3<T>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	};
public:
	bool operator == (const Vec3<T>& v) {
		return (
			this->x == v.x && 
			this->y == v.y && 
			this->z == v.z
		);
	};
	bool operator != (const Vec3<T>& v) {
		return (
			this->x != v.x || 
			this->y != v.y || 
			this->z != v.z
		);
	};
public:
	Vec3<T> div(T v) {
		return Vec3<T>(x / v, y / v, z / v);
	};
	Vec3<T> div(T vX, T vY, T vZ) {
		return Vec3<T>(x / vX, y / vY, z / vZ);
	};
	Vec3<T> div(Vec3<T>& v) {
		return Vec3<T>(x / v.x, y / v.y, z / v.z);
	};
public:
	Vec3<T> mul(T v) {
		return Vec3<T>(x * v, y * v, z * v);
	};
	Vec3<T> mul(T vX, T vY, T vZ) {
		return Vec3<T>(x * vX, y * vY, z * vZ);
	};
	Vec3<T> mul(Vec3<T>& v) {
		return Vec3<T>(x * v.x, y * v.y, z * v.z);
	};
public:
	Vec3<T> add(T v) {
		return Vec3<T>(x + v, y + v, z + v);
	};
	Vec3<T> add(T vX, T vY, T vZ) {
		return Vec3<T>(x + vX, y + vY, z + vZ);
	};
	Vec3<T> add(Vec3<T>& v) {
		return Vec3<T>(x + v.x, y + v.y, z + v.z);
	};
public:
	Vec3<T> sub(T v) {
		return Vec3<T>(x - v, y - v, z - v);
	};
	Vec3<T> sub(T vX, T vY, T vZ) {
		return Vec3<T>(x - vX, y - vY, z - vZ);
	};
	Vec3<T> sub(Vec3<T>& v) {
		return Vec3<T>(x - v.x, y - v.y, z - v.z);
	};
};

template<typename T>
class Vec4 : public Vec3<T> {
public:
	T x = 0;
	T y = 0;
	T z = 0;
	T w = 0;
public:
	Vec4(T x = 0, T y = 0, T z = 0, T w = 0) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	};
public:
	Vec4<T>& operator = (const Vec4<T>& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	};
public:
	bool operator == (const Vec4<T>& v) {
		return (
			this->x == v.x && 
			this->y == v.y && 
			this->z == v.z && 
			this->w == v.w
		);
	};
	bool operator != (const Vec4<T>& v) {
		return (
			this->x != v.x || 
			this->y != v.y || 
			this->z != v.z || 
			this->w != v.w
		);
	};
public:
	Vec4<T> div(T v) {
		return Vec4<T>(x / v, y / v, z / v, w / v);
	};
	Vec4<T> div(T vX, T vY, T vZ, T vW) {
		return Vec4<T>(x / vX, y / vY, z / vZ, w / vW);
	};
	Vec4<T> div(Vec4<T>& v) {
		return Vec4<T>(x / v.x, y / v.y, z / v.z, w / v.w);
	};
public:
	Vec4<T> mul(T v) {
		return Vec4<T>(x * v, y * v, z * v, w * v);
	};
	Vec4<T> mul(T vX, T vY, T vZ, T vW) {
		return Vec4<T>(x * vX, y * vY, z * vZ, w * vW);
	};
	Vec4<T> mul(Vec4<T>& v) {
		return Vec4<T>(x * v.x, y * v.y, z * v.z, w * v.w);
	};
public:
	Vec4<T> add(T v) {
		return Vec4<T>(x + v, y + v, z + v, w + v);
	};
	Vec4<T> add(T vX, T vY, T vZ, T vW) {
		return Vec4<T>(x + vX, y + vY, z + vZ, w + vW);
	};
	Vec4<T> add(Vec4<T>& v) {
		return Vec4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
	};
public:
	Vec4<T> sub(T v) {
		return Vec4<T>(x - v, y - v, z - v, w - v);
	};
	Vec4<T> sub(T vX, T vY, T vZ, T vW) {
		return Vec4<T>(x - vX, y - vY, z - vZ, w - vW);
	};
	Vec4<T> sub(Vec4<T>& v) {
		return Vec4<T>(x - v.x, y - v.y, z - v.z, w - v.z);
	};
};