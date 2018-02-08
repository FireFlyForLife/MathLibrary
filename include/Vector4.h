/// The vector class inherits from matrix, so it needs to include matrix, but matrix has methods with vector3.
/// So what I do is include the Matrix.h, which then defines 'VECTOR_DONT_INCUDE_MATRIX_FILE' and includes Vector3.h to get the definition for function implementations
// ReSharper disable once CppMissingIncludeGuard
#ifndef VECTOR_DONT_INCUDE_MATRIX_FILE
#include "Matrix.h"
#else
#include <Impl/VectorImpl.h>


namespace Math {
	class Vector4 : public Matrix<4, 1>
	{
	public:
		using MatrixType = Matrix<4, 1>;

		static constexpr unsigned int Size = MatrixType::Rows;

		//TODO: Figure out if I want this, or a traditional getter/setter
		Math::_Impl_::matrix_variable_proxy<Vector4> x{ *this, 0, 0 };
		Math::_Impl_::matrix_variable_proxy<Vector4> y{ *this, 1, 0 };
		Math::_Impl_::matrix_variable_proxy<Vector4> z{ *this, 2, 0 };
		Math::_Impl_::matrix_variable_proxy<Vector4> w{ *this, 3, 0 };


		Vector4()
		{
			//Just so I know when I fucked up
			static_assert(std::is_base_of_v<MatrixType, std::remove_pointer_t<decltype(this)>>,
				"The MatrixType does not match up with the matrix type which the vector inherited from!");
		}

		Vector4(MatrixType matrix)
			: Matrix(matrix)
		{
			//Just so I know when I fucked up
			static_assert(std::is_base_of_v<MatrixType, std::remove_pointer_t<decltype(this)>>,
				"The MatrixType does not match up with the matrix type which the vector inherited from!");
		}

		Vector4(float x_, float y_, float z_, float w_)
		{
			x = x_;
			y = y_;
			z = z_;
			w = w_;

			//Just so I know when I fucked up
			static_assert(std::is_base_of_v<MatrixType, std::remove_pointer_t<decltype(this)>>,
				"The MatrixType does not match up with the matrix type which the vector inherited from!");
		}

		///Create a vec4 from a vec2 and z and w
		explicit Vector4(const Matrix<2, 1>& vec2, float z_ = 0.f, float w_ = 0.f)
		{
			x = vec2.at(0, 0);
			y = vec2.at(1, 0);
			z = z_;
			w = w_;
		}

		///Create a vec4 from a vec2 and z and w
		explicit Vector4(const Matrix<3, 1>& vec3, float w_ = 0.f)
		{
			x = vec3.at(0, 0);
			y = vec3.at(1, 0);
			z = vec3.at(2, 0);
			w = w_;
		}

		//TODO: Figure out if writing the operator overload out will give a performance improvement
		Vector4 operator+(const Vector4& b) const
		{
			auto matrix = MatrixType::operator+(b);
			Vector4 vec{ matrix };

			return vec;
		}

		//TODO: Figure out if writing the operator overload out will give a performance improvement
		Vector4 operator-(const Vector4& b) const
		{
			auto matrix = MatrixType::operator-(b);
			Vector4 vec{ matrix };

			return vec;
		}

		Vector4 operator*(const Vector4& b) const
		{
			const auto& a = *this;

			return {
				a.x * b.x,
				a.y * b.y,
				a.z * b.z,
				a.w * b.w
			};
		}

		Vector4 operator*(float scalar) const
		{
			const auto& a = *this;

			return{
				a.x * scalar,
				a.y * scalar,
				a.z * scalar,
				a.w * scalar
			};
		}

		Vector4 operator/(const Vector4& b) const
		{
			const auto& a = *this;

			return {
				a.x / b.x,
				a.y / b.y,
				a.z / b.z,
				a.w / b.w
			};
		}

		//NOTE: Does not check for divided by zero exceptions
		Vector4 operator/(float scalar) const
		{
			const auto& a = *this;

			return {
				a.x / scalar,
				a.y / scalar,
				a.z / scalar,
				a.w * scalar
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
