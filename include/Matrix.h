#pragma once
#include <array>
#include <cassert>
#include "MathFunctions.h"
#include "MathConstants.h"
#include <string>

namespace Math {
	//Type aliases for ease of use
	template<unsigned, unsigned> struct Matrix;
	using Matrix3 = Matrix<3, 3>;
	using Matrix33 = Matrix<3, 3>;
	using Matrix3x3 = Matrix<3, 3>;
	using Mat3 = Matrix<3, 3>;
	using Matrix4 = Matrix<4, 4>;
	using Matrix44 = Matrix<4, 4>;
	using Matrix4x4 = Matrix<4, 4>;
	using Mat4 = Matrix<4, 4>;

	template<unsigned R> struct Vector_t;
	using Vector4 = Vector_t<4>;
	using Vector3 = Vector_t<3>;
	using Vector2 = Vector_t<2>;

	template<unsigned int rows, unsigned int columns = rows>
	struct matrix_base
	{
		static constexpr unsigned int Rows = rows;
		static constexpr unsigned int Columns = columns;

		union
		{
			std::array<std::array<float, Columns>, Rows> m = {};
			std::array<float, Rows * Columns> f;
		};
	};

	template<>
	struct matrix_base<2, 1>
	{
		static constexpr unsigned int Rows = 2;
		static constexpr unsigned int Columns = 1;

		union
		{
			struct
			{
				float x;
				float y;
			};
			std::array<std::array<float, Columns>, Rows> m = {};
			std::array<float, Rows * Columns> f;
		};
	};

