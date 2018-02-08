#include "Catch2/catch.hpp"
#include <Matrix.h>
#include <Matrix44.h>
#include <iostream>
#include <ToString.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/matrix.hpp>

#include "MatrixDebugging.h"
#include <random>


inline float DegToRad(float deg) { return deg * Pi / 180.0f; }

using namespace std;
using namespace Math; // my own math

TEST_CASE("Matrix perspective")
{
	const unsigned int seed = 123;
	std::mt19937 rng_engine{seed};
	std::uniform_real_distribution<float> fov_distr{ 5, 90 };
	std::uniform_real_distribution<float> dist_distr{ 10, 1000 };
	std::uniform_real_distribution<float> ratio_distr{ 1, 1.5 };

	const int test_amount = 100;
	for (int i = 0; i < test_amount; i++) {
		/*float fov = 60.0f;
		float dist = 100.0f;
		float ratio = 800 / 600;*/

		float fov = fov_distr(rng_engine);
		float dist = dist_distr(rng_engine);
		float ratio = ratio_distr(rng_engine);

		Matrix44 my_projection = Matrix44::CreatePerspective(DegToRad(fov), ratio, 0.1f, 2000.0f);
		glm::mat4 glm_projection = glm::perspective(DegToRad(fov), ratio, 0.1f, 2000.0f);
		igad::Matrix44 igad_projection = igad::Matrix44::CreatePerspective(DegToRad(fov), ratio, 0.1f, 2000.0f);

		REQUIRE_COMPARE_MATRIX(glm_projection, my_projection);
		REQUIRE_COMPARE_MATRIX(igad_projection, my_projection);
		REQUIRE_COMPARE_MATRIX(glm_projection, igad_projection);
	}
}

TEST_CASE("Matrix lookat func")
{
	const unsigned int seed = 123;
	std::mt19937 rng_engine{ seed };
	std::uniform_real_distribution<float> dist_distr{ 10, 1000 };

	const int test_amount = 100;
	for (int i = 0; i < test_amount; i++) {
		/*float fov = 60.0f;
		float dist = 100.0f;
		float ratio = 800 / 600;*/

		float dist = dist_distr(rng_engine);

		Matrix44 my_view = Matrix44::CreateLookAt(Vector3(0, dist, 0), Vector3(), Vector3(0, 0, 1));
		igad::Matrix44 igad_view = igad::Matrix44::CreateLookAt(igad::Vector3(0, dist, 0), igad::Vector3(), igad::Vector3(0, 0, 1));


		REQUIRE_COMPARE_MATRIX(igad_view, my_view);
	}
}

TEST_CASE("Compare stuff to Bojansteroids")
{

	float fov = 60.0f;
	float dist = 100.0f;
	float ratio = 800 / 600;
	Matrix44 my_view = Matrix44::CreateLookAt(Vector3(0, dist, 0), Vector3(), Vector3(0, 0, 1));
	Matrix44 my_projection = Matrix44::CreatePerspective(DegToRad(fov), ratio, 0.1f, 2000.0f);

	igad::Matrix44 igad_view = igad::Matrix44::CreateLookAt(igad::Vector3(0, dist, 0), igad::Vector3(), igad::Vector3(0, 0, 1));
	igad::Matrix44 igad_projection = igad::Matrix44::CreatePerspective(DegToRad(fov), ratio, 0.1f, 2000.0f);

	/*glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));*/
	glm::mat4 glm_projection = glm::perspective(DegToRad(fov), ratio, 0.1f, 2000.0f);
	glm::vec4 m;
	auto t = glm_projection*m;

	/*REQUIRE(compare_matrix(igad_view, my_view, "igad_view", "my_view"));
	REQUIRE(compare_matrix(igad_projection, my_projection, "igad_projection", "my_projection"));
	REQUIRE(compare_matrix(glm_projection, my_projection, "glm_projection", "glm_projection"));*/

	glm::mat4 glm_mat(1, 3, 1, 0,
		2, 4, 1, 0,
		1, 1, 1, 0,
		0, 0, 0, 1);
	glm::mat4 glm_mat2(5, 12, 3, 0,
		4, 3, 16, 0,
		3, 2, 10, 0,
		0, 0, 0, 1);
	Matrix<4> my_mat{ { 1, 3, 1, 0 },
		{ 2, 4, 1, 0 },
		{ 1, 1, 1, 0 },
		{ 0, 0, 0, 1} };
	Matrix<4> my_mat2{ {5,12, 3, 0},
		{4, 3, 16, 0 },
		{3, 2, 10, 0},
		{0, 0, 0, 1} };

	glm_mat *= glm_mat2;
	//PrintGlmMatrixC(glm::translate(glm::mat4{1}, { 1,0 ,0 }), "glm translate");
	my_mat *= my_mat2;
	REQUIRE_COMPARE_MATRIX(glm_mat2, my_mat2);
	REQUIRE_COMPARE_MATRIX(glm_mat, my_mat);

	Matrix<4> my_rotate_test = Matrix<4>::Identity;
	my_rotate_test = my_rotate_test.CreateRotate(1.f, Vector3(2, 3, 4));
	igad::Matrix44 igad_rotate_test = igad::Matrix44::CreateRotate(1.f, igad::Vector3(2, 3, 4));
	REQUIRE_COMPARE_MATRIX(igad_rotate_test, my_rotate_test);
}
