#pragma once
#include "Vertex.h"
#include <math.h> 

class PointLight
{
public:
	PointLight();
	PointLight(int _a,int _b, int _c, Vertex _position);
	~PointLight();
	PointLight(const PointLight& pl);

	void SetIntensity(const int _r, const int _g, const int _b);
	const int GetIntensity(const int i) const;
	const int GetAttenuationCoefficients(const int i) const;
	const Vertex GetPosition() const;

	PointLight& operator= (const PointLight &rhs);

private:
	int red;
	int green;
	int blue;
	int a;
	int b;
	int c;
	Vertex position;
};