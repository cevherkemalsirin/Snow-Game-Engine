//============================================================================
// Name        : Vector 2D
// Author      : Cevher Kemal Sirin
// Version     : 1.0
// Copyright   : MIT
// Description : Vector class which consist of x and y axis.
//============================================================================

#pragma once
#include <iostream>
class Vector2D
{
private:
	float x;
	float y;

	friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec);
	friend Vector2D operator*(float scalar, const Vector2D& Vec);
public:
	static const Vector2D ZERO;
	//Constructors
	Vector2D() :Vector2D(0) {};
	explicit Vector2D(float value);
	Vector2D(float x, float y);

	//setters
	inline void SetX(float x) { this->x = x; }
	inline void SetY(float y) { this->y = y; }

	//getters
	inline float GetX() const { return this->x; }
	inline float GetY() const { return this->y; }

	//operators
	bool operator == (const Vector2D& vec2) const;
	bool operator != (const Vector2D& vec2) const;
	//negate the vector ---> to <---
	Vector2D operator-() const;
	Vector2D operator*(float scalar) const;
	Vector2D operator/(float scalar) const;
	Vector2D& operator*=(float scalar);
	Vector2D& operator/=(float scalar);
	//vector addition
	Vector2D operator+(const Vector2D& vec2) const;
	Vector2D operator-(const Vector2D& vec2) const;
	Vector2D& operator-=(const Vector2D& vec2);
	Vector2D& operator+=(const Vector2D& vec2);

	//vector magnitude / length of the vector
	float Magnitude() const;
	float Magnitude_square() const;
	//get unitVector or normalize
	Vector2D GetNormalized() const;
	Vector2D& Normalize();
	//Distance to the vector
	float DistanceTo(const Vector2D& target) const;
	//Dot Product
	float Dot(const Vector2D& vec2) const;
	/*
		 A
		/|
	   / |
	  /__|____B

	  A.B = cos# * |A| * |B|
	  if B is an unit vector it becomes
	  A.B = cos# * |A|
	  cos# is  shadow / |A|
	  then A.B = shadow
	  shadow * unit vector of B becomes shadow vector which is projected vector
	  */
	Vector2D DotVector(const Vector2D& vec2) const;

	//Get angles between 2 vectors
	/*
		a.b = |a| * |b| * cosA
		lets say they are unit vectors
		a.b = cosA
		A = acos(a.b)
	*/
	float GetAngleBetween(const Vector2D& vec2) const;
	//Get reflecting vector
	/*
		  __\/__ A.N * ||N|| Projected vector of N , multiply with -2 and add A we find reflection
	*/
	Vector2D ReflectedVector(const Vector2D& normal) const;

	//rotate vector around the point by given angle
	void RotateVector(float angle, const Vector2D& point);
	//Get rotated vector without rotating the original vector
	Vector2D RotatedVector(float angle, const Vector2D& point) const;
};


