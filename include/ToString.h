#pragma once
#include <string>
#include "Matrix.h"
#include "Vectors.h"
#include <fstream>

namespace Math
{
	namespace _Impl_
	{
		template<unsigned width, unsigned height>
		std::string toStr(const Matrix<width, height>& matrix)
		{
			return "";
		}
	}

	template<typename T>
	std::string ToString(const T& t)
	{
//#if defined(_DEBUG) && !defined(MATH_DISABLE_WARNINGS)
//		throw std::exception((std::string("Unknown Type: ") + typeid(t).name() + ". Could not convert to std::string.").c_str());
//#endif
		auto str = _Impl_::toStr(t);

		return std::string("Unknown Type: ") + typeid(t).name() + ". Could not convert to std::string.";
	}

	template<>
	inline std::string ToString(const Vector2& vec)
	{
		using namespace std::string_literals;
		return "Vec2("s + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ")";
	}

	template<unsigned rows, unsigned columns>
	std::string ToString(const Matrix<rows, columns>& t)
	{
		//TODO: Add width calculation
		std::string matrix;
		for (unsigned c = 0; c < columns; c++)
		{
			std::string line = "[ ";
			for(unsigned r = 0; r < rows; r++)
			{
				line += std::to_string(t[r][c]) + ' ';
			}
			line += "]\n";
			matrix += line;
		}

		return matrix;
	}

	
}
