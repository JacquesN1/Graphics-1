#pragma once
#include "Matrix.h"

class Camera
{
public:
	Camera();
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);
	Matrix& GetCM();

private:
	Matrix CameraMatrix;
};