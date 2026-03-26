#pragma once
#include <cmath>

namespace math
{
	static const float EPSILON = 0.00001f;

	static const float PI = 3.14159f;

	//checks if given 2 floats are equal 
	bool FEqual(float x, float y);

	//checks if given 2 floats are equal or greater
	bool FEqualGreater(float x, float y);

	//checks if given 2 floats are equal or smaller
	bool FEqualSmaller(float x, float y);

	float DegreeToRadian(float degree);


	int GetRandom(int min, int max);
}

