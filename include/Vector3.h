/// The vector class inherits from matrix, so it needs to include matrix, but matrix has methods with vector3.
/// So what I do is include the Matrix.h, which then defines 'VECTOR_DONT_INCUDE_MATRIX_FILE' and includes Vector3.h to get the definition for function implementations
// ReSharper disable once CppMissingIncludeGuard
#ifndef VECTOR_DONT_INCUDE_MATRIX_FILE
#include "Matrix.h"
#else

#include <Impl/VectorImpl.h>

namespace Math {
	//TODO: Update the other Vector classes as well
	class Vector3 : public Matrix<3, 1>
	{
	public:
		using MatrixType = Matrix<3, 1>;

		static constexpr unsigned int Size = MatrixType::Rows;

		//TODO: Figure out if I want this, or a traditional getter/setter
		Math::_Impl_::matrix_variable_proxy<Vector3> x{ *this, 0, 0 };
		Math::_Impl_::matrix_variable_proxy<Vector3> y{ *this, 1, 0 };
		Math::_Impl_::matrix_variable_proxy<Vector3> z{ *this, 2, 0 };

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

		///Create a vector3 from a vector4, discard the w axis
		explicit Vector3(const Matrix<4, 1>& vec4)
		{
			x = vec4.at(0, 0);
			y = vec4.at(1, 0);
			z = vec4.at(2, 0);
		}

		explicit Vector3(const Matrix<2, 1>& vec2, float z_ = 0.f)
		{
			x = vec2.at(0, 0);
			y = vec2.at(1, 0);
			z = z_;
		}

		Vector3(const Vector3& vec) = default;
		Vector3(Vector3&&) = default;
		Vector3& operator=(const Vector3& vec) = default;
		Vector3& operator=(Vector3&&) = default;



#pragma region Operator overloads
		Vector3 operator+(const Vector3& b) const
		{
			return {
				x + b.x,
				y + b.y,
				z + b.z
			};
		}

		Vector3& operator+=(const Vector3& b)
		{
			x += b.x;
			y += b.y;
			z += b.z;

			return *this;
		}

		Vector3 operator-(const Vector3& b) const
		{
			return {
				x - b.x,
				y - b.y,
				z - b.z
			};
		}

		Vector3& operator-=(const Vector3& b)
		{
			x -= b.x;
			y -= b.y;
			z -= b.z;

			return *this;
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

		//TODO: Should this be a scalar?
		Vector3& operator*=(const Vector3& b)
		{
			x *= b.x;
			y *= b.y;
			z *= b.z;

			return *this;
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

		Vector3& operator*=(float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;

			return *this;
		}

		///NOTE: Does not check for an DividedByZero
		Vector3 operator/(const Vector3& b) const
		{
			const auto& a = *this;

			return {
				a.x / b.x,
				a.y / b.y,
				a.z / b.z
			};
		}

		///NOTE: Does not check for an DividedByZero
		Vector3& operator/=(const Vector3& b)
		{
			x /= b.x;
			y /= b.y;
			z /= b.z;

			return *this;
		}

		///NOTE: Does not check for divided by zero exceptions
		Vector3 operator/(float scalar) const
		{
			const auto& a = *this;

			return {
				a.x / scalar,
				a.y / scalar,
				a.z / scalar
			};
		}

		///NOTE: Does not check for an DividedByZero
		Vector3& operator/=(float scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;

			return *this;
		}

		float& operator[](unsigned int index)
		{
			return at(index, 0);
		}

		const float& operator[](unsigned int index) const
		{
			return at(index, 0);
		}
#pragma endregion 

		float SquareMagnitude() const
		{
			return x*x + y*y + z*z;
		}

		///Alias for SquareMagnitude
		float Magnitude2() const
		{
			return x*x + y*y + z*z;
		}

		float Magnitude() const
		{
			float mag2 = SquareMagnitude();
			return sqrtf(mag2);
		}

		void Normalize()
		{
			float mag = Magnitude();
			(*this) /= mag;
		}

		Vector3 Normalized() const
		{
			float mag = Magnitude();
			return *this / mag;
		}

		void Clear()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		Vector3 Cross(const Vector3& b) const
		{
			//TODO: Figure out why this works (or doesn't)

			return {
				y*b.z - b.y*z,
				z*b.x - b.z*x,
				x*b.y - b.x*y
			};
		}

		float Dot(const Vector3& b) const
		{
			return x*b.x + y*b.y + z*b.z;
		}

		Vector3 Slerp(float fact, const Vector3& end) const
		{
			const Vector3& start = *this;
			// Dot product - the cosine of the angle between 2 vectors.
			float dot = start.Dot(end);
			// Clamp it to be in the range of Acos()
			// This may be unnecessary, but floating point
			// precision can be a fickle mistress.
			dot = Math::Clampf(dot, -1.0f, 1.0f);
			// Acos(dot) returns the angle between start and end,
			// And multiplying that by percent returns the angle between
			// start and the final result.
			float theta = acosf(dot)*fact;
			Vector3 RelativeVec = end - start*dot;
			RelativeVec.Normalize();     // Orthonormal basis
										 // The final result.
			return (start*cosf(theta)) + (RelativeVec*sinf(theta));
		}
	};
}

#endif
