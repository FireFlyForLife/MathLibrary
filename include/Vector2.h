/// The vector class inherits from matrix, so it needs to include matrix, but matrix has methods with vector3.
/// So what I do is include the Matrix.h, which then defines 'VECTOR_DONT_INCUDE_MATRIX_FILE' and includes Vector3.h to get the definition for function implementations
// ReSharper disable once CppMissingIncludeGuard
#ifndef VECTOR_DONT_INCUDE_MATRIX_FILE
#include "Matrix.h"
#else

#include <Impl/VectorImpl.h>

namespace Math {
	class Vector2 : public Matrix<2, 1>
	{
	public:
		using MatrixType = Matrix<2, 1>;

		static constexpr unsigned int Size = MatrixType::Rows;

		//TODO: Figure out if I want this, or a traditional getter/setter
		Math::_Impl_::matrix_variable_proxy<Vector2> x{ *this, 0, 0 };
		Math::_Impl_::matrix_variable_proxy<Vector2> y{ *this, 1, 0 };


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

		///Create a vec2, discard the z axis
		explicit Vector2(const Matrix<3, 1>& vec3)
		{
			x = vec3.at(0, 0);
			y = vec3.at(1, 0);
		}

		///Create a vec2, discard the z and w axis
		explicit Vector2(const Matrix<4, 1>& vec4)
		{
			x = vec4.at(0, 0);
			y = vec4.at(1, 0);
		}

		//TODO: Figure out if writing the operator overload out will give a performance improvement
		Vector2 operator+(const Vector2& b) const
		{
			auto matrix = MatrixType::operator+(b);
			Vector2 vec{ matrix };

			return vec;
		}

		//TODO: Figure out if writing the operator overload out will give a performance improvement
		Vector2 operator-(const Vector2& b) const
		{
			auto matrix = MatrixType::operator-(b);
			Vector2 vec{ matrix };

			return vec;
		}

		//TODO: Figure out if I want a have an overload with the matrix reprisentation 2,1 and 1,2
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

		float& operator[](unsigned int index)
		{
			return at(index, 0);
		}

		const float& operator[](unsigned int index) const
		{
			return at(index, 0);
		}
	};
}
#endif
