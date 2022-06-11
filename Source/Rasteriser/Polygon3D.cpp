#include "Polygon3D.h"

Polygon3D::Polygon3D() {};

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	marked = false;
}

Polygon3D::~Polygon3D() {};

Polygon3D::Polygon3D(const Polygon3D& p) 
{
	_indices[0] = p._indices[0];
	_indices[1] = p._indices[1];
	_indices[2] = p._indices[2];
	marked = p.marked;
	averageDepth = p.averageDepth;
	colour[0] = p.colour[0];
	colour[1] = p.colour[1];
	colour[2] = p.colour[2];
	normal = p.normal;
};

int Polygon3D::GetIndex(int i) const 
{
	return _indices[i];
};

bool Polygon3D::GetMarked() const
{
	return marked;
};

void Polygon3D::SetMarked(const bool m)
{
	marked = m;
}

float Polygon3D::GetAverage() const
{
	return averageDepth;
};

void Polygon3D::SetAverage(const float avg)
{
	averageDepth = avg;
}

const int Polygon3D::GetR() const
{
	return colour[0];
};

const int Polygon3D::GetG() const
{
	return colour[1];
};

const int Polygon3D::GetB() const
{
	return colour[2];
};

void Polygon3D::SetColour(const int r, const int g, const int b)
{
	colour[0] = r;
	colour[1] = g;
	colour[2] = b;
}

const Vector3D Polygon3D::getNormal() const
{
	return normal;
};

void Polygon3D::SetNormal(Vector3D _normal)
{
	normal = _normal;
};

Polygon3D& Polygon3D::operator=(const Polygon3D &rhs)
{
	if (this != &rhs)
	{
		_indices[0] = rhs._indices[0];
		_indices[1] = rhs._indices[1];
		_indices[2] = rhs._indices[2];
		marked = rhs.marked;
		averageDepth = rhs.averageDepth;
		colour[0] = rhs.colour[0];
		colour[1] = rhs.colour[1];
		colour[2] = rhs.colour[2];
		normal = rhs.normal;
	}
	return *this;
};

void Polygon3D::Copy(const Polygon3D & other)
{
	for (int i = 0; i < 3; i++)
	{
		_indices[i]= other.GetIndex(i);
	}
	marked = other.GetMarked();
	averageDepth = other.GetAverage();
	SetColour(other.GetR(), other.GetG(), other.GetB());
}