	template<>
	struct matrix_base<3, 1>
	{
		static constexpr unsigned int Rows = 3;
		static constexpr unsigned int Columns = 1;

		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};
			std::array<std::array<float, Columns>, Rows> m = {};
			std::array<float, Rows * Columns> f;
		};
	};

	template<>
	struct matrix_base<4, 1>
	{
		static constexpr unsigned int Rows = 4;
		static constexpr unsigned int Columns = 1;

		union
		{
			std::array<std::array<float, Columns>, Rows> m = {};
			std::array<float, Rows * Columns> f;
			struct
			{
				float x;
				float y;
				float z;
				float w;
			};
		};
	};

	template<unsigned int rows>
	struct Vector_t : public matrix_base<rows, 1>
	{
		using Super = matrix_base<rows, 1>;
		using Super::Rows;
		using Super::Columns;
		using Super::m;
		using Super::f;

		//TODO: make the methods for all the vector types
		Vector_t()
		{
			f = {};
		}

		template<typename = std::enable_if_t<Rows == 2>>
		Vector_t(float x, float y)
		{
			static_assert(Rows == 2, "Calling the Vector2 constructor when this is not a vec2! more info: " __FUNCSIG__);

			f = { x, y };
		}

		template<typename = std::enable_if_t<Rows == 3>>
		Vector_t(float x, float y, float z)
		{
			static_assert(Rows == 3, "Calling the Vector3 constructor when this is not a vec2! more info: " __FUNCSIG__);

			f = { x, y, z };
		}

		template<typename = std::enable_if_t<Rows == 4>>
		Vector_t(float x, float y, float z, float w)
		{
			static_assert(Rows == 4, "Calling the Vector4 constructor when this is not a vec2! more info: " __FUNCSIG__);

			f = { x, y, z, w };
		}

		//TODO: Remove this, if you have a typedef this becomes a huge pain to deal with
		/*template<typename ...Args>
		Vector_t(Args... args)
		{
			static_assert(sizeof...(Args) == Rows, "Not the right size!");
			static_assert(std::is_convertible_v<std::common_type_t<Args...>, float>, "Argument type is not a number!");

			f = { { static_cast<float>(args)... } };
		}*/

#pragma region
		Vector_t operator+(const Vector_t& b) const
		{
			Vector_t ret;

			for (int i = 0; i < Rows; ++i)
			{
				ret.f[i] = f[i] + b.f[i];
			}

			return ret;
		}

		Vector_t operator+=(const Vector_t& b)
		{
			auto vec = *this +  b;
			f = vec.f;

			return *this;
		}

		Vector_t operator-(const Vector_t& b) const
		{
			Vector_t ret;

			for (int i = 0; i < Rows; ++i) {
				ret.f[i] = f[i] - b.f[i];
			}

			return ret;
		}

		Vector_t operator-=(const Vector_t& b)
		{
			auto vec = *this - b;
			f = vec.f;

			return *this;
		}

		Vector_t operator*(const Vector_t& b) const
		{
			Vector_t ret;

			for (int i = 0; i < Rows; ++i) {
				ret.f[i] = f[i] * b.f[i];
			}

			return ret;
		}

		Vector_t operator*=(const Vector_t& b)
		{
			auto vec = *this *  b;
			f = vec.f;

			return *this;
		}

		Vector_t operator*(float b) const
		{
			Vector_t ret;

			for (int i = 0; i < Rows; ++i) {
				ret.f[i] = f[i] * b;
			}

			return ret;
		}

		Vector_t operator*=(float b)
		{
			auto vec = *this *  b;
			f = vec.f;

			return *this;
		}

		Vector_t operator/(float b) const
		{
			Vector_t ret;

			for (int i = 0; i < Rows; ++i) {
				ret.f[i] = f[i] / b;
			}

			return ret;
		}

		Vector_t operator/=(float b)
		{
			auto vec = *this /  b;
			f = vec.f;

			return *this;
		}

		bool operator==(const Vector_t& b) const
		{
			for (int r = 0; r < Rows; ++r) 
			{
				for (int c = 0; c < Columns; ++c)
				{
					if (!fequals(m[r][c], b.m[r][c]))
						return false;
				}
			}

			return true;
		}
#pragma endregion 
		float SquareMagnitude() const
		{
			float total = 0.f;
			for (int i = 0; i < Rows; ++i)
			{
				total += f[i] * f[i];
			}
			return total;
		}

		///Alias for SquareMagnitude
		float Magnitude2() const
		{
			return SquareMagnitude();
		}

		float Magnitude() const
		{
			return sqrtf(SquareMagnitude());
		}

		void Normalize()
		{
			float mag = Magnitude();
			assert(mag != 0);
			*this /= mag;
		}

		Vector_t Normalized() const
		{
			float mag = Magnitude();
			assert(mag != 0);
			return *this / mag;
		}

		void Clear()
		{
			f = {};
		}

		float Dot(const Vector_t& b) const
		{
			float total = 0.0f;

			for (int i = 0; i < Rows; ++i)
			{
				total += f[i] * b.f[i];
			}

			return total;
		}

		///@Returns a vector of size 'NewI' and will try to copy the contents over from the current vector
		template<unsigned int NewI>
		Vector_t<NewI> As() const
		{
			Vector_t<NewI> vector;
			
			unsigned int min_size = std::min(NewI, Rows);
			for (int i = 0; i < min_size; ++i)
			{
				vector.f[i] = f[i];
			}

			return vector;
		}

		///@Returns a vector of size 'NewI' and will try to copy the contents over from the current vector,
		/// If there are any new cells, then the value assigned will be @default_value .
		template<unsigned int NewI>
		Vector_t<NewI> As(float default_value) const
		{
			Vector_t<NewI> vector;
			for (unsigned int i = 0; i < NewI; ++i)
			{
				vector.f[i] = default_value;
			}

			unsigned int min_size = std::min(NewI, Rows);
			for (int i = 0; i < min_size; ++i) {
				vector.f[i] = f[i];
			}

			return vector;
		}
	};

	template<>
	struct Vector_t<3> : public matrix_base<3, 1>
	{
		using Super = matrix_base<3, 1>;
		using Super::m;
		using Super::f;
		using Super::x;
		using Super::y;
		using Super::z;

		Vector_t() 
		{}
		//template<typename ...Args, typename = std::enable_if_t<sizeof...(Args) == Rows>>
		Vector_t(float x, float y, float z)
		{
			//static_assert(sizeof...(Args) == Rows, "Not the right size!");
			//static_assert(std::is_convertible_v<std::common_type_t<Args...>, float>, "Argument type is not a number!");

			f = { x, y, z };
		}

		Vector_t(float floats[3])
		{
			f = { floats[0], floats[1], floats[2] };
		}

		Vector_t(std::array<float, 3> floats)
		{
			f = floats;
		}

#pragma region Operator overloads
		Vector3 operator+(const Vector3& b) const;

		Vector3& operator+=(const Vector3& b);

		Vector3 operator-(const Vector3& b) const;

		Vector3& operator-=(const Vector3& b);

		Vector3 operator*(const Vector3& b) const;

		//TODO: Should this be a scalar?
		Vector3& operator*=(const Vector3& b);

		Vector3 operator*(float scalar) const;

		Vector3& operator*=(float scalar);

		///NOTE: Does not check for an DividedByZero
		Vector3 operator/(const Vector3& b) const;

		///NOTE: Does not check for an DividedByZero
		Vector3& operator/=(const Vector3& b);

		///NOTE: Does not check for divided by zero exceptions
		Vector3 operator/(float scalar) const;

		///NOTE: Does not check for an DividedByZero
		Vector3& operator/=(float scalar);

		float& operator[](unsigned int index)
		{
			return f[index];
		}

		const float& operator[](unsigned int index) const
		{
			return f[index];
		}
#pragma endregion 

		float SquareMagnitude() const;

		///Alias for SquareMagnitude
		float Magnitude2() const;

		float Magnitude() const;

		void Normalize();

		Vector3 Normalized() const;

		void Clear();

		Vector3 Cross(const Vector3& b) const;

		float Dot(const Vector3& b) const;

		Vector3 Slerp(float fact, const Vector3& end) const;

		///@Returns a vector of size 'NewI' and will try to copy the contents over from the current vector
		template<unsigned int NewI>
		Vector_t<NewI> As() const
		{
			Vector_t<NewI> vector;

			unsigned int min_size = std::min(NewI, Rows);
			for (int i = 0; i < min_size; ++i) {
				vector.f[i] = f[i];
			}

			return vector;
		}
	};

	//TODO: Write a specialization for the 4x4 matrix for effecienty
	template<unsigned int rows, unsigned int columns = rows>
	struct Matrix : public matrix_base<rows, columns>
	{
		using Super = matrix_base<rows, columns>;
		using Super::m;
		using Super::f;
		using Super::Rows;
		using Super::Columns;

		///To be able to inspect the dimensions in the debugger, we need a member variable.
		///This will however mean that our sizeof is no longer just 3 floats
#if defined(_DEBUG) && defined(MATH_SHOW_MATRIX_DIMENSIONS)
		unsigned int _matrix_rows = rows;
		unsigned int _matrix_columns = columns;
#endif

		static constexpr bool IsSquare()
		{
			return Rows == Columns;
		}

		//std::array<std::array<float, Columns>, Rows> m = { {} };

		///Default constructor which makes this matrix an Identity matrix
		Matrix()
		{
			*this = Matrix<Rows, Columns>::Identity;
		}

		///constructor which scales an Identity matrix by scalar f
		Matrix(float f)
		{
			if (Math::fequals(f, 0.0f) || !IsSquare())
				return;

			for(int i = 0; i < Rows; i++)
			{
				m[i][i] = f;
			}
		}

		template<typename ...Args, typename = std::enable_if_t<Columns == 1>>
		Matrix(Args... args)
		{
			static_assert(sizeof...(Args) == rows, "Not the right size!");
			static_assert(std::is_convertible_v<std::common_type_t<Args...>>, "Argument type is not a number!");

			f = { { static_cast<float>(args)... } };
		}

		template<typename = std::enable_if_t<Columns == 1>>
		Matrix(std::initializer_list<float> nums)
		{
			auto it = nums.begin();
			for (int num = 0; num < rows; ++num) {
				f[num++] = *it;
				++it;
			}
		}

		//TODO: Figure out if I can do this calculation sometimes at compile time
		template<typename = std::enable_if_t<Columns != 1>>
		Matrix(std::initializer_list<std::initializer_list<float>> init_list)
		{
			auto list_height = init_list.size();
			auto it = init_list.begin();

			auto list_width = (*it).size();
#if defined(_DEBUG) && !defined(MATH_DISABLE_WARNINGS)
			assert((list_height == Rows || list_width == Columns) && "the initializer list height or width does not match up with the matrix width or height");

			//check each horizontal line to see if they are the same size
			auto check_it = init_list.begin();
			for (++check_it /*increment because we already saved the first item*/; check_it != init_list.end(); ++check_it)
			{
				auto horizontal_list = *check_it;
				assert((list_width == horizontal_list.size()) && "The initializer list width is not a consistent number");
			}
#endif
			int vertical = 0;
			for (; it != init_list.end(); ++it)
			{
				int horizontal = 0;
				for (auto it_horizontal = it->begin(); it_horizontal != it->end(); ++it_horizontal)
				{
					float f = *it_horizontal;

					m[vertical][horizontal] = f;

					horizontal++;
				}
				vertical++;
			}
		}

		float& at(unsigned int row, unsigned int column)
		{
			return m.at(row).at(column);
		}

		const float& at(unsigned int row, unsigned int column) const
		{
			return m.at(row).at(column);
		}

		float* data()
		{
			return &f[0];
		}

		const float* data() const
		{
			return &f[0];
		}

		std::array<float, Columns>& operator[](unsigned int i)
		{
			return m[i];
		}

		const std::array<float, Columns>& operator[](unsigned int i) const
		{
			return m[i];
		}

		Matrix<Rows, Columns> operator+(const Matrix<Rows, Columns>& b) const
		{
			const auto& a = *this;
			Matrix<Rows, Columns> matrix{0};

			for (int r = 0; r < Rows; r++)
			{
				for (int c = 0; c < Columns; c++)
				{
					matrix[r][c] = a[r][c] + b[r][c];
				}
			}

			return matrix;
		}

		Matrix<Rows, Columns> operator-(const Matrix<Rows, Columns>& b) const
		{
			const auto& a = *this;
			Matrix<Rows, Columns> matrix{0};

			for (int r = 0; r < Rows; r++)
			{
				for (int c = 0; c < Columns; c++)
				{
					matrix[r][c] = a[r][c] - b[r][c];
				}
			}

			return matrix;
		}


		//I cant get the templated multiply to work with vectors
		Vector3 operator*(const Vector3& vec) const;
		Vector4 operator*(const Vector4& vec) const;

		template<unsigned other_rows, unsigned other_columns,
			typename = std::enable_if_t<columns == other_rows>>
			Matrix<rows, other_columns> operator*(const Matrix<other_rows, other_columns>& b) const
		{
			using ReturnMatrix = Matrix<rows, other_columns>;

			const auto& a = *this;

			//TODO: Make this work for non square matrices

			ReturnMatrix matrix{0};
			int c_amount = 0;
			int r_amount = 0;
			for (int c = 0; c < ReturnMatrix::Columns; c++, c_amount++)
			{
				for (int r = 0; r < ReturnMatrix::Rows; r++, r_amount++)
				{
					for (int i = 0; i < Columns /*or other_rows*/; i++)
					{
						const float a_val = a[i][c_amount%Columns];
						const float b_val = b[r_amount%other_rows][i];
						matrix[r][c] += a_val * b_val;
					}
				}
			}

			return matrix;
		}

		///We only accept our own size because we can't change our size like we can when we return a new matrix. 
		///That is also why our own size needs to be square, because multiplying with another size would require a dimension change
		Matrix<Rows, Columns> operator*=(const Matrix<Rows, Columns>& b)
		{
			//TODO: Create a std::enable_if_t in this method
			static_assert(IsSquare(), "The current matrix is not square, Rows and Columns are not equal.");


			auto& a = *this;

			auto matrix = a * b;

			a.m = matrix.m;

			return *this;
		}

		///multiply each element with the scalar
		Matrix<Rows, Columns> operator*=(float b)
		{
			for (int r = 0; r < Rows; r++)
			{
				for (int c = 0; c < Columns; c++)
				{
					at(r, c) *= b;
				}
			}

			return *this;
		}

		//TODO: Write all the += -= operators and stuff

		//Requires the matrix to be square (Rows==Columns)
		template<typename = std::enable_if_t<(IsSquare() && Rows > 2)>>
					Matrix<Rows - 1, Columns - 1> GetMinor(unsigned row, unsigned column) const
					{
						Matrix<Rows - 1, Columns - 1> matrix{0};

						int c_total = 0;

						for (int c = 0; c < Columns; c++)
						{
							int r_total = 0;

							if (column == c)
								continue;

							for (int r = 0; r < Rows; r++)
							{
								if (row == r)
									continue;

								matrix.at(r_total, c_total) = at(r, c);
								r_total++;
							}
							c_total++;
						}

						return matrix;
					}

					//TODO: This will create a lot of temporairy objects, possible optimization spot
					//TODO: Figure out if I want to write an edge case for Matrix<0>
					float Determinant() const;

					//TODO: Add a static_assert to make sure the matrix is square
					///Make this matrix the matrix of its own minors
					void MatrixOfMinors()
					{
						Matrix<Rows, Columns> matrix;

						for (int r = 0; r < Rows; r++)
						{
							for (int c = 0; c < Columns; c++)
							{
								auto minor = GetMinor(r, c);
								matrix[r][c] = minor.Determinant();
							}
						}

						m = matrix.m;
					}

					///Returns true if the Determinant!=0 and if the Rows==Columns
					bool Invert()
					{
						float det = Determinant();
						if (Math::fequals(det, 0.0f) || !IsSquare())
							return false;

						Transpose();

						MatrixOfMinors();

						for (int r = 0; r < Rows; r++)
						{
							for (int c = 0; c < Columns; c++)
							{
								if ((r + c) % 2 == 1)
									at(r, c) *= -1;
							}
						}

						(*this) *= 1.0 / det;

						return true;
					}

#ifdef MATH_ENABLE_OPTIONAL_ENABLE_IF
					template<typename = std::enable_if_t<(IsSquare())>>
#endif
					///Changes itself to a transposed version of itself.
					void Transpose()
					{
						static_assert(IsSquare(),
							"To be able to transpose this matrix, it needs to be rectangular. "
							"Alternitavely use the 'Transposed' method to get the matrix by value.");

						for (int r = 0; r < Rows; r++)
						{
							for (int c = r; c < Columns; c++)
							{
								float a = at(r, c);
								float b = at(c, r);

								at(r, c) = b;
								at(c, r) = a;
							}
						}
					}

					///Returns the transposed version of itself
					Matrix<Columns, Rows> Transposed() const
					{
						Matrix<Columns, Rows> matrix{0};
						for (int r = 0; r < Rows; r++)
						{
							for (int c = 0; c < Columns; c++)
							{
								matrix.at(c, r) = at(r, c);
							}
						}

						return matrix;
					}

					///=================================================
					///Some methods which require the matrix to be 4x4
					///=================================================

					Vector3 GetTranslation() const;
					void SetTranslation(const Vector3& vec);

					Vector3 GetXAxis() const;
					Vector3 GetYAxis() const;
					Vector3 GetZAxis() const;

					void SetXAxis(const Vector3& x_axis);
					void SetYAxis(const Vector3& y_axis);
					void SetZAxis(const Vector3& z_axis);

					/// Sets the orientation of the matrix to the orthogonal basis vector
					/// It perfoms no checks on the orthogonality!
					///
					/// @param x X orthogonal basis vector
					/// @param y Y orthogonal basis vector
					/// @param z Z orthogonal basis vector
					void SetOrientation(const Vector3& x,
						const Vector3& y,
						const Vector3& z);

					/// Set orientation using Euler angles. Currently working!
					void SetEulerAxis(float yaw, float pitch, float roll);

					/// Transfrom just the direction
					Vector3 TransformDirectionVector(const Vector3& direction) const;

					/// Creates a transation matrix
					///
					/// @return Translation matrix
					static Matrix<4> CreateTranslation(float x, float y, float z);

					static Matrix<4> CreateScale(Vector3 scale);

					/// Creates a rotation matrix around an arbitrary axis
					static Matrix<4> CreateRotate(float angle, const Vector3& axis);

					/// Angle in radians
					static Matrix<rows, columns> CreateRotateX(float angle);

					/// Angle in radians
					static Matrix<rows, columns> CreateRotateY(float angle);

					/// Angle in radians
					static Matrix<rows, columns> CreateRotateZ(float angle);

					/// Creates an orthographic projection matrix
					static Matrix<4> CreateOrtho(float left, float right, float bottom, float top, float nearZ, float farZ);

					/// Creates a frustum projection matrix
					static Matrix<4> CreateFrustum(float left, float right, float bottom, float top, float nearZ, float farZ);

					/// Creates a perspective projection matrix from camera settings
					static Matrix<4> CreatePerspective(float fovy, float aspect, float nearZ, float farZ);

					/// Creates a look at matrix, usualy a view matrix  
					static Matrix<4> CreateLookAt(const Vector3& eye, const Vector3& center, const Vector3& up);

					static Matrix<Rows, Columns> CreateIdentity()
					{
						return Matrix<Rows, Columns>::Identity;
					}

					///Will return true if the sizes are the same and if every element is the same in each matrix, 
					///uses Math::fequals to account for floating point inaccuracies
					template<unsigned other_rows, unsigned other_columns>
					bool operator==(const Matrix<other_rows, other_columns>& rhs)
					{
						if (rows != other_rows || columns != other_columns)
							return false;

						for (int r = 0; r < Rows; r++)
						{
							for (int c = 0; c < Columns; c++)
							{
								if (!Math::fequals(at(r, c), rhs.at(r, c)))
									return false;
							}
						}

						return true;
					}

					bool operator!=(const Matrix& rhs)
					{
						return !(*this == rhs);
					}

					static const Matrix Identity;
	};

	inline Vector3 Vector_t<3>::operator+(const Vector3& b) const
	{
		return {
			x + b.x,
			y + b.y,
			z + b.z
		};
	}

	inline Vector3& Vector_t<3>::operator+=(const Vector3& b)
	{
		x += b.x;
		y += b.y;
		z += b.z;

		return *this;
	}

	inline Vector3 Vector_t<3>::operator-(const Vector3& b) const
	{
		return {
			x - b.x,
			y - b.y,
			z - b.z
		};
	}

	inline Vector3& Vector_t<3>::operator-=(const Vector3& b)
	{
		x -= b.x;
		y -= b.y;
		z -= b.z;

		return *this;
	}

	inline Vector3 Vector_t<3>::operator*(const Vector3& b) const
	{
		const auto& a = *this;

		return {
			a.x * b.x,
			a.y * b.y,
			a.z * b.z
		};
	}

	inline Vector3& Vector_t<3>::operator*=(const Vector3& b)
	{
		x *= b.x;
		y *= b.y;
		z *= b.z;

		return *this;
	}

	inline Vector3 Vector_t<3>::operator*(float scalar) const
	{
		const auto& a = *this;

		return {
			a.x * scalar,
			a.y * scalar,
			a.z * scalar
		};
	}

	inline Vector3& Vector_t<3>::operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return *this;
	}

	inline Vector3 Vector_t<3>::operator/(const Vector3& b) const
	{
		const auto& a = *this;

		return {
			a.x / b.x,
			a.y / b.y,
			a.z / b.z
		};
	}

	inline Vector3& Vector_t<3>::operator/=(const Vector3& b)
	{
		x /= b.x;
		y /= b.y;
		z /= b.z;

		return *this;
	}

	inline Vector3 Vector_t<3>::operator/(float scalar) const
	{
		const auto& a = *this;

		return {
			a.x / scalar,
			a.y / scalar,
			a.z / scalar
		};
	}

	inline Vector3& Vector_t<3>::operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;

		return *this;
	}

	inline float Vector_t<3>::SquareMagnitude() const
	{
		return x * x + y * y + z * z;
	}

	inline float Vector_t<3>::Magnitude2() const
	{
		return x * x + y * y + z * z;
	}

	inline float Vector_t<3>::Magnitude() const
	{
		float mag2 = SquareMagnitude();
		return sqrtf(mag2);
	}

	inline void Vector_t<3>::Normalize()
	{
		float mag = Magnitude();
		(*this) /= mag;
	}

	inline Vector3 Vector_t<3>::Normalized() const
	{
		float mag = Magnitude();
		return *this / mag;
	}

	inline void Vector_t<3>::Clear()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	inline Vector3 Vector_t<3>::Cross(const Vector3& b) const
	{
		//TODO: Figure out why this works (or doesn't)

		return {
			y * b.z - b.y * z,
			z * b.x - b.z * x,
			x * b.y - b.x * y
		};
	}

	inline float Vector_t<3>::Dot(const Vector3& b) const
	{
		return x * b.x + y * b.y + z * b.z;
	}

	inline Vector3 Vector_t<3>::Slerp(float fact, const Vector3& end) const
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
		float theta = acosf(dot) * fact;
		Vector3 RelativeVec = end - start * dot;
		RelativeVec.Normalize(); // Orthonormal basis
								 // The final result.
		return (start * cosf(theta)) + (RelativeVec * sinf(theta));
	}

	template <unsigned rows, unsigned columns>
	float Matrix<rows, columns>::Determinant() const
	{
		static_assert(Rows == Columns,
			"The Determinant cannot be computed when the matrix is not square (The rows and columns must be the same height!)");

		//Slice the current matrix and call determinant on that:
		using MiniMatrix = Matrix<Rows - 1, Columns - 1>;
		std::array<MiniMatrix, Columns> matrices;

		for (int i = 0; i < matrices.size(); i++)
		{
			matrices[i] = GetMinor(0, i);
		}

		//get the determinant from the smaller matrices:
		float total = 0;
		for (int i = 0; i < matrices.size(); i++)
		{
			if (i % 2 == 0)
			{
				total += at(0, i) * matrices[i].Determinant();
			}
			else
			{
				total -= at(0, i) * matrices[i].Determinant();
			}
		}

		return total;
	}

	template<>
	inline float Matrix<1, 1>::Determinant() const
	{
		return at(0, 0);
	}

	template<>
	inline float Matrix<2, 2>::Determinant() const
	{
		return at(0, 0) * at(1, 1) - at(1, 0) * at(0, 1);
	}

} // end namespace Math

