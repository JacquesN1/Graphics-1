#pragma once 
#include "Matrix.h" 

#include <initializer_list> 

		// Constructor that initialises all elements.  Note that an initialiser 
		// list is used to pass in the values.  This is a new C++ feature.   
		Matrix::Matrix(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p)
		{
			_Matrix[0][0] = a;
			_Matrix[0][1] = b;
			_Matrix[0][2] = c;
			_Matrix[0][3] = d;
			_Matrix[1][0] = e;
			_Matrix[1][1] = f;
			_Matrix[1][2] = g;
			_Matrix[1][3] = h; 
			_Matrix[2][0] = i;
			_Matrix[2][1] = j;
			_Matrix[2][2] = k;
			_Matrix[2][3] = l;
			_Matrix[3][0] = m;
			_Matrix[3][1] = n;
			_Matrix[3][2] = o;
			_Matrix[3][3] = p;
		};

		// Copy constructor   
		Matrix::Matrix(const Matrix& other) 
		{
			Copy(other);
		};

		// Destructor  
		Matrix::~Matrix() {};

		// Retrieve value in matrix at specified row and column   
		float Matrix::GetM(const int row, const int column) const
		{
			return _Matrix[row][column];
		};

		// Set value in matrix at specified row and column   
		void Matrix::SetM(const int row, const int column, const float value) 
		{
			_Matrix[row][column] = value;
		};

		// Copy assignment operator  
		Matrix& Matrix::operator=(const Matrix &rhs) 
		{
			if (this != &rhs)
			{
				Copy(rhs);
			}
			return *this;
		};

		// Multiply two matrices together    
		const Matrix Matrix::operator*(const Matrix &other) const 
		{
			Matrix newMatrix(
				((other.GetM(0, 0) * _Matrix[0][0]) + (other.GetM(0, 1) * _Matrix[1][0]) + (other.GetM(0, 2) * _Matrix[2][0]) + (other.GetM(0, 3) * _Matrix[3][0])),
				((other.GetM(0, 0) * _Matrix[0][1]) + (other.GetM(0, 1) * _Matrix[1][1]) + (other.GetM(0, 2) * _Matrix[2][1]) + (other.GetM(0, 3) * _Matrix[3][1])),
				((other.GetM(0, 0) * _Matrix[0][2]) + (other.GetM(0, 1) * _Matrix[1][2]) + (other.GetM(0, 2) * _Matrix[2][2]) + (other.GetM(0, 3) * _Matrix[3][2])),
				((other.GetM(0, 0) * _Matrix[0][3]) + (other.GetM(0, 1) * _Matrix[1][3]) + (other.GetM(0, 2) * _Matrix[2][3]) + (other.GetM(0, 3) * _Matrix[3][3])),
				((other.GetM(1, 0) * _Matrix[0][0]) + (other.GetM(1, 1) * _Matrix[1][0]) + (other.GetM(1, 2) * _Matrix[2][0]) + (other.GetM(1, 3) * _Matrix[3][0])),
				((other.GetM(1, 0) * _Matrix[0][1]) + (other.GetM(1, 1) * _Matrix[1][1]) + (other.GetM(1, 2) * _Matrix[2][1]) + (other.GetM(1, 3) * _Matrix[3][1])),
				((other.GetM(1, 0) * _Matrix[0][2]) + (other.GetM(1, 1) * _Matrix[1][2]) + (other.GetM(1, 2) * _Matrix[2][2]) + (other.GetM(1, 3) * _Matrix[3][2])),
				((other.GetM(1, 0) * _Matrix[0][3]) + (other.GetM(1, 1) * _Matrix[1][3]) + (other.GetM(1, 2) * _Matrix[2][3]) + (other.GetM(1, 3) * _Matrix[3][3])),
				((other.GetM(2, 0) * _Matrix[0][0]) + (other.GetM(2, 1) * _Matrix[1][0]) + (other.GetM(2, 2) * _Matrix[2][0]) + (other.GetM(2, 3) * _Matrix[3][0])),
				((other.GetM(2, 0) * _Matrix[0][1]) + (other.GetM(2, 1) * _Matrix[1][1]) + (other.GetM(2, 2) * _Matrix[2][1]) + (other.GetM(2, 3) * _Matrix[3][1])),
				((other.GetM(2, 0) * _Matrix[0][2]) + (other.GetM(2, 1) * _Matrix[1][2]) + (other.GetM(2, 2) * _Matrix[2][2]) + (other.GetM(2, 3) * _Matrix[3][2])),
				((other.GetM(2, 0) * _Matrix[0][3]) + (other.GetM(2, 1) * _Matrix[1][3]) + (other.GetM(2, 2) * _Matrix[2][3]) + (other.GetM(2, 3) * _Matrix[3][3])),
				((other.GetM(3, 0) * _Matrix[0][0]) + (other.GetM(3, 1) * _Matrix[1][0]) + (other.GetM(3, 2) * _Matrix[2][0]) + (other.GetM(3, 3) * _Matrix[3][0])),
				((other.GetM(3, 0) * _Matrix[0][1]) + (other.GetM(3, 1) * _Matrix[1][1]) + (other.GetM(3, 2) * _Matrix[2][1]) + (other.GetM(3, 3) * _Matrix[3][1])),
				((other.GetM(3, 0) * _Matrix[0][2]) + (other.GetM(3, 1) * _Matrix[1][2]) + (other.GetM(3, 2) * _Matrix[2][2]) + (other.GetM(3, 3) * _Matrix[3][2])),
				((other.GetM(3, 0) * _Matrix[0][3]) + (other.GetM(3, 1) * _Matrix[1][3]) + (other.GetM(3, 2) * _Matrix[2][3]) + (other.GetM(3, 3) * _Matrix[3][3])));
			return newMatrix;
		
		};

		// Multiply a matrix by a vertex, returning a vertex   
		const Vertex Matrix::operator*(const Vertex &other) const 
		{
			Vertex newVertex(
				((other.GetX() * _Matrix[0][0]) + (other.GetY() * _Matrix[0][1]) + (other.GetZ() * _Matrix[0][2]) + (other.GetW() * _Matrix[0][3])),
				((other.GetX() * _Matrix[1][0]) + (other.GetY() * _Matrix[1][1]) + (other.GetZ() * _Matrix[1][2]) + (other.GetW() * _Matrix[1][3])),
				((other.GetX() * _Matrix[2][0]) + (other.GetY() * _Matrix[2][1]) + (other.GetZ() * _Matrix[2][2]) + (other.GetW() * _Matrix[2][3])),
				((other.GetX() * _Matrix[3][0]) + (other.GetY() * _Matrix[3][1]) + (other.GetZ() * _Matrix[3][2]) + (other.GetW() * _Matrix[3][3])));
			newVertex.SetColour(other.GetR(), other.GetG(), other.GetB());
			newVertex.SetNormal(other.getNormal());
			newVertex.SetContributingCount (other.GetContributingCount());
			return newVertex;
		};	
		
		void Matrix::Copy(const Matrix & other)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					_Matrix[i][j] = other.GetM(i, j);
				}
			}
		}


