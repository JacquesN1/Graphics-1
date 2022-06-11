#pragma once 
#include "Vertex.h" 
#include <initializer_list> 

class Matrix
{
public:
	// Default constructor  
	Matrix() {};

	// Constructor that initialises all elements.  Note that an initialiser 
	// list is used to pass in the values.  This is a new C++ feature.   
	Matrix(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p);

	// Copy constructor   
	Matrix(const Matrix& other);

	// Destructor  
	~Matrix();

	// Retrieve value in matrix at specified row and column   
	float GetM(const int row, const int column) const;

	// Set value in matrix at specified row and column   
	void SetM(const int row, const int column, const float value);

	// Copy assignment operator  
	Matrix& operator=(const Matrix &rhs);

	// Multiply two matrices together   
	const Matrix operator*(const Matrix &other) const;

	// Multiply a matrix by a vertex, returning a vertex   
	const Vertex operator*(const Vertex &other) const;

private:

	 float _Matrix[4][4];
	 void Copy(const Matrix& other);
};
