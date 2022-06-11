#pragma once
#include "Vertex.h" 
#include "Polygon3D.h"
#include "Matrix.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"
#include "PointLight.h"
#include "Texture.h"
#include <vector>
#include <algorithm>  
#include <functional>   
#include <iostream>  

class Model
{
public:

	Model();
	~Model();

	Model(const Model& m);
	Model& operator= (const Model& rhs);

	// Accessors
	std::vector<Polygon3D>&	GetPolygons();
	std::vector<Vertex>& GetVertices();
	size_t GetPolygonCount() const;
	size_t GetVertexCount() const;
	void AddVertex(float x, float y, float z);
	void AddPolygon(int i0, int i1, int i2);

	void ApplyTransformToLocalVertices(const Matrix &transform);
	void ApplyTransformToTransformedVertices(const Matrix &transform);
	void DehomogenizeTransformedVertices();
	void CalculateBackfaces(Vertex cameraPosition);
	void Sort(void);
	void CalculateLightingDirectional(std::vector<DirectionalLight>);
	void CalculateLightingDirectionalGouraud(std::vector<DirectionalLight>);
	void CalculateLightingAmbient(AmbientLight _ambientLight);
	void CalculateLightingAmbientGouraud(AmbientLight _ambientLight);
	void CalculateLightingPoint(std::vector<PointLight>);
	void CalculateLightingPointGouraud(std::vector<PointLight>);
	void CalculateNormalVectors();

private:
	std::vector<Polygon3D> _polygons;
	std::vector<Vertex> _vertices;
	std::vector<Vertex> TransformedVertices;
	float w = 1;
	float ka_r;
	float ka_g;
	float ka_b;
	float kd_r;
	float kd_g;
	float kd_b;
	float kf_r;
	float kf_g;
	float kf_b;
};