//Yes I know this is a very hacky solution but I cannot find a cleaner way to do this
//More info in Vector3.h
//#define VECTOR_DONT_INCUDE_MATRIX_FILE
//#include "Vector2.h"
//#include "Vector3.h"
//#include "Vector4.h"
//#undef VECTOR_DONT_INCUDE_MATRIX_FILE

namespace Math{
	inline Vector3 Matrix<4, 4>::operator*(const Vector3& vec) const
	{
		const auto& m = *this;
		Vector3 ret{ vec.x * m[0][0] +
			vec.y * m[1][0] +
			vec.z * m[2][0] + m[3][0],

			vec.x * m[0][1] +
			vec.y * m[1][1] +
			vec.z * m[2][1] + m[3][1],

			vec.x * m[0][2] +
			vec.y * m[1][2] +
			vec.z * m[2][2] + m[3][2] };
		return ret;
	}

	inline Vector4 Matrix<4, 4>::operator*(const Vector4& vec) const
	{
		const auto* f = this->data();
		return Vector4(f[0] * vec.x + f[4] * vec.y + f[8] * vec.z + f[12] * vec.w,
			f[1] * vec.x + f[5] * vec.y + f[9] * vec.z + f[13] * vec.w,
			f[2] * vec.x + f[6] * vec.y + f[10] * vec.z + f[14] * vec.w,
			f[3] * vec.x + f[7] * vec.y + f[11] * vec.z + f[15] * vec.w);
	}
/// Transform the given vector by this matrix.
///
/// @param vec vector that is asssumed to be homogenuos with w=1
/// @return Resulting vector is asssumed to be homogenuos with w=1
//TODO: Write this
//template<>
//Matrix<3, 1> Matrix<4, 4>::operator*(const Matrix<3, 1>& vec) const
//{
//	return {};
//}

