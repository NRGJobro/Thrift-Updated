#pragma once
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

class Rect : public Vec4<float> {
public:
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float w = 0.f;
public:
	Rect(float top = 0.f, float left = 0.f, float right = 0.f, float bottom = 0.f) {
		this->x = top;
		this->y = left;
		this->z = right;
		this->w = bottom;
	};
public:
	auto get(void) -> float* {
		float v[] = { this->x, this->y, this->z, this->w };
		return v;
	};
};

class Color {
public:
	float r = 255.f;
	float g = 255.f;
	float b = 255.f;
	float a = 1.f;
public:
	Color(float r = 255.f, float g = 255.f, float b = 255.f, float a = 1.f) {
		this->r = r / 255.f;
		this->g = g / 255.f;
		this->b = b / 255.f;
		this->a = a;
	};
public:
	auto get(void) -> float* {
		float v[] = { this->r, this->g, this->b, this->a };
		return v;
	};
};