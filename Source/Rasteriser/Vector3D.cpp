#include "Vector3D.h"
#include <math.h>

Vector3D::Vector3D()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
}

Vector3D::Vector3D(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

Vector3D::Vector3D(const Vector3D& v)
{
	_x = v.GetX();
	_y = v.GetY();
	_z = v.GetZ();
}

Vector3D::~Vector3D()
{
}

float Vector3D::GetX() const
{
	return _x;
}

void Vector3D::SetX(const float x)
{
	_x = x;
}

float Vector3D::GetY() const
{
	return _y;
}

void Vector3D::SetY(const float y)
{
	_y = y;
}

float Vector3D::GetZ() const
{
	return _z;
}

void Vector3D::SetZ(const float z)
{
	_z = z;
}

Vector3D& Vector3D::operator=(const Vector3D& rhs)
{
	if (this != &rhs)
	{
		_x = rhs.GetX();
		_y = rhs.GetY();
		_z = rhs.GetZ();
	}
	return *this;
}

bool Vector3D::operator==(const Vector3D& rhs) const
{
	return (_x == rhs.GetX() && _y == rhs.GetY() && _z == rhs.GetZ());
}

const Vector3D Vector3D::operator+(const Vector3D& rhs) const
{
	return Vector3D(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ());
}


float Vector3D::DotProduct(const Vector3D &other) const
{
	float DotProduct = ((_x * other.GetX()) + (_y * other.GetY()) + (_z * other.GetZ()));
	return DotProduct;
}

const Vector3D Vector3D::CrossProduct(const Vector3D &other) const 
{
	Vector3D CrossProduct(((_y * other.GetZ()) - (_z * other.GetY())), ((_z * other.GetX()) - (_x * other.GetZ())), ((_x * other.GetY()) - (_y * other.GetX())));
	return CrossProduct;
}

void Vector3D::normalise()
{
	double length = sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2));

	_x = _x/ (float)length;
	_y = _y/ (float)length;
	_z = _z/ (float)length;
};

