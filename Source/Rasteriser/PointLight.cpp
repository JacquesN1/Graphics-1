#include "PointLight.h"

PointLight::PointLight() {};

PointLight::PointLight(int _a, int _b, int _c, Vertex _position) 
{
	a = _a;
	b = _b;
	c = _c;
	position = _position;
};

PointLight::~PointLight() {};

PointLight::PointLight(const PointLight& pl)
{
	a = pl.a;
	b = pl.b;
	c = pl.c;
	red = pl.red;
	green = pl.green;
	blue = pl.blue;
	position = pl.position;
};

const int PointLight::GetIntensity(const int i) const
{
	int colours[3];
	colours[0] = red;
	colours[1] = green;
	colours[2] = blue;

	return colours[i];
};

const int PointLight::GetAttenuationCoefficients(const int i) const
{
	int coefficients[3];
	coefficients[0] = a;
	coefficients[1] = b;
	coefficients[2] = c;

	return coefficients[i];
};

void PointLight::SetIntensity(const int _r, const int _g, const int _b)
{
	red = _r;
	green = _g;
	blue = _b;
};

PointLight& PointLight::operator= (const PointLight &rhs)
{
	if (this != &rhs)
	{
		a = rhs.a;
		b = rhs.b;
		c = rhs.c;
		position = rhs.position;
		red = rhs.red;
		green = rhs.green;
		blue = rhs.blue;
	}
	return *this;
};

const Vertex PointLight::GetPosition() const 
{
	return position;
};