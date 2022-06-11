#pragma once
#include "Vector3D.h"
#include <vector>

class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	~Polygon3D();
	Polygon3D(const Polygon3D& p);

	// Accessor to return index of specified vertex
	int GetIndex(int) const;
	bool GetMarked() const;
	void SetMarked(const bool m);
	float GetAverage() const;
	void SetAverage(const float avg);
	const int GetR() const;
	const int GetG() const;
	const int GetB() const;
	void SetColour(const int r, const int g, const int b);
	const Vector3D getNormal() const;
	void SetNormal(Vector3D _normal);
	Polygon3D& operator= (const Polygon3D &rhs);

private:
	int _indices[3];
	bool marked;
	float averageDepth;
	int colour[3];
	Vector3D normal;
	void Copy(const Polygon3D& other);
};
