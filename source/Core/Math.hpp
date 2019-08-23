#ifndef KFTG_MATH
#define KFTG_MATH

#include "types.hpp"
#include "string.hpp"

namespace KFTG
{

// hash: one_at_a_time
u32 hash (const string &key);

struct Vec2
{
	Vec2 (f32 a, f32 b) : x (a), y (b) {}

	bool  operator == (const Vec2 &other)
	{ return x == other.x && y == other.y; }

	bool  operator != (const Vec2 &other)
	{ return *this == other; }

	Vec2& operator +  (const Vec2 &other);
	Vec2& operator += (const Vec2 &other);
	Vec2& operator -  (const Vec2 &other);
	Vec2& operator -= (const Vec2 &other);
	Vec2& operator *  (const f32  &other);
	Vec2& operator *= (const f32  &other);
	Vec2& operator /  (const f32  &other);
	Vec2& operator /= (const f32  &other);

	f32 x;
	f32 y;
};

// AABB collision detection
inline bool AABB (Vec2 a1, Vec2 a2, Vec2 b1, Vec2 b2)
{
	return a1.x <= b1.x && a1.y <= b1.y
		&& a2.x >= b1.x && a2.y >= b2.y;
}

}

#endif // MATH