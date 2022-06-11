#include "UVCoordinates.h"

UVCoordinates::UVCoordinates() {};

UVCoordinates::UVCoordinates(int _u, int _v) 
{
	u = _u;
	v = _v;
};

UVCoordinates::~UVCoordinates() {};

UVCoordinates::UVCoordinates(const UVCoordinates& uv) 
{
	u = uv.u;
	v = uv.v;
};

void UVCoordinates::SetU(int _u) 
{
	u = _u;
};

int UVCoordinates::GetU() 
{
	return u;
};

void UVCoordinates::SetV(int _v) 
{
	v = _v;
};

int UVCoordinates::GetV() 
{
	return v;
};

UVCoordinates& UVCoordinates::operator=(const UVCoordinates& rhs) 
{

	if (this != &rhs)
	{
		u = rhs.u;
		v = rhs.v;
	}
	return *this;
};