	template <unsigned rows, unsigned columns>
	inline Vector3 Matrix<rows, columns>::GetTranslation() const
	{
		static_assert(rows >= 3 && columns >= 4, "Matrix::GetTranslation requires the matrix to be at least 3x4");

		return {
			at(3, 0),
			at(3, 1),
			at(3, 2)
		};
	}

	template <unsigned rows, unsigned columns>
	inline void Matrix<rows, columns>::SetTranslation(const Vector3& vec)
	{
		static_assert(rows >= 3 && columns >= 4, "Matrix::SetTranslation requires the matrix to be at least 3x4");

		at(3, 0) = vec.x;
		at(3, 1) = vec.y;
		at(3, 2) = vec.z;
		//TODO: Should I set W to 1 as well?
	}

	template <unsigned rows, unsigned columns>
	inline Vector3 Matrix<rows, columns>::GetXAxis() const
	{
		static_assert(rows >= 3 && columns >= 3, "Matrix::GetXAxis requires the matrix to be at least 3x3");

		return{
			at(0, 0),
			at(0, 1),
			at(0, 2)
		};
	}

	template <unsigned rows, unsigned columns>
	inline Vector3 Matrix<rows, columns>::GetYAxis() const
	{
		static_assert(rows >= 3 && columns >= 3, "Matrix::GetYAxis requires the matrix to be at least 3x3");

		return{
			at(1, 0),
			at(1, 1),
			at(1, 2)
		};
	}

