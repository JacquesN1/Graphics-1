#pragma once
#include "Vector3D.h"

class Vertex
{
public:
	Vertex();
	Vertex(float x, float y, float z, float w);

	// Copy constructor.  
	Vertex(const Vertex& v);

	// Destructer
	~Vertex();

	// Accessors
	float GetX() const;
	void SetX(const float x);
	float GetY() const;
	void SetY(const float y);
	float GetZ() const;
	void SetZ(const float z);
	float GetW() const;
	void SetW(const float w);

	const int GetR() const;
	const int GetG() const;
	const int GetB() const;
	void SetColour(const int r, const int g, const int b);

	const int GetContributingCount() const;
	void SetContributingCount(const int count);

	const Vector3D getNormal() const;
	void SetNormal(Vector3D _normal);

	// Assignment operator
	Vertex& operator= (const Vertex& rhs);

	bool operator== (const Vertex& rhs) const;

	const Vertex operator+ (const Vertex& rhs) const;

	const Vector3D subtract(const Vertex &other) const;

	const int GetUVRef() const;

	void SetUVRef(int _UVRef);

private:
	float _x;
	float _y;
	float _z;
	float _w;
	Vector3D normalVector;
	int colour[3];
	int contributingCount;
	int UVRef;
};
