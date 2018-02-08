#include "Matrix.h"
#include "Catch2/catch.hpp"

#include <iostream>
#include <string>

#include "ToString.h"
#include "Vectors.h"
#include "MatrixDebugging.h"
#include <random>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace Math;

//TODO: Write actual tests
TEST_CASE("Matrix")
{
	/*Matrix<3> matrix1({
		{3, 2, 4},
		{1, 9, 7},
		{6, 3, 2}
	});
	cout << "matrix1:\n" << Math::ToString(matrix1) << endl;

	Matrix<3> matrix2{
		{ 1, 2, 7 },
		{ 3, 4, 2 },
		{ 2, 9, 4 }
	};
	cout << "matrix2:\n" << Math::ToString(matrix2) << endl;


	Matrix<3> addition_matrix = matrix1 + matrix2;
	cout << Math::ToString(addition_matrix) << endl;
	Matrix<3> subtracktion_matrix = matrix1 - matrix2;
	cout << Math::ToString(subtracktion_matrix) << endl;

	Matrix<3, 2> hori_matrix {
		{4, 3},
		{1, 2},
		{2, 3}
	};

	Matrix<2, 3> vert_matrix{
		{5, 2, 2},
		{1, 3, 6}
	};

	cout << "hori_matrix\n" << Math::ToString(hori_matrix) << endl;
	cout << "vert_matrix\n" << Math::ToString(vert_matrix) << endl;

	auto multiplication_matrix = hori_matrix * vert_matrix;
	cout << Math::ToString(multiplication_matrix) << endl;*/
}

TEST_CASE("Matrix multiplication")
{
	Matrix<4, 4> t{
		{2, 1, 0, 0},
		{-1, 2, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 1}
	};
	glm::mat4 glm_t( 2,1,0,0,
	- 1,2,0,0,
	0,0,0,0,
	0,0,0,1 );
	glm::vec4 glm_pos{ 2,1,2,1 };
	auto glm_tp = glm_t*glm_pos;
	Vector4 pos{ 2, 1, 2, 1 };

	auto tp = t * pos;
	REQUIRE_COMPARE_VECTOR(glm_tp, tp );

	/*Matrix<2> m1 {
		{1, 2},
		{3, 4}
	};

	Matrix<2> m2{
		{ 5, 6 },
		{ 7, 8 }
	};

	Matrix<2> m1x2 = m1 * m2;
	PrintMyMatrixC(m1x2, "m1x2");
	CHECK((m1x2 == Matrix<2>{ {19, 22}, { 43, 50 }}));

	Matrix<2, 3> m2by3{
		{1, 2, 3},
		{3, 4, 6}
	};
	Matrix<2, 3> longmatrix = m1 * m2by3;
	PrintMyMatrixC(longmatrix, "longmatrix");
	auto longmatrix_actual_result = Matrix<2, 3>{ { 7, 10, 15 },{ 15, 22, 33 } };
	CHECK((longmatrix == longmatrix_actual_result));
	Matrix<3> m3{
		{ 1, 2, 3 },
		{ 3, 4, 3 },
		{3, 3, 3}
	};

	Matrix<3> m4{
		{ 5, 6 , 3},
		{ 7, 8,3 },
		{3, 3, 3}
	};

	auto m3x4 = m3 * m4;
	CHECK((m3x4 == Matrix<3>{ {28, 31, 18}, { 52, 59, 30 }, {45, 51, 27}}));

	float f = 10.f;
	f *= 10;
	REQUIRE(f == Approx(100.f));

	m3 *= m4;
	CHECK((m3 == m3x4));*/
}

TEST_CASE("Matrix Determinant")
{
	Matrix<4, 4> m1{
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	};
	glm::mat4 glm_det = glm::make_mat4(&m1.m[0][0]);
	REQUIRE(m1.Determinant() == Approx(0.f));
	REQUIRE(glm::determinant(glm_det) == Approx(0.f));
	REQUIRE(glm::determinant(glm_det) == Approx(m1.Determinant()) );

	Matrix<4, 4> m2{
		{ 4, 1, 3, 2 },
		{ 1, 3, 7, 3 },
		{ 1, 1, 4, 2 },
		{ 3, 14, 5, 16 }
	};
	glm::mat4 glm_det2 = glm::make_mat4(&m2.m[0][0]);
	REQUIRE(m2.Determinant() == Approx(288.f));
	REQUIRE(glm::determinant(glm_det2) == Approx(288.f));
	REQUIRE(glm::determinant(glm_det2) == Approx(m2.Determinant()));
}

