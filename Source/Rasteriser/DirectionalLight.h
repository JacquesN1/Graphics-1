#pragma once
#include "Vector3D.h"

class DirectionalLight
{
public:
	DirectionalLight();
	DirectionalLight(Vector3D _direction);
	~DirectionalLight();
	DirectionalLight(const DirectionalLight& dl);

	const int GetIntensity(const int i) const;
	void SetIntensity(const int _r, const int _g, const int _b);
	const Vector3D returnDirection() const;

	DirectionalLight& operator= (const DirectionalLight &rhs);

private:
	int r;
	int g;
	int b;
	Vector3D direction;
};