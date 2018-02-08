#pragma once
#include <limits>
#include <string>
#include <MathConstants.h>

namespace Math {
	template<typename T>
	inline T MoveTowards(T from, T to, T maxStep) {
		T diff = to - from;
		if (diff >= 0)
			return from + fmin(diff, maxStep);
		else
			return from + fmax(diff, -maxStep);
	}

	//Clamp a the value 'val' between 'min' and 'max'
	template<typename T>
	inline T Clamp(T val, T min, T max) {
		return fmin(max, fmax(val, min));
	}

	//Alias to Math::Clamp<float>
	inline float Clampf(float val, float min, float max) {
		return Clamp<float>(val, min, max);
	}
	
	inline bool fequals(float a, float b, float epsilon = std::numeric_limits<float>::epsilon() * 1000)
	{
		return abs(a - b) < epsilon;
	}
	
	//TODO: Write Lerp

	/// Alias for multiplying with DEG2RAD
	/// @returns the amount of radians for the parameter 'degrees'
	template<typename T>
	inline T DegToRad(T degrees)
	{
		return degrees * DEG2RAD;
	}

	/// Alias for multiplying with DEG2RAD
	/// @returns the amount of degrees for the parameter 'radians'
	template<typename T>
	inline T RadToDeg(T radians)
	{
		return radians * RAD2DEG;
	}


	template<typename T>
	constexpr inline T Sum(T num)
	{
		return num;
	}

	template<typename T, typename... Ts>
	constexpr inline T Sum(T num, Ts... nums)
	{
		return num + Sum(nums...);
	}

	template<typename... Ts>
	constexpr inline auto Average(Ts... ts)
	{
		using T = std::common_type_t<Ts...>;

		constexpr T sz = sizeof...(Ts);
		T total = Sum(ts...);

		return total / sz;
	}
}