TEST_CASE("Matrix Transpose / Transposed")
{
	Matrix<3> m33{ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	auto m33_transposed = m33.Transposed();
	m33.Transpose();

	auto m33_result = Matrix<3>{ { 1, 4, 7 },{ 2, 5, 8 },{ 3, 6, 9 } };
	REQUIRE((m33_transposed == m33_result));
	REQUIRE((m33 == m33_result));
	REQUIRE((m33 == m33_transposed));


	Matrix<2, 3> m23{ 
		{ 1, 2, 3 }, 
		{ 4, 5, 6 }
	};
	auto m23_transposed = m23.Transposed();
	
	REQUIRE((m23_transposed == Matrix<3, 2>{ {1, 4}, { 2, 5 }, { 3, 6 }}));
}

TEST_CASE("Matrix invert")
{
	Matrix<3> m33_basic{ { 1, 2, 3 },{ 4, 5, 6 },{ 7, 8, 9 } };
	REQUIRE_FALSE(m33_basic.Invert());

	Matrix<4> m44_hannes{
		{ 3, 5, 8, 6 },
		{ 4, 9, 2, 7 },
		{ 5, 1, 2, 6 },
		{ 7, 5, 2, 9 }
	};
	Matrix<4> m44_hannes2{
		{ 3, 5, 8, 6 },
		{ 4, 9, 2, 7 },
		{ 5, 1, 2, 6 },
		{ 7, 5, 2, 9 }
	};

	m44_hannes.Invert();
	m44_hannes2 *= m44_hannes;
	PrintMyMatrixC(m44_hannes2, "Hannes own nums");
	auto m44_identity = Matrix<4>::Identity;
	REQUIRE_COMPARE_MATRIX(m44_hannes2, m44_identity);

	Matrix<3> m33_advanced{ { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 2 } };
	REQUIRE(m33_advanced.Invert());
	Matrix<3> m33_advanced_result{ 
		{ 1, 0, 0 }, 
		{ 0, 1, 0 }, 
		{ 0, 0, 0.5}
	};

	Matrix<3> m33_advanced2{ { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 2 } };
	auto mdkwa = m33_advanced2 * m33_advanced;
	PrintMyMatrixC(mdkwa, "Hannes test!");

	REQUIRE((m33_advanced == m33_advanced_result));

	Matrix<4> m44_2{
		{2, 3, 1, 1},
		{1, 5, 1, 2},
		{1, 3, 2, 1},
		{2, 3, 2, 1}
	};

	m44_2.Invert();

	Matrix<4> m44_2_result{
		{0, 0, -1, 1},
		{3, -1, 3, -4},
		{-1, 0, 0, 1 },
		{-7, 3, -7, 9}
	};

	REQUIRE((m44_2 == m44_2_result));
}

static float* generate_random_matrix(mt19937& rng_engine, uniform_real_distribution<float>& dist_distr)
{
	float* f = new float[16];
	for (int i = 0; i < 16; ++i)
	{
		f[i] = dist_distr(rng_engine);
	}
	return f;
}

TEST_CASE("Matrix inversion x100")
{
	const unsigned int seed = 123;
	std::mt19937 rng_engine{ seed };
	std::uniform_real_distribution<float> dist_distr{ -150, 150 };

	const int test_amount = 100;
	for (int i = 0; i < test_amount; i++) {


		float* f = generate_random_matrix(rng_engine, dist_distr);
		glm::mat4 glm_inverse = glm::make_mat4(f);
		igad::Matrix44 igad_inverse_mat{ f[0], f[1], f[2], f[3], f[4], f[5],f[6], f[7], f[8], f[9], f[10], f[11], f[12], f[13], f[14], f[15] };
		Matrix44 my_inverse = Math::MakeMatrix<4>(f);

		REQUIRE_COMPARE_MATRIX(glm_inverse, igad_inverse_mat);
		REQUIRE_COMPARE_MATRIX(glm_inverse, my_inverse);
	}
}

TEST_CASE("Matrix equality")
{
	Matrix<1> m1{2 };
	Matrix<1> m2{ 3 };
	Matrix<1> m3{ 2 };

	bool b = (m1 == m2);
	REQUIRE_FALSE(b);
	PrintMyMatrixC(m1);
	PrintMyMatrixC(m2);

	PrintMyMatrixC(m3);
	b = (m1 == m3);
	REQUIRE(b);

	Matrix<2> m4{ {2, 3},{4, 5} };
	Matrix<2> m5{ {6, 7}, {8, 9} };
	Matrix<2> m6{ {2, 3}, {4, 5} };
	PrintMyMatrixC(m4);
	PrintMyMatrixC(m5);
	PrintMyMatrixC(m6);

	b = m1 == m4;
	REQUIRE_FALSE(b);
	b = (m4 == m5);
	REQUIRE_FALSE(b);
	b = (m4 == m6);
	REQUIRE( b);

	Matrix<2, 1> m7{ 
		2,5 
	};

	Vector2 vec{ 2, 5 };
	//b = m7 == vec;
	//REQUIRE(b);

	float fx = vec.x;
	float fy = vec.y;
	REQUIRE(fequals(fx, 2));
	REQUIRE(fequals(fy, 5));
}

TEST_CASE("Matrix EulerAngles comparison")
{
	
}

TEST_CASE("Matrix addition")
{
	//TODO: Write these tests if I have time left
}

TEST_CASE("Matrix subtraction")
{
	//TODO: Write these tests if I have time left
}

//template<int m, int n>
//struct meme
//{
//	float x, y;
//
//	//meme(std::initializer_list<std::initializer_list<float>> meem) {}
//
//	meme(float (&meem)[m][n]) : x(meem[0]), y(meem[1])
//	{
//		cout << m << " " << n << endl;
//	}
//};
//
//TEST_CASE("DWA")
//{
//	meme<3, 3> m({ { {1.f, 2.f, 3.f}, {4.f, 4.f, 4.f}, {1.f, 1.f, 1.f} } });
//	
//}
