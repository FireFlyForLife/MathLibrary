#pragma once
#include "Matrix.h"
#include <Matrix44.h>
#include <iostream>
#include <glm/mat4x4.hpp>
#include "ToString.h"

using namespace std;
using namespace Math;

#define str(s) #s
#define REQUIRE_COMPARE_MATRIX(a, b) REQUIRE(compare_matrix(a, b, str(a), str(b)));

template<unsigned w, unsigned h>
static void PrintMyMatrixC(const Matrix<w, h>& m, const char* name = nullptr)
{
	if (name)
		cout << string(name) << "\n" << Math::ToString(m) << endl;
	else
		cout << Math::ToString(m) << endl;

}
#define PRINT_MINE(mat) PrintMyMatrixC(mat, str(mat))

static void PrintIgadMatrixC(const igad::Matrix44& m, const char* name = nullptr)
{
	if (name)
		cout << string(name) << "\n";

	std::string matrix;
	for (unsigned y = 0; y < 4; y++)
	{
		std::string line = "[ ";
		for (unsigned x = 0; x < 4; x++)
		{
			line += std::to_string(m.m[x][y]) + ' ';
		}
		line += "]\n";
		matrix += line;
	}

	cout << matrix << endl;

}
#define PRINT_IGAD(mat) PrintIgadMatrixC(mat, str(mat))

static void PrintGlmMatrixC(const glm::mat4& m, const char* name = nullptr)
{
	if (name)
		cout << string(name) << "\n";

	std::string matrix;
	for (unsigned c = 0; c < 4; c++)
	{
		std::string line = "[ ";
		for (unsigned r = 0; r < 4; r++)
		{
			line += std::to_string(m[r][c]) + ' ';
		}
		line += "]\n";
		matrix += line;
	}

	cout << matrix << endl;
}
#define PRINT_GLM(mat) PrintGlmMatrixC(mat, str(mat));


#define REQUIRE_COMPARE_VECTOR(a, b) REQUIRE(compare_vector(a, b, str(a), str(b)))

static bool compare_vector(const igad::Vector3& a, const Vector3& b, const char* nameA = nullptr, const char* nameB = nullptr)
{
	bool equal = (Math::fequals(a.x, b.x) &&
		Math::fequals(a.y, b.y) &&
		Math::fequals(a.z, b.z));

	if (!equal)
	{
		if (nameA)
			cout << nameA << '\n';
		cout << "[" << std::to_string(a.x) << ", " << std::to_string(a.y) << ", " << std::to_string(a.z) << "]" << endl;

		if (nameB)
			cout << nameB << '\n';
		cout << "[" << std::to_string(b.x) << ", " << std::to_string(b.y) << ", " << std::to_string(b.z) << "]" << endl;

	}

	return equal;
}

static bool compare_vector(const glm::vec4& a, const Vector4& b, const char* nameA = nullptr, const char* nameB = nullptr)
{
	bool equal = (Math::fequals(a.x, b.x) &&
		Math::fequals(a.y, b.y) &&
		Math::fequals(a.z, b.z));

	if (!equal)
	{
		if (nameA)
			cout << nameA << '\n';
		cout << "[" << std::to_string(a.x) << ", " << std::to_string(a.y) << ", " << std::to_string(a.z) << "]" << endl;

		if (nameB)
			cout << nameB << '\n';
		cout << "[" << std::to_string(b.x) << ", " << std::to_string(b.y) << ", " << std::to_string(b.z) << "]" << endl;

	}

	return equal;
}

template<unsigned rows, unsigned columns, unsigned other_rows, unsigned other_columns>
static bool compare_matrix(const Math::Matrix<rows, columns>& a, const Math::Matrix<other_rows, other_columns>& b, const char* nameA = nullptr, const char* nameB = nullptr)
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			if (!Math::fequals(a[r][c], b[r][c])) {
				PrintMyMatrixC(a, nameA);
				PrintMyMatrixC(b, nameB);

				return false;
			}
		}
	}

	return true;
}

template<unsigned rows, unsigned columns>
static bool compare_matrix(const igad::Matrix44& a, const Matrix<rows, columns>& b, const char* nameA = nullptr, const char* nameB = nullptr)
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			if (!Math::fequals(a.m[r][c], b.m[r][c])) {
				PrintIgadMatrixC(a, nameA);
				PrintMyMatrixC(b, nameB);

				return false;
			}
		}
	}

	return true;
}

template<unsigned rows, unsigned columns>
static bool compare_matrix(const glm::mat4& a, const Matrix<rows, columns>& b, const char* nameA = nullptr, const char* nameB = nullptr)
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			if (!Math::fequals(a[r][c], b.m[r][c])) {
				PrintGlmMatrixC(a, nameA);
				PrintMyMatrixC(b, nameB);

				return false;
			}
		}
	}

	return true;
}

static bool compare_matrix(const igad::Matrix44& a, const igad::Matrix44& b, const char* nameA = nullptr, const char* nameB = nullptr)
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			if (!Math::fequals(a.m[r][c], b.m[r][c]))
			{
				PrintIgadMatrixC(a, nameA);
				PrintIgadMatrixC(b, nameB);
				return false;

			}
		}
	}

	return true;
}

static bool compare_matrix(const glm::mat4& a, const igad::Matrix44& b, const char* nameA = nullptr, const char* nameB = nullptr)
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			if (!Math::fequals(a[r][c], b.m[r][c]))
			{
				PrintGlmMatrixC(a, nameA);
				PrintIgadMatrixC(b, nameB);
				return false;

			}
		}
	}

	return true;
}
