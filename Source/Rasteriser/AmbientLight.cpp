#include "AmbientLight.h"

AmbientLight::AmbientLight() {};

AmbientLight::AmbientLight(const int _r, const int _g, const int _b)
{
	r = _r;
	g = _g;
	b = _b;
};

AmbientLight::~AmbientLight() {};

AmbientLight::AmbientLight(const AmbientLight& dl)
{
	r = dl.r;
	g = dl.g;
	b = dl.b;
};

const int AmbientLight::GetR() const 
{
	return r;
};

const int AmbientLight::GetG() const 
{
	return g;
};

const int AmbientLight::GetB() const 
{
	return b;
};

AmbientLight& AmbientLight::operator= (const AmbientLight &rhs)
{
	if (this != &rhs)
	{
		r = rhs.r;
		g = rhs.g;
		b = rhs.b;
	}
	return *this;
};