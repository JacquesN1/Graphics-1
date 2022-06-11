#pragma once

class UVCoordinates
{
public:
	UVCoordinates();
	UVCoordinates(int _u, int _v);
	~UVCoordinates();
	UVCoordinates(const UVCoordinates& uv);
	UVCoordinates& operator= (const UVCoordinates& rhs);

	void SetU(int _u);
	int GetU();
	void SetV(int _v);
	int GetV();
	
private:
	int u;
	int v;
};