	template <unsigned rows, unsigned columns>
	inline Vector3 Matrix<rows, columns>::GetZAxis() const
	{
		static_assert(rows >= 3 && columns >= 3, "Matrix::GetZAxis requires the matrix to be at least 3x3");

		return{
			at(2, 0),
			at(2, 1),
			at(2, 2)
		};
	}

	template <unsigned rows, unsigned columns>
	void Matrix<rows, columns>::SetXAxis(const Vector3& x_axis)
	{
		static_assert(rows >= 3 && columns >= 3, "Matrix::SetXAxis requires the matrix to be at least 3x3");

		at(0, 0) = x_axis.x;
		at(0, 1) = x_axis.y;
		at(0, 2) = x_axis.z;
	}

	template <unsigned rows, unsigned columns>
	void Matrix<rows, columns>::SetYAxis(const Vector3& y_axis)
	{
		static_assert(rows >= 3 && columns >= 3, "Matrix::SetYAxis requires the matrix to be at least 3x3");

		at(1, 0) = y_axis.x;
		at(1, 1) = y_axis.y;
		at(1, 2) = y_axis.z;
	}

	template <unsigned rows, unsigned columns>
	void Matrix<rows, columns>::SetZAxis(const Vector3& z_axis)
	{
		static_assert(rows >= 3 && columns >= 3, "Matrix::SetZAxis requires the matrix to be at least 3x3");

		at(2, 0) = z_axis.x;
		at(2, 1) = z_axis.y;
		at(2, 2) = z_axis.z;
	}

