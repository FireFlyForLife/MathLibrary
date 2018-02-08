#pragma once
#include "Matrix.h"
#include <functional>

//A namespace with some private implementation details, do not directly use the contents in your code
namespace Math {
	namespace _Impl_ {
		template<typename Vec>
		class vector_variable_proxy
		{
			Vec& vec;
			int x, y;

		public:
			vector_variable_proxy(Vec& vec, int x, int y) : vec(vec), x(x), y(y) {}

			inline vector_variable_proxy& operator=(float other)
			{
				vec.at(x, y) = other;

				return *this;
			}

			// ReSharper disable once CppNonExplicitConversionOperator
			inline operator float() const { return vec.at(x, y); }
		};
	}
}

class Vector2 : public Matrix<1, 2>
{
	using MatrixType = Matrix<1, 2>;

public:
	static constexpr unsigned int Size = 2;

	//TODO: Figure out if I want this, or a traditional getter/setter
	
	Math::_Impl_::vector_variable_proxy<Vector2> x{ *this, 0, 0 };
	Math::_Impl_::vector_variable_proxy<Vector2> y{ *this, 0, 1 };


	Vector2()
	{
		//Just so I know when I fucked up
		static_assert(std::is_base_of_v<MatrixType, std::remove_pointer_t<decltype(this)>>, 
			"The MatrixType does not match up with the matrix type which the vector inherited from!");
	}

	Vector2(MatrixType matrix)
		: Matrix(matrix)
	{
		//Just so I know when I fucked up
		static_assert(std::is_base_of_v<MatrixType, std::remove_pointer_t<decltype(this)>>,
			"The MatrixType does not match up with the matrix type which the vector inherited from!");
	}

	Vector2(float x_, float y_)
	{
		x = x_;
		y = y_;

		//Just so I know when I fucked up
		static_assert(std::is_base_of_v<MatrixType, std::remove_pointer_t<decltype(this)>>,
			"The MatrixType does not match up with the matrix type which the vector inherited from!");
	}

	//TODO: Figure out if writing all the operator overloads out will have a performance improvement

	Vector2 operator+(const Vector2& b) const
	{
		auto matrix = MatrixType::operator+(b);
		Vector2 vec {matrix};

		return vec;
	}

	Vector2 operator-(const Vector2& b) const
	{
		auto matrix = MatrixType::operator-(b);
		Vector2 vec{ matrix };

		return vec;
	}

	Vector2 operator*(const Vector2& b) const
	{
		const auto& a = *this;

		return {
			a.x * b.x,
			a.y * b.y
		};
	}

	Vector2 operator*(float scalar) const
	{
		const auto& a = *this;

		return{
			a.x * scalar,
			a.y * scalar
		};
	}

	Vector2 operator/(const Vector2& b) const
	{
		const auto& a = *this;
		
		return {
			a.x / b.x,
			a.y / b.y
		};
	}

	//NOTE: Does not check for divided by zero exceptions
	Vector2 operator/(float scalar) const
	{
		const auto& a = *this;

		return {
			a.x / scalar,
			a.y / scalar
		};
	}
};

class Vector3 : public Matrix<1, 3>
{
	using MatrixType = Matrix<1, 3>;

public:
	static constexpr unsigned int Size = 2;

	//TODO: Figure out if I want this, or a traditional getter/setter

	Math::_Impl_::vector_variable_proxy<Vector3> x{ *this, 0, 0 };
	Math::_Impl_::vector_variable_proxy<Vector3> y{ *this, 0, 1 };
	Math::_Impl_::vector_variable_proxy<Vector3> z{ *this, 0, 2 };


	Vector3()
	{
		//Just so I know when I fucked up
		static_assert(std::is_base_of_v<MatrixType, std::remove_pointer_t<decltype(this)>>,
			"The MatrixType does not match up with the matrix type which the vector inherited from!");
	}

	Vector3(MatrixType matrix)
		: Matrix(matrix)
	{
		//Just so I know when I fucked up
		static_assert(std::is_base_of_v<MatrixType, std::remove_pointer_t<decltype(this)>>,
			"The MatrixType does not match up with the matrix type which the vector inherited from!");
	}

	Vector3(float x_, float y_, float z_)
	{
		x = x_;
		y = y_;
		z = z_;

		//Just so I know when I fucked up
		static_assert(std::is_base_of_v<MatrixType, std::remove_pointer_t<decltype(this)>>,
			"The MatrixType does not match up with the matrix type which the vector inherited from!");
	}

	//TODO: Figure out if writing all the operator overloads out will have a performance improvement

	Vector3 operator+(const Vector3& b) const
	{
		auto matrix = MatrixType::operator+(b);
		Vector3 vec{ matrix };

		return vec;
	}

	Vector3 operator-(const Vector3& b) const
	{
		auto matrix = MatrixType::operator-(b);
		Vector3 vec{ matrix };

		return vec;
	}

	Vector3 operator*(const Vector3& b) const
	{
		const auto& a = *this;

		return {
			a.x * b.x,
			a.y * b.y,
			a.z * b.z
		};
	}

	Vector3 operator*(float scalar) const
	{
		const auto& a = *this;

		return{
			a.x * scalar,
			a.y * scalar,
			a.z * scalar
		};
	}

	Vector3 operator/(const Vector3& b) const
	{
		const auto& a = *this;

		return {
			a.x / b.x,
			a.y / b.y,
			a.z / b.z
		};
	}

	//NOTE: Does not check for divided by zero exceptions
	Vector3 operator/(float scalar) const
	{
		const auto& a = *this;

		return {
			a.x / scalar,
			a.y / scalar,
			a.z / scalar
		};
	}
};
