#include "Math/Utils.h"

#include <random>

bool math::FEqual(float x, float y)
{
	return  fabsf(x - y) < EPSILON;
}

bool math::FEqualGreater(float x, float y)
{
	return FEqual(x, y) || x > y;
}

bool math::FEqualSmaller(float x, float y)
{
	return FEqual(x, y) || x < y;
}

float math::DegreeToRadian(float degree)
{
	return degree * (PI / 180.0f);
}



int math::GetRandom(int min, int max)
{
	std::random_device rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(eng);
}
