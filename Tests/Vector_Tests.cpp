#include "Catch2/catch.hpp"
#include "Vectors.h"
#include <Matrix44.h>
#include <iostream>
#include "MatrixDebugging.h"

using namespace std;
using namespace Math;

TEST_CASE("Vector Math Operations")
{
	Vector2 vec1{ 4, 5 };
	Vector2 vec2{ 2, 3 };
	
	auto plus = vec1 + vec2;
	REQUIRE((plus == Vector2{6, 8}));


}

TEST_CASE("Vector Dot")
{
	{
		igad::Vector3 igad_dot_0{ 5, 6, 7 };
		Math::Vector3 my_dot_0{ 5, 6, 7 };
		igad::Vector3 igad_dot_1{ 3,4,5 };
		Math::Vector3 my_dot_1{ 3,4,5 };
		REQUIRE(igad_dot_0.Dot(igad_dot_1) == Approx(my_dot_0.Dot(my_dot_1)));
	}
	{
		glm::vec2 glm_dot_0{ 5, 6 };
		Math::Vector2 my_dot_0{ 5, 6 };
		glm::vec2 glm_dot_1{ 3,4 };
		Math::Vector2 my_dot_1{ 3,4 };
		REQUIRE(glm::dot(glm_dot_0, glm_dot_1) == Approx(my_dot_0.Dot(my_dot_1)));
	}
}

TEST_CASE("Vector Slerp")
{
	Vector3 vec1{ 1, 1, 0 };
	Vector3 vec2{0, 0, 1 };
	Vector3 vec1plus2 = vec1.Slerp(0.4, vec2);
	
	igad::Vector3 igad_vec1{ 1, 1, 0 };
	igad::Vector3 igad_vec2{ 0, 0, 1 };
	igad::Vector3 igad_vec1plus2 = igad_vec1.Slerp(0.4, igad_vec2);

	REQUIRE(compare_vector(igad_vec1plus2, vec1plus2, "igad_vec1plus2", "vec1plus2"));
	//TODO: More testing
}