	template <unsigned rows, unsigned columns>
	void Matrix<rows, columns>::SetOrientation(const Vector3& x, const Vector3& y, const Vector3& z)
	{
		static_assert(rows >= 3 && columns >= 3, "Matrix::SetOrientation requires the matrix to be at least 3x3");

		//TODO: are these the actual axis'?
		SetXAxis(x);
		SetYAxis(y);
		SetZAxis(z);
	}

	template <unsigned rows, unsigned columns>
	void Matrix<rows, columns>::SetEulerAxis(float yaw, float pitch, float roll)
	{
		static_assert(rows >= 3 && columns >= 3, "Matrix::SetEulerAxis requires the matrix to be at least 3x3");

		////TODO: Uptimize this by only making this one calculation
		//auto z_matrix = Matrix<4>::CreateRotateZ(roll);
		//auto y_matrix = Matrix<4>::CreateRotateY(pitch);
		//auto x_matrix = Matrix<4>::CreateRotateX(yaw);

		//auto rotation_matrix = x_matrix * y_matrix * z_matrix;
		////TODO: Make the CreateRotateX/Y/Z methods have an overload for returning a 3x3 matrix
		////TODO: Make a method for setting a matrix (maybe smaller) to our own matrix
		//for (int r = 0; r < 3; ++r)
		//{
		//	for (int c = 0; c < 3; ++c)
		//	{
		//		m[r][c] = rotation_matrix[r][c];
		//	}
		//}

		//Transpose();

		float tmp_ch = cosf(yaw);
		float tmp_sh = sinf(yaw);
		float tmp_cp = cosf(pitch);
		float tmp_sp = sinf(pitch);
		float tmp_cb = cosf(roll);
		float tmp_sb = sinf(roll);

		*this = Identity;
		m[0][0] = tmp_ch * tmp_cb + tmp_sh * tmp_sp * tmp_sb;
		m[0][1] = tmp_sb * tmp_cp;
		m[0][2] = -tmp_sh * tmp_cb + tmp_ch * tmp_sp * tmp_sb;
		m[1][0] = -tmp_ch * tmp_sb + tmp_sh * tmp_sp * tmp_cb;
		m[1][1] = tmp_cb * tmp_cp;
		m[1][2] = tmp_sb * tmp_sh + tmp_ch * tmp_sp * tmp_cb;
		m[2][0] = tmp_sh * tmp_cp;
		m[2][1] = -tmp_sp;
		m[2][2] = tmp_ch * tmp_cp;
	}

