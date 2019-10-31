#pragma once

namespace	epion
{
	struct	Color	final
	{
		float	r;
		float	g;
		float	b;
		float	a;
		Color() {};
		constexpr	Color(float	r_, float	g_, float	b_, float	a_) :r(r_), g(g_), b(b_), a(a_) {};
	};

	struct	FixColor
	{
		static	constexpr	Color	Red = { 1.0f,	0.0f,	0.0f,	1.0f };
		static	constexpr	Color	Blue = { 0.0f,	0.0f,	1.0f,	1.0f };
		static	constexpr	Color	Green = { 0.0f,	0.0f,	0.0f,	1.0f };
		static	constexpr	Color	Yellow = { 1.0f,	1.0f,	0.0f,	1.0f };
		static	constexpr	Color	White = { 1.0f,	1.0f,	1.0f,	1.0f };
		static	constexpr	Color	Black = { 0.0f,	0.0f,	0.0f,	1.0f };
		static	constexpr	Color	LightSteelBlue = { 0.69f,	0.77f,	0.87f,	0.3f };
		static	constexpr	Color	Gold = { 1.0f,	0.84f,	0.00f,	1.0f };
		static	constexpr	Color	SkyBlue = { 0.53f,	0.81f,	0.92f,	1.0f };

	};
}