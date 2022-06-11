#pragma once

class AmbientLight
{
public:
	AmbientLight();
	AmbientLight(const int _r, const int _g, const int _b);
	~AmbientLight();
	AmbientLight(const AmbientLight& al);

	const int GetR() const;
	const int GetG() const;
	const int GetB() const;

	AmbientLight& operator= (const AmbientLight &rhs);

private:
	int r;
	int g;
	int b;
};