	template <>
	inline Vector3 Matrix<4, 4>::TransformDirectionVector(const Vector3& direction) const
	{
		//Matrix m = Transposed();
		Vector4 direction4 = { direction.x, direction.y, direction.z, 0 };

		auto transformed_direction = *this * direction4;
		
		return {
			transformed_direction.f[0],
			transformed_direction.f[1],
			transformed_direction.f[2]
		};
	}

	template<>
	inline Matrix<4> Matrix<4, 4>::CreateTranslation(float x, float y, float z)
	{
		auto matrix = Matrix<4>::Identity;

		matrix[3][0] = x;
		matrix[3][1] = y;
		matrix[3][2] = z;

		return matrix;
	}

	template <>
	inline Matrix<4> Matrix<4, 4>::CreateScale(Vector3 scale)
	{
		auto matrix = Matrix<4>::Identity;

		matrix[0][0] = scale.x;
		matrix[1][1] = scale.y;
		matrix[2][2] = scale.z;

		return matrix;
	}

	template <>
	inline Matrix<4> Matrix<4, 4>::CreateRotate(float angle, const Vector3& axis)
	{
		auto m = Matrix<4>::Identity;

		const Vector3& u = axis.Normalized();
		float c = cosf(angle);
		float s = sinf(angle);

		//const Vector3& u = axis.Normalized();
		float cos_a = cosf(angle);
		float sin_a = sinf(angle);

		/*m[0][0] = cos_a + u.x*u.x*(1 - cos_a);				m[0][1] = u.x*u.y*(1 - cos_a) - u.z*sin_a;		m[0][2] = u.x*u.y*(1 - cos_a) + u.y*sin_a;
		m[1][0] = u.y*u.x*(1 - cos_a) - u.z*sin_a;			m[1][1] = cos_a + u.y*u.y*(1 - cos_a);			m[1][2] = u.y*u.z*(1 - cos_a) + u.x*sin_a;
		m[2][0] = u.z*u.x*(1 - cos_a) - u.y*sin_a;			m[2][1] = u.z*u.y*(1 - cos_a) - u.x*sin_a;		m[2][2] = cos_a + u.z*u.z*(1 - cos_a);*/

		/*m[0][0] = cos_a + u.x*u.x*(1 - cos_a);				m[0][1] = u.x*u.y*(1 - cos_a) - u.z*sin_a;		m[0][2] = (1-c) * axis.x * axis.z + axis.y * s;
		m[1][0] = u.y*u.x*(1 - cos_a) - u.z*sin_a;			m[1][1] = cos_a + u.y*u.y*(1 - cos_a);			m[1][2] = u.y*u.z*(1 - cos_a) + u.x*sin_a;
		m[2][0] = u.z*u.x*(1 - cos_a) - u.y*sin_a;			m[2][1] = u.z*u.y*(1 - cos_a) - u.x*sin_a;		m[2][2] = cos_a + u.z*u.z*(1 - cos_a);*/

		

		m[0][0] = c + axis.x*axis.x * (1 - c);
		m[0][1] = axis.y * axis.x * (1 - c) + axis.z * s;
		m[0][2] = axis.z * axis.x * (1 - c) - axis.y * s;

		m[1][0] = axis.x * axis.y * (1 - c) - axis.z * s;
		m[1][1] = c + axis.y * axis.y * (1 - c);
		m[1][2] = axis.z * axis.y * (1 - c) + axis.x * s;

		m[2][0] = axis.x * axis.z * (1 - c) + axis.y * s;
		m[2][1] = axis.y * axis.z * (1 - c) - axis.x * s;
		m[2][2] = c + axis.z * axis.z *(1 - c);

		/*m[0][0] = c + axis.x*axis.x * (1 - c);
		m[0][1] = axis.y * axis.x * (1 - c) + axis.z * s;
		m[0][2] = axis.z * axis.x * (1 - c) - axis.y * s;

		m[1][0] = axis.x * axis.y * (1 - c) - axis.z * s;
		m[1][1] = c + axis.y * axis.y * (1 - c);
		m[1][2] = axis.z * axis.y * (1 - c) + axis.x * s;

		m[2][0] = axis.x * axis.z * (1 - c) + axis.y * s;
		m[2][1] = axis.y * axis.z * (1 - c) - axis.x * s;
		m[2][2] = c + axis.z * axis.z *(1 - c);*/

		return m;
	}

	template<unsigned rows, unsigned columns>
	inline Matrix<rows, columns> Matrix<rows, columns>::CreateRotateX(float angle)
	{
		static_assert(IsSquare() && (rows == 3 || rows == 4), "Matrix::CreateRotateX requires the matrix to be 3x3 or 4x4 with a identity matrix border");

		auto matrix = Matrix<rows, columns>::Identity;

		float cos_x = cosf(angle);
		float sin_x = sinf(angle);

		matrix[1][1] = cos_x;	matrix[1][2] = -sin_x;
		matrix[2][1] = sin_x;	matrix[2][2] = cos_x;

		return matrix;
	}

