#include "Rasteriser.h"
#include "MD2Loader.h"
#include "Model.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"
#include "PointLight.h"
#include <math.h> 
#include <algorithm>
#include <ctime>
#include <cstdlib>

#define PI 3.14159265

Rasteriser app;
Model _model;
Matrix PerspectiveMatrix;
Matrix VeiwMatrix;
Matrix RotationMatrixX;
Matrix RotationMatrixY;
Matrix RotationMatrixZ;
Matrix Translation;
Matrix Scale;
vector<DirectionalLight> DiretionalLights;
vector<PointLight> PointLights;
AmbientLight ambientLight(10, 10, 10);
int angleX = 5;
int angleY = 5;
int angleZ = 5;
float scale = 0.25;
float translate = 0.25;
int counter = 0;

bool Rasteriser::Initialise()
{
	Vector3D direction(0, -1, 0);
	DirectionalLight light(direction);
	light.SetIntensity(100, 100, 100);
	DiretionalLights.push_back(light);

	Vertex Position(0, 0, -5, 1);
	PointLight pointL(0, 1, 0, Position);
	pointL.SetIntensity(0, 100, 0);
	PointLights.push_back(pointL);

	

	if (!MD2Loader::LoadModel("teapot.md2", _model,
		&Model::AddPolygon,
		&Model::AddVertex))
	{
		return false;
	}

	return true;
} 

void GeneratePerspectiveMatrix(float d, float aspectRatio) 
{
	Matrix _PerspectiveMatrix(d/aspectRatio,0,0,0,0,d,0,0,0,0,d,0,0,0,1,0);
	PerspectiveMatrix = _PerspectiveMatrix;
};

void GenerateViewMatrix(float d, int width, int height) 
{
	Matrix _VeiwMatrix((float)width / 2, 0, 0, (float)width / 2, 0, (float)((height / 2)*-1), 0, (float)height / 2, 0, 0, (float)d / 2, (float)d / 2, 0, 0, 0, 1);
	VeiwMatrix = _VeiwMatrix;
};

void DrawWireFrame(Bitmap &bitmap) 
{
	vector <Vertex> verticies = _model.GetVertices();

	HDC hdc = bitmap.GetDC();
	HPEN hPen = CreatePen(PS_SOLID, 4, RGB(255, 255, 255));
	HGDIOBJ oldPen = SelectObject(hdc, hPen);

	for each (Polygon3D polygon in _model.GetPolygons())
	{
		if (polygon.GetMarked() == false) 
		{
			Vertex point1 = verticies.at(polygon.GetIndex(0));
			Vertex point2 = verticies.at(polygon.GetIndex(1));
			Vertex point3 = verticies.at(polygon.GetIndex(2));

			MoveToEx(hdc, (int)point1.GetX(), (int)point1.GetY(), NULL);
			LineTo(hdc, (int)point2.GetX(), (int)point2.GetY());
			LineTo(hdc, (int)point3.GetX(), (int)point3.GetY());
			LineTo(hdc, (int)point1.GetX(), (int)point1.GetY());
		}
	}
	SelectObject(hdc, oldPen);
	DeleteObject(hPen);
};

void DrawSolidFlat(Bitmap &bitmap)
{
	HDC hdc = bitmap.GetDC();
	vector <Vertex> verticies = _model.GetVertices();
	
	for each (Polygon3D polygon in _model.GetPolygons())
	{
		if (polygon.GetMarked() == false)
		{
			int r = polygon.GetR();
			int g = polygon.GetG();
			int b = polygon.GetB();

			HPEN Pen = CreatePen(PS_SOLID, 1, RGB(r,g,b));
			SelectObject(hdc, Pen);
			HBRUSH Brush = CreateSolidBrush(RGB(r, g, b));
			SelectObject(hdc, Brush);

			POINT points[3];
			Vertex point1 = verticies.at(polygon.GetIndex(0));
			Vertex point2 = verticies.at(polygon.GetIndex(1));
			Vertex point3 = verticies.at(polygon.GetIndex(2));

			points[0] = { (int)point1.GetX() ,(int)point1.GetY() };
			points[1] = { (int)point2.GetX() ,(int)point2.GetY() };
			points[2] = { (int)point3.GetX() ,(int)point3.GetY() };

			Polygon(hdc, points, 3);

			DeleteObject(Pen);
			DeleteObject(Brush);
		}
	}
}

