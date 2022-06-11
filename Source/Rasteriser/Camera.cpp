#include "Camera.h"
#include <math.h>  

Camera::Camera()
{};

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
{
	Matrix VeiwingTransformationMatrix1(1, 0, 0, (position.GetX()*-1), 0, 1, 0, (position.GetY()*-1), 0, 0, 1, (position.GetZ()*-1), 0, 0, 0, 1);
	Matrix VeiwingTransformationMatrix2(1, 0, 0, 0, 0, (float)cos(xRotation), (float)sin(xRotation), 0, 0, (float)(sin(xRotation)*-1), (float)cos(xRotation), 0, 0, 0, 0, 1);
	Matrix VeiwingTransformationMatrix3((float)cos(yRotation), 0, (float)(sin(yRotation)*-1), 0, 0, 1, 0, 0, (float)sin(yRotation), 0, (float)cos(yRotation), 0, 0, 0, 0, 1);
	Matrix VeiwingTransformationMatrix4((float)cos(zRotation), (float)sin(zRotation), 0, 0, (float)(sin(zRotation)*-1), (float)cos(zRotation), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

	CameraMatrix = VeiwingTransformationMatrix1.operator*(VeiwingTransformationMatrix2.operator*(VeiwingTransformationMatrix3.operator*(VeiwingTransformationMatrix4)));
};

Matrix& Camera::GetCM()
{
	return CameraMatrix;
}

