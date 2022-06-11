#pragma once
class Vector3D
{
public:
	Vector3D();
	Vector3D(float x, float y, float z);

	// Copy constructor.  
	Vector3D(const Vector3D& v);

	// Destructer
	~Vector3D();

	// Accessors
	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float z);

	// Assignment operator
	Vector3D& operator= (const Vector3D& rhs);

	bool operator== (const Vector3D& rhs) const;

	const Vector3D operator+ (const Vector3D& rhs) const;

	float DotProduct(const Vector3D &other) const;

	const Vector3D CrossProduct(const Vector3D &other) const;

	void normalise();

private:
	float _x;
	float _y;
	float _z;
};