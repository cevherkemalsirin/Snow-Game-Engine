#include "Math/Vector2D.h"
#include "Math/Utils.h"

const Vector2D Vector2D::ZERO{ 0 };

Vector2D::Vector2D(float value) :x(value), y(value)
{
}

Vector2D::Vector2D(float x, float y) :x(x), y(y)
{

}

bool Vector2D::operator==(const Vector2D& vec2) const
{
	return (math::FEqual(this->GetX(), vec2.GetX()) && math::FEqual(this->GetY(), vec2.GetY()));
}

bool Vector2D::operator!=(const Vector2D& vec2) const
{
	return !(*this == vec2);
}

Vector2D Vector2D::operator-() const
{
	return Vector2D(-this->GetX(), -this->GetY());
}

Vector2D Vector2D::operator*(float scalar) const
{
	return Vector2D((this->GetX() * scalar), (this->GetY() * scalar));
}

Vector2D Vector2D::operator/(float scalar) const
{
	if (fabs(scalar) < math::EPSILON) { throw std::invalid_argument("Divaded By 0"); }

	return Vector2D((this->GetX() / scalar), (this->GetY() / scalar));
}

Vector2D& Vector2D::operator*=(float scalar)
{
	(*this) = (*this) * scalar;
	return *this;
}

Vector2D& Vector2D::operator/=(float scalar)
{
	(*this) = (*this) / scalar;
	return *this;
}

Vector2D Vector2D::operator+(const Vector2D& vec2) const
{
	return Vector2D((this->GetX() + vec2.GetX()), (this->GetY() + vec2.GetY()));
}

Vector2D Vector2D::operator-(const Vector2D& vec2) const
{
	return (*this + (-vec2));
}

Vector2D& Vector2D::operator-=(const Vector2D& vec2)
{
	*this = *this - vec2;
	return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& vec2)
{
	*this = *this + vec2;
	return *this;
}

float Vector2D::Magnitude() const
{
	return sqrt(this->Magnitude_square());
}

float Vector2D::Magnitude_square() const
{
	return (powf(this->GetX(), 2) + powf(this->GetY(), 2));
}

Vector2D Vector2D::GetNormalized() const
{
	float mag = this->Magnitude();
	if (mag <= math::EPSILON) { return ZERO; }

	return *this / mag;
}

Vector2D& Vector2D::Normalize()
{
	float mag = this->Magnitude();
	if (mag <= math::EPSILON) { return *this; }

	*this /= mag;
	return *this;
}

float Vector2D::DistanceTo(const Vector2D& target) const
{
	return (*this - target).Magnitude();
}

float Vector2D::Dot(const Vector2D& vec2) const
{
	return (this->GetX() * vec2.GetX()) + (this->GetY() * vec2.GetY());
}

Vector2D Vector2D::DotVector(const Vector2D& vec2) const
{
	//normalize the vec 2
	Vector2D normalizedVec2 = vec2.GetNormalized();
	//get dot product of vectors
	float dotProduct = this->Dot(normalizedVec2);
	//get dot vector
	return normalizedVec2 * dotProduct;
}

float Vector2D::GetAngleBetween(const Vector2D& vec2) const
{
	return acosf(this->GetNormalized().Dot(vec2.GetNormalized())); // gives in radian
}

Vector2D Vector2D::ReflectedVector(const Vector2D& normal) const
{
	return (2 * -this->DotVector(normal)) + *this;
}

Vector2D Vector2D::RotatedVector(float angle, const Vector2D& point) const
{
	float sinA = sinf(angle);
	float cosA = cosf(angle);
	Vector2D thisVector = *this;

	thisVector -= point;

	float rotX = thisVector.GetX() * cosA - thisVector.GetY() * sinA;
	float rotY = thisVector.GetY() * cosA + thisVector.GetX() * sinA;

	thisVector.SetX(rotX);
	thisVector.SetY(rotY);

	return thisVector + point;
}

void Vector2D::RotateVector(float angle, const Vector2D& point)
{
	*this = this->RotatedVector(angle, point);
}


//FRIENDS
std::ostream& operator<<(std::ostream& os, const Vector2D& vec)
{
	os << " x: " << vec.GetX() << " y: " << vec.GetY();
	return os;
}

Vector2D operator*(float scalar, const Vector2D& Vec)
{
	return Vec * scalar;
}