void FillPolygonFlat(Vertex v1, Vertex v2, Vertex v3, int r, int g, int b, Bitmap &bitmap)
{
	HDC hdc = bitmap.GetDC();

	int maxX = max((int)v1.GetX(), max((int)v2.GetX(), (int)v3.GetX()));
	int minX = min((int)v1.GetX(), min((int)v2.GetX(), (int)v3.GetX()));
	int maxY = max((int)v1.GetY(), max((int)v2.GetY(), (int)v3.GetY()));
	int minY = min((int)v1.GetY(), min((int)v2.GetY(), (int)v3.GetY()));

	Vector3D vt1(v2.GetX() - v1.GetX(), v2.GetY() - v1.GetY(), 0);
	Vector3D vt2(v3.GetX() - v1.GetX(), v3.GetY() - v1.GetY(), 0);

	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			Vector3D q(x - v1.GetX(), y - v1.GetY(), 0);

			float s = (((q.GetX() * vt2.GetY()) - (q.GetY() * vt2.GetX())) / ((vt1.GetX() * vt2.GetY()) - (vt1.GetY() * vt2.GetX())));
			float t = (((vt1.GetX() * q.GetY()) - (vt1.GetY() * q.GetX())) / ((vt1.GetX() * vt2.GetY()) - (vt1.GetY() * vt2.GetX())));

			if ((s >= 0) && (t >= 0) && (s + t <= 1))
			{
				SetPixel(hdc, x, y, RGB(r, g, b));
			}
		}
	}
}
 
void MyDrawSolidFlat(Bitmap &bitmap)
{
	vector <Vertex> verticies = _model.GetVertices();
	for each (Polygon3D polygon in _model.GetPolygons())
	{
		if (polygon.GetMarked() == false)
		{
			FillPolygonFlat(verticies.at(polygon.GetIndex(0)), verticies.at(polygon.GetIndex(1)), verticies.at(polygon.GetIndex(2)), polygon.GetR(), polygon.GetG(), polygon.GetB(), bitmap);
		}
	}
};

void FillPolygonGouraud(Vertex v1, Vertex v2, Vertex v3, Bitmap &bitmap)
{
	HDC hdc = bitmap.GetDC();

	int deltaRed12 = v2.GetR() - v1.GetR();
	int deltaGreen12 = v2.GetG() - v1.GetG();
	int deltaBlue12 = v2.GetB() - v1.GetB();
	int deltaRed13 = v3.GetR() - v1.GetR();
	int deltaGreen13 = v3.GetG() - v1.GetG();
	int deltaBlue13 = v3.GetB() - v1.GetB();

	int maxX = max((int)v1.GetX(), max((int)v2.GetX(), (int)v3.GetX()));
	int minX = min((int)v1.GetX(), min((int)v2.GetX(), (int)v3.GetX()));
	int maxY = max((int)v1.GetY(), max((int)v2.GetY(), (int)v3.GetY()));
	int minY = min((int)v1.GetY(), min((int)v2.GetY(), (int)v3.GetY()));

	Vector3D vt1(v2.GetX() - v1.GetX(), v2.GetY() - v1.GetY(), 0);
	Vector3D vt2(v3.GetX() - v1.GetX(), v3.GetY() - v1.GetY(), 0);

	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			Vector3D q(x - v1.GetX(), y - v1.GetY(), 0);

			float s = (((q.GetX() * vt2.GetY()) - (q.GetY() * vt2.GetX())) / ((vt1.GetX() * vt2.GetY()) - (vt1.GetY() * vt2.GetX())));
			float t = (((vt1.GetX() * q.GetY()) - (vt1.GetY() * q.GetX())) / ((vt1.GetX() * vt2.GetY()) - (vt1.GetY() * vt2.GetX())));

			if ((s >= 0) && (t >= 0) && (s + t <= 1))
			{
				int r = v1.GetR() + (int)(s * deltaRed12) + (int)(t * deltaRed13);
				int g = v1.GetG() + (int)(s * deltaGreen12) + (int)(t * deltaGreen13);
				int b = v1.GetB() + (int)(s * deltaBlue12) + (int)(t * deltaBlue13);

				SetPixel(hdc, x, y, RGB(r, g, b));
			}
		}
	}
}

void DrawGouraud(Bitmap &bitmap)
{
	vector <Vertex> verticies = _model.GetVertices();
	for each (Polygon3D polygon in _model.GetPolygons())
	{
		if (polygon.GetMarked() == false)
		{
			FillPolygonGouraud(verticies.at(polygon.GetIndex(0)), verticies.at(polygon.GetIndex(1)), verticies.at(polygon.GetIndex(2)), bitmap);
		}
	}
};

void DrawString(Bitmap &bitmap, LPCTSTR text)
{
	HDC hdc = bitmap.GetDC();
	HFONT hFont, hOldFont;

	// Retrieve a handle to the variable stock font.  
	hFont = hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Myfont"));

	// Select the variable stock font into the specified device context. 
	if (hOldFont = (HFONT)SelectObject(hdc, hFont))
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));

		// Display the text string.  
		TextOut(hdc, 10, 10, text, lstrlen(text));

		// Restore the original font.        
		SelectObject(hdc, hOldFont);
	}
	DeleteObject(hFont);
}

void Rasteriser::Update(Bitmap &bitmap)
{
	Matrix _RotationMatrixY((float) cos(angleY * PI /180),0,(float)sin(angleY * PI/180),0,0,1,0,0,(float)(sin(angleY * PI/180)*-1),0, (float)cos(angleY * PI / 180),0,0,0,0,1);
	angleY++;
	RotationMatrixY = _RotationMatrixY;

	Matrix _RotationMatrixX(1,0,0,0,0,(float)cos(angleX * PI / 180), (float)(sin(angleX * PI / 180)*-1), 0, 0 , (float)sin(angleX * PI / 180), (float)cos(angleX * PI / 180), 0, 0, 0, 0, 1);
	angleX++;
	RotationMatrixX = _RotationMatrixX;

	Matrix _RotationMatrixZ((float)cos(angleZ * PI / 180), (float)(sin(angleZ * PI / 180)*-1),0,0, (float)sin(angleZ * PI / 180), (float)cos(angleZ * PI / 180),0,0,0,0,1,0,0,0,0,1);
	angleZ++;
	RotationMatrixZ = _RotationMatrixZ;

	Matrix _Translation(1, 0, 0, translate, 0, 1, 0, translate, 0, 0, 1, 0, 0, 0, 0, 1);
	Translation = _Translation;

	Matrix _Scale(scale, 0, 0, 0, 0, scale, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
	Scale = _Scale;

	float AspectRatio = float(bitmap.GetWidth()) / float(bitmap.GetHeight());
	GeneratePerspectiveMatrix(1, AspectRatio);

	GenerateViewMatrix(1, bitmap.GetWidth(), bitmap.GetHeight());
}

void Rasteriser::Render(Bitmap &bitmap)
{
	bitmap.Clear(RGB(0, 0, 0));

	if (counter <= 360 || counter >= 1080)
	{
		_model.ApplyTransformToLocalVertices(RotationMatrixY);

		if (counter <= 90)
		{
			DrawString(bitmap, L"Wire Frame model");
		}
		else if (counter <= 360)
		{
			DrawString(bitmap, L"Rotation of 5 degrees around the Y axis");
		}
	}
	else if (counter > 360 && counter <= 720)
	{
		_model.ApplyTransformToLocalVertices(RotationMatrixX);
		DrawString(bitmap, L"Rotation of 5 degrees around the X axis");
	}
	else if (counter > 720 && counter <= 900)
	{
		_model.ApplyTransformToLocalVertices(RotationMatrixZ);
		DrawString(bitmap, L"Rotation of 5 degrees around the Z axis");
	}
	else if (counter > 900 && counter <= 990)
	{
		translate++;
		_model.ApplyTransformToLocalVertices(Translation);
		DrawString(bitmap, L"Translation by 1 in X and Y");
	}
	else if (counter > 990)
	{
		scale++;
		_model.ApplyTransformToLocalVertices(Scale);
		DrawString(bitmap, L"Scale by 1 in X and Y");
	}


	Vertex position(0, 0, -10, 1);
	Camera c(0, 0, 0, position);

	if (counter >= 1080)
	{
		_model.CalculateBackfaces(position);
		_model.Sort();
		_model.CalculateNormalVectors();

		if (counter >= 1080 && counter < 1170)
		{
			DrawString(bitmap, L"Backface Culling");
		}
	}

	if (counter >= 1350 && counter < 1800)
	{
		_model.CalculateLightingAmbient(ambientLight);

		if (counter >= 1350 && counter < 1440)
		{
			DrawString(bitmap, L"Ambient Lighting (10,10,10)");
		}
	}

	if (counter >= 1800)
	{
		_model.CalculateLightingAmbientGouraud(ambientLight);

		if (counter >= 1800 && counter < 1890)
		{
			DrawString(bitmap, L"Ambient Lighting (10,10,10)");
		}
	}

	if (counter >= 1440 && counter < 1620)
	{
		_model.CalculateLightingDirectional(DiretionalLights);
		DrawString(bitmap, L"Directional Lighting (100,100,100) (0, 1, 0)");
	}

	if (counter >= 1890 && counter < 2070)
	{
		_model.CalculateLightingDirectionalGouraud(DiretionalLights);
		DrawString(bitmap, L"Directional Lighting (100,100,100) (0, 1, 0)");
	}

	if (counter >= 1620 && counter < 1800)
	{
		_model.CalculateLightingPoint(PointLights);
		DrawString(bitmap, L"Point Lighting (0,100,0) (0, -1, 0 ,(0, 0, -10, 1))");
    }

	if (counter >= 2070 )
	{
		_model.CalculateLightingPointGouraud(PointLights);
		DrawString(bitmap, L"Point Lighting (0,100,0) (0, -1, 0 ,(0, 0, -10, 1))");
	}

	_model.ApplyTransformToTransformedVertices(c.GetCM());

	float AspectRatio = float(bitmap.GetWidth()) / float(bitmap.GetHeight());
	GeneratePerspectiveMatrix(1, AspectRatio);
	_model.ApplyTransformToTransformedVertices(PerspectiveMatrix);
	_model.DehomogenizeTransformedVertices();

	GenerateViewMatrix(1, bitmap.GetWidth(), bitmap.GetHeight());
	_model.ApplyTransformToTransformedVertices(VeiwMatrix);

	if (counter < 1170)
	{
		DrawWireFrame(bitmap);
	}
	else if (counter >= 1170 && counter < 1260)
	{
		DrawSolidFlat(bitmap);
		DrawString(bitmap, L" Solid Figure");
	}
	else if (counter >= 1260 && counter < 1800)
	{
		MyDrawSolidFlat(bitmap);
		if (counter >= 1260 && counter < 1350)
		{
			DrawString(bitmap, L" Flat Shading");
		}
	}
	else
	{
		DrawGouraud(bitmap);
		if (counter >= 1800 && counter < 1890)
		{
			DrawString(bitmap, L"Gouraud Shading");
		}
	}

	counter++;

	if (counter >= 2250)
	{
		counter = 0;
	}
}
