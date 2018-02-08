#pragma once
//A namespace with some private implementation details, do not directly use the contents in your code
namespace Math {
	namespace _Impl_ {

#ifdef _DEBUG
#define SET_CACHE val = vec.at(r, c);
#else
#define SET_CACHE
#endif
		//TODO: Should x and y be a type?
		template<typename Vec>
		class matrix_variable_proxy
		{
#ifdef _DEBUG
			float val;
#endif

			Vec& vec;
			int r, c;

			friend class matrix_variable_proxy<Vec>;
		public:
			matrix_variable_proxy(Vec& vec, int x, int y) : vec(vec), r(x), c(y)
			{
				SET_CACHE
			}

			inline matrix_variable_proxy& operator=(float other)
			{
				vec.at(r, c) = other;

				SET_CACHE

				return *this;
			}

			inline matrix_variable_proxy& operator=( const matrix_variable_proxy& other)
			{
				vec.at(r, c) = other.vec.at(other.r, other.c);

				SET_CACHE

				return *this;
			}

			//TODO: Write all the other += etc operators
			inline matrix_variable_proxy& operator+=(float other)
			{
				vec.at(r, c) += other;

				SET_CACHE

				return *this;
			}

			inline matrix_variable_proxy& operator-=(float other)
			{
				vec.at(r, c) -= other;

				SET_CACHE

				return *this;
			}

			inline matrix_variable_proxy& operator*=(float other)
			{
				vec.at(r, c) *= other;

				SET_CACHE

				return *this;
			}

			///NOTE: Does not check for a DividedByZero exception!
			inline matrix_variable_proxy& operator/=(float other)
			{
				vec.at(r, c) /= other;

				SET_CACHE

				return *this;
			}

			inline float operator+(float other) const
			{
				return vec.at(r, c) + other;
			}

			inline float operator-(float other) const
			{
				return vec.at(r, c) - other;
			}

			inline float operator*(float other) const
			{
				return vec.at(r, c) * other;
			}

			inline float operator/(float other) const
			{
				return vec.at(r, c) / other;
			}

			inline float* operator&()
			{
				auto& matrix_float = vec.at(r, c);
				return &matrix_float;
			}

			inline const float* operator&() const
			{
				const auto& matrix_float = vec.at(r, c);
				return &matrix_float;
			}

			// ReSharper disable once CppNonExplicitConversionOperator
			inline operator float() const { return vec.at(r, c); }
		};
	}
}