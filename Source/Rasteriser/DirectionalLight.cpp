#include "DirectionalLight.h"
#include <math.h> 

DirectionalLight::DirectionalLight() {};

DirectionalLight::DirectionalLight(Vector3D _direction) 
{
	direction = _direction;
	direction.normalise();
};

DirectionalLight::~DirectionalLight() {};

DirectionalLight::DirectionalLight(const DirectionalLight& dl)
{
	r = dl.r;
	g = dl.g;
	b = dl.b;
	direction = dl.direction;
};

const int DirectionalLight::GetIntensity(const int i) const
{
	int colours[3];
	colours[0] = r;
	colours[1] = g;
	colours[2] = b;

	return colours[i];
};


void DirectionalLight::SetIntensity(const int _r, const int _g, const int _b) 
{
	r = _r;
	g = _g;
	b = _b;
};

const Vector3D DirectionalLight::returnDirection() const 
{
	return direction;
};

DirectionalLight& DirectionalLight::operator= (const DirectionalLight &rhs)
{
	if (this != &rhs)
	{
		r = rhs.r;
		g = rhs.g;
		b = rhs.b;
		direction = rhs.direction;
	}
	return *this;
};