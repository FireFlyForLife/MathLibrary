#include "Catch2/catch.hpp"
#include "MathFunctions.h"
#include <Matrix44.h>
#include "Matrix.h"
#include <iostream>
#include "ToString.h"
#include <string>
#include "MatrixDebugging.h"
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <random>

using namespace std;
using namespace Math; //my own math



TEST_CASE("Matrix44 TransformDirectionVector comparison")
{
	std::mt19937 rng;
	rng.seed(123123);
	std::uniform_real_distribution<float> dist{ -100, 100 };

	Matrix<4> my_matrix{
		{10, 1, 2, 0},
		{11, -10, 1, 0},
		{-29, 1, 2, 0},
		{0, 0, 0, 1}
	};
	igad::Matrix44 igad_matrix{10, 1, 2, 0, 11, -10, 1, 0, -29, 1, 2, 0, 0, 0, 0, 1};
	
	const int test_amout = 100;
	for (int i = 0; i < test_amout; i++) {
		float x, y, z;
		x = dist(rng);
		y = dist(rng);
		z = dist(rng);

		Vector3 my_vec{ x, y, z };
		igad::Vector3 igad_vec{ x, y, z };

		my_vec = my_matrix.TransformDirectionVector(my_vec);
		igad_vec = igad_matrix.TransformDirectionVector(igad_vec);

		REQUIRE_COMPARE_VECTOR(igad_vec, my_vec);
	}
}

TEST_CASE("igad::Matrix44 comparison")
{
	igad::Matrix44 igad_matrix_test;
	igad_matrix_test.SetTranslation({ 5, 3, 2 });
	igad_matrix_test.SetOrientation({ 1,1,1 }, { 2,2,2 }, { 3,3,3 });

	Math::Matrix44 my_matrix_test;
	my_matrix_test.SetTranslation({ 5,3,2 });
	my_matrix_test.SetOrientation({ 1,1,1 }, { 2,2,2 }, { 3,3,3 });

	REQUIRE_COMPARE_MATRIX(igad_matrix_test, my_matrix_test);

	igad::Matrix44 igad_matrix{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	auto igad_matrix_sqrt = igad_matrix * igad_matrix;
	igad::Matrix44 igad_matrix_result{ 90, 100, 110, 120, 202, 228, 254, 280, 314, 356, 398, 440, 426, 484, 542, 600 };
	REQUIRE_COMPARE_MATRIX(igad_matrix_sqrt, igad_matrix_result);

	Matrix<4> my_matrix{
		{ 1, 2, 3, 4}, 
		{5, 6, 7, 8}, 
		{9, 10, 11, 12}, 
		{13, 14, 15, 16}
	};
	auto my_matrix_sqrt = my_matrix * my_matrix;
	REQUIRE(compare_matrix(igad_matrix_sqrt, my_matrix_sqrt, "igad_matrix_sqrt", "my_matrix_sqrt"));

	glm::mat4 glm_mat_translation{ 1 };
	glm_mat_translation = glm::translate(glm_mat_translation, { 5, 5, 5 });
	igad::Matrix44 igad_mat_translation;
	igad_mat_translation.SetTranslation({ 5, 5, 5 });
	REQUIRE_COMPARE_MATRIX(glm_mat_translation, igad_mat_translation);
	Matrix<4> my_mat_translation = Matrix<4>::Identity;
	my_mat_translation.SetTranslation({ 5,5,5 });
	REQUIRE_COMPARE_MATRIX(glm_mat_translation, my_mat_translation);

	glm::mat4 glm_matrix_euler = glm::yawPitchRoll(0.5f, 1.f, 1.f);

	Matrix<4> my_matrix_euler = Matrix<4>::Identity;
	my_matrix_euler.SetEulerAxis(0.5f, 1.f, 1.f);
	REQUIRE_COMPARE_MATRIX(glm_matrix_euler, my_matrix_euler);

	igad::Matrix44 igad_matrix_around_axis = igad::Matrix44::CreateRotate(2, igad::Vector3{0, 1, 0});
	PrintIgadMatrixC(igad_matrix_around_axis, "PrintIgadMatrixC");
	Matrix<4> my_matrix_around_axis = Matrix<4>::CreateRotate(2, Vector3{ 0, 1, 0 });
	PrintMyMatrixC(my_matrix_around_axis, "my_matrix_around_axis");
	REQUIRE_COMPARE_MATRIX(igad_matrix_around_axis, my_matrix_around_axis);

	igad::Matrix44 igad_matrix_lookat_projection = igad::Matrix44::CreateLookAt(igad::Vector3{ 2, 2, 0 }, igad::Vector3{ -4, 0, 2 }, igad::Vector3{ 0, 1, 0 });
	//PrintIgadMatrixC(igad_matrix_lookat_projection, "igad_matrix_lookat_projection");
	Matrix<4> my_matrix_lookat_projection = Matrix<4>::CreateLookAt(Vector3{ 2, 2, 0 }, Vector3{ -4, 0, 2 }, Vector3{ 0, 1, 0 });
	//PrintMyMatrixC(my_matrix_lookat_projection, "my_matrix_lookat_projection");
	REQUIRE_COMPARE_MATRIX(igad_matrix_lookat_projection, my_matrix_lookat_projection);

	igad::Matrix44 igad_matrix_otrhographic_projection = igad::Matrix44::CreateOrtho(-40, 40, -50, 50, 10, 100);
	//PrintIgadMatrixC(igad_matrix_otrhographic_projection, "igad_matrix_otrhographic_projection");
	Matrix<4> my_matrix_projection_projection = Matrix<4>::CreateOrtho(-40, 40, -50, 50, 10, 100);
	//PrintMyMatrixC(my_matrix_projection_projection, "my_matrix_projection_projection");
	REQUIRE_COMPARE_MATRIX(igad_matrix_otrhographic_projection, my_matrix_projection_projection);

	igad::Matrix44 igad_matrix_frustrum = igad::Matrix44::CreateFrustum(-40, 40, -50, 50, 10, 100);
	//PrintIgadMatrixC(igad_matrix_frustrum, "igad_matrix_frustrum");
	Matrix<4> my_matrix_frustrum = Matrix<4>::CreateFrustum(-40, 40, -50, 50, 10, 100);
	//PrintMyMatrixC(my_matrix_frustrum, "my_matrix_frustrum");
	//my_matrix_frustrum.Transpose();
	//PrintMyMatrixC(my_matrix_frustrum, "my_matrix_frustrum");
	REQUIRE_COMPARE_MATRIX(igad_matrix_frustrum, my_matrix_frustrum);


	igad::Matrix44 igad_matrix_perspective = igad::Matrix44::CreatePerspective(90.0, 4.0/3.0, 1.0, 128.0);
	Matrix<4> my_matrix_perspective = Matrix<4>::CreatePerspective(90.0, 4.0 / 3.0, 1.0, 128.0);
	REQUIRE_COMPARE_MATRIX(igad_matrix_perspective, my_matrix_perspective);
	igad::Matrix44 igad_matrix_perspective2 = igad::Matrix44::CreatePerspective(45.0, 4.0 / 3.0, 1.0, 1000.0);
	Matrix<4> my_matrix_perspective2 = Matrix<4>::CreatePerspective(45.0, 4.0 / 3.0, 1.0, 1000.0);
	REQUIRE_COMPARE_MATRIX(igad_matrix_perspective2, my_matrix_perspective2);

	igad::Matrix44 igad_transformation_matrix{
		1, 0, 2, 0,
		0, 1, 0, 0,
		1, 0, 1, 0,
		0, 0, 0, 1
	};
	igad::Vector3 igad_dir_vector{ 1, 1, 1 };
	igad::Vector3 igad_transformed_dir = igad_transformation_matrix.TransformDirectionVector(igad_dir_vector);

	Matrix<4> my_transformation_matrix{
		{ 1, 0, 2, 0 },
		{ 0, 1, 0, 0 },
		{ 1, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	};
	//my_transformation_matrix.Transpose();
	//TODO: Fix that method!
	Vector3 my_dir_vector{ 1, 1, 1 };
	Vector3 my_transformed_dir = my_transformation_matrix.TransformDirectionVector(my_dir_vector);
	REQUIRE(compare_vector(igad_transformed_dir, my_transformed_dir));
}

TEST_CASE("igad::Vector comparison")
{
	igad::Vector3 igad_vec3{ 1,2 ,3 };
	igad::Vector2 igad_vec2{ 1, 2 };
	igad::Vector4 igad_vec4{ 1,2,3,4 };

	Vector3 my_vec3{ 1,2,3 };
	Vector2 my_vec2{ 1,2 };
	Vector4 my_vec4{ 1,2,3,4 };

	REQUIRE(compare_vector(igad_vec3+igad_vec3, my_vec3+my_vec3));
	REQUIRE(igad_vec3.Dot(igad_vec3)== my_vec3.Dot(my_vec3));
	REQUIRE(compare_vector(igad_vec3.Cross(igad_vec3), my_vec3.Cross(my_vec3)));
	//REQUIRE(compare_vector(igad_vec3.Slerp(0.3f, { 2, 10, 10 }), my_vec3.Slerp(0.3f, {10, 10, 10}) ));
	
}