	template<unsigned rows, unsigned columns>
	inline Matrix<rows, columns> Matrix<rows, columns>::CreateRotateY(float angle)
	{
		auto matrix = Matrix<rows, columns>::Identity;

		float cos_y = cosf(angle);
		float sin_y = sinf(angle);

		matrix[0][0] = cos_y;				matrix[0][2] = sin_y;

		matrix[2][0] = -sin_y;				matrix[2][2] = cos_y;

		return matrix;
	}

	template<unsigned rows, unsigned columns>
	inline Matrix<rows, columns> Matrix<rows, columns>::CreateRotateZ(float angle)
	{
		auto matrix = Matrix<rows, columns>::Identity;

		float cos_z = cosf(angle);
		float sin_z = sinf(angle);

		matrix[0][0] = cos_z;	matrix[0][1] = -sin_z;
		matrix[1][0] = sin_z;	matrix[1][1] = cos_z;

		return matrix;
	}

	template <>
	inline Matrix<4> Matrix<4, 4>::CreateOrtho(float left, float right, float bottom, float top, float nearZ, float farZ)
	{
		auto matrix = Matrix<4>::Identity;

		matrix[0][0] = 2.f / (right - left);
		matrix[1][1] = 2.f / (top - bottom);
		matrix[2][2] = -2.f / (farZ - nearZ);

		matrix[3][0] = -(right + left) / (right - left);
		matrix[3][1] = -(top + bottom) / (top - bottom);
		matrix[3][2] = -(farZ + nearZ) / (farZ - nearZ);

		return matrix;
	}

	template <>
	inline Matrix<4> Matrix<4, 4>::CreateFrustum(float left, float right, float bottom, float top, float nearZ, float farZ)
	{
		auto m = Matrix<4>::Identity;

		float zDelta = (farZ - nearZ);
		float dir = (right - left);
		float height = (top - bottom);
		float nearZ2 = (2 * nearZ);

		m[0][0] = 2.0f*nearZ / dir;
		m[0][2] = (right + left) / dir;
		m[1][1] = nearZ2 / height;
		m[1][1] = nearZ2 / height;
		m[1][2] = (top + bottom) / height;
		m[2][2] = -(farZ + nearZ) / zDelta;
		m[2][3] = -nearZ2*farZ / zDelta;
		m[3][2] = -1.f;
		m[3][3] = 0.f;

		m.Transpose();

		return m;
	}

	template <>
	inline Matrix<4> Matrix<4, 4>::CreatePerspective(float fovy, float aspect, float nearZ, float farZ)
	{
		//
		// General form of the Projection Matrix
		//
		// uh = Cot( fov/2 ) == 1/Tan(fov/2)
		// uw / uh = 1/aspect
		// 
		//   uw         0       0       0
		//    0        uh       0       0
		//    0         0      f/(f-n)  1
		//    0         0    -fn/(f-n)  0
		//
		// Make result to be identity first

		// check for bad parameters to avoid divide by zero:
		// if found, assert and return an identity matrix.
		if (fovy <= 0 || aspect == 0)
		{
			assert(fovy > 0 && aspect != 0);
			return {};
		}

		Matrix<4> m = Matrix<4>::Identity;

		float frustumDepth = farZ - nearZ;
		float oneOverDepth = 1 / frustumDepth;
		bool leftHanded = true;

		m[1][1] = 1 / tan(0.5f * fovy);
		m[0][0] = (leftHanded ? 1 : -1) * m[1][1] / aspect;
		m[2][2] = (farZ + nearZ) / (nearZ - farZ);
		m[3][2] = (2.0f * farZ * nearZ) / (nearZ - farZ);
		m[2][3] = -1;
		m[3][3] = 0;

		return m;
	}

	template <>
	inline Matrix<4> Matrix<4, 4>::CreateLookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
	{
		Vector3 zaxis = eye - center;		// The "forward" vector.
		zaxis.Normalize();
		Vector3 xaxis = up.Cross(zaxis);	// The "right" vector.
		xaxis.Normalize();
		Vector3 yaxis = zaxis.Cross(xaxis);	// The "up" vector.

		Vector3 translation{ -xaxis.Dot(eye), -yaxis.Dot(eye), -zaxis.Dot(eye) };

		Matrix<4> matrix = Matrix<4>::Identity;
		matrix.SetOrientation(xaxis, yaxis, zaxis);
		matrix.Transpose();
		matrix.SetTranslation(translation);

		return matrix;
	}


	template<unsigned int width, unsigned int height>
	constexpr Matrix<width, height> make_identity_matrix()
	{
		if (width != height)
			return Matrix<width, height>(0);

		Matrix<width, height> matrix{0};
		for (int i = 0; i < height; i++)
		{
			matrix[i][i] = 1.f;
		}
		return matrix;
	}

	template<unsigned int width, unsigned int height>
	const Matrix<width, height> Matrix<width, height>::Identity = make_identity_matrix<width, height>();

	template<unsigned rows, unsigned cols = rows>
	constexpr Matrix<rows, cols> MakeMatrix(const float floats[rows*cols])
	{
		Matrix<rows, cols> m;
		for (int r = 0; r < rows; ++r)
		{
			for (int c = 0; c < cols; ++c)
			{
				m[r][c] = floats[r*cols + c]; 
			}
		}

		return m;
	}



} //End namespace Math
