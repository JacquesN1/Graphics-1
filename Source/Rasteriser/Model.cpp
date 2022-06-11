 #include "Model.h"

Model::Model() 
{
	ka_r = 1.00;
	ka_g = 1.00;
	ka_b = 1.00;
	kd_r = 1.00;
	kd_g = 1.00;
	kd_b = 1.00;
	kf_r = 1.00;
	kf_g = 1.00;
	kf_b = 1.00;
};

Model::~Model() {};

Model::Model(const	Model& m)
{
	_vertices = m._vertices;
	_polygons = m._polygons;
	TransformedVertices = m.TransformedVertices;
	ka_r = m.ka_r;
	ka_g = m.ka_g;
	ka_b = m.ka_b;
	kd_r = m.kd_r;
	kd_g = m.kd_g;
	kd_b = m.kd_b;
	kf_r = m.kf_r;
	kf_g = m.kf_g;
	kf_b = m.kf_b;
};

void Model::AddVertex(float x, float y, float z) 
{
	Vertex NewVertex(x, y, z, w);
	_vertices.push_back(NewVertex);
};

void Model::AddPolygon(int i0, int i1, int i2)
{
	Polygon3D NewPolygon(i0,i1,i2);
	_polygons.push_back(NewPolygon);
};

std::vector<Polygon3D>& Model::GetPolygons() 
{
	return _polygons;
};

std::vector<Vertex>& Model::GetVertices()
{ 
	return TransformedVertices;
};

size_t Model::GetPolygonCount() const 
{
	return _polygons.size();
};

size_t Model::GetVertexCount() const
{
	return _vertices.size();
};

Model& Model::operator=(const Model& rhs)
{
	if (this != &rhs)
	{
		_vertices = rhs._vertices;
		_polygons = rhs._polygons;
		TransformedVertices = rhs.TransformedVertices;
		ka_r = rhs.ka_r;
		ka_g = rhs.ka_g;
		ka_b = rhs.ka_b;
		kd_r = rhs.kd_r;
		kd_g = rhs.kd_g;
		kd_b = rhs.kd_b;
		kf_r = rhs.kf_r;
		kf_g = rhs.kf_g;
		kf_b = rhs.kf_b;
	}
	return *this;
};

void Model::ApplyTransformToLocalVertices(const Matrix &transform) 
{
	if (TransformedVertices.size() != _vertices.size())
	{
		for each (Vertex v in _vertices)
		{
			TransformedVertices.push_back(transform.operator*(v));
		}
	}
	else for (int i = 0; i < TransformedVertices.size(); i++)
	{
		TransformedVertices.at(i) = transform.operator*(_vertices.at(i));
	}
};

void Model::ApplyTransformToTransformedVertices(const Matrix &transform)
{
	if (TransformedVertices.size() != 0)
	{
		for (int i = 0; i < TransformedVertices.size(); i++)
		{
			TransformedVertices.at(i) = transform.operator*(TransformedVertices.at(i));
		}
	}
};

void Model::DehomogenizeTransformedVertices()
{
	int i = 0;
	for each (Vertex v in TransformedVertices)
	{
		float X = v.GetX();
		float Y = v.GetY();
		float Z = v.GetZ();
		float W = v.GetW();

		Vertex DehomogenizedVertex(X / W, Y / W, Z / W, W / W);
		DehomogenizedVertex.SetColour(TransformedVertices[i].GetR(), TransformedVertices[i].GetG(), TransformedVertices[i].GetB());
		DehomogenizedVertex.SetNormal(TransformedVertices[i].getNormal());
		DehomogenizedVertex.SetContributingCount(TransformedVertices[i].GetContributingCount());

		TransformedVertices[i] = DehomogenizedVertex;
		i++;
	}
};

void Model::CalculateBackfaces(Vertex cameraPosition)
{
	for (int i = 0; i < _polygons.size(); i++) 
	{
		Vertex Vertex0 = TransformedVertices.at(_polygons[i].GetIndex(0));
		Vertex Vertex1 = TransformedVertices.at(_polygons[i].GetIndex(1));
		Vertex Vertex2 = TransformedVertices.at(_polygons[i].GetIndex(2));

		Vector3D VectorA = Vertex0.subtract(Vertex1);
		Vector3D VectorB = Vertex0.subtract(Vertex2);

		Vector3D normal = VectorB.CrossProduct(VectorA);
		_polygons[i].SetNormal(normal);
		Vector3D eyeVector = Vertex0.subtract(cameraPosition);
		float dotProduct = normal.DotProduct(eyeVector);

		if (dotProduct < 0)
		{
			_polygons[i].SetMarked(true);
		}
		else
		{
			_polygons[i].SetMarked(false);
		}
	}
}

bool UDgreater(Polygon3D p1, Polygon3D p2)
{
	return p1.GetAverage() > p2.GetAverage();
}

void Model::Sort(void) 
{
	for (int i = 0; i < _polygons.size(); i++)
	{
		Vertex Vertex0 = TransformedVertices.at(_polygons[i].GetIndex(0));
		Vertex Vertex1 = TransformedVertices.at(_polygons[i].GetIndex(1));
		Vertex Vertex2 = TransformedVertices.at(_polygons[i].GetIndex(2));

		float average = (Vertex0.GetZ() + Vertex1.GetZ() + Vertex2.GetZ()) / 3;
		_polygons[i].SetAverage(average);
	}
 	sort(_polygons.begin(), _polygons.end(), UDgreater);
};

void Model::CalculateLightingDirectional(std::vector<DirectionalLight> directionalLights)
{
	float totalR;
	float totalG;
	float totalB;
	float tempR;
	float tempG;
	float tempB;

	for (int i = 0; i < _polygons.size(); i++)
	{
		totalR = (float)_polygons[i].GetR();
		totalG = (float)_polygons[i].GetG();
		totalB = (float)_polygons[i].GetB();

		for (int _i = 0; _i < directionalLights.size(); _i++)
		{
			tempR = directionalLights[_i].GetIntensity(0) * kd_r;
			tempG = directionalLights[_i].GetIntensity(1) * kd_g;
			tempB = directionalLights[_i].GetIntensity(2) * kd_b;

			float dotProduct = directionalLights[_i].returnDirection().DotProduct(_polygons[i].getNormal());
			tempR = tempR * dotProduct;
			tempG = tempG * dotProduct;
			tempB = tempB * dotProduct;

			totalR = totalR + tempR;
			totalG = totalG + tempG;
			totalB = totalB + tempB;
		}
		if (totalR < 0)
		{
			totalR = 0;
		}
		else if (totalR > 255)
		{
			totalR = 255;
		}

		if (totalG < 0)
		{
			totalG = 0;
		}
		else if (totalG > 255)
		{
			totalG = 255;
		}

		if (totalB < 0)
		{
			totalB = 0;
		}
		else if (totalB > 255)
		{
			totalB = 255;
		}

		_polygons[i].SetColour((int)totalR, (int)totalG, (int)totalB);
	}
};

void Model::CalculateLightingDirectionalGouraud(std::vector<DirectionalLight> directionalLights)
{
	float totalR;
	float totalG;
	float totalB;
	float tempR;
	float tempG;
	float tempB;

	for (int i = 0; i < TransformedVertices.size(); i++)
	{
		totalR = (float)TransformedVertices[i].GetR();
		totalG = (float)TransformedVertices[i].GetG();
		totalB = (float)TransformedVertices[i].GetB();

		for (int _i = 0; _i < directionalLights.size(); _i++)
		{
			tempR = directionalLights[_i].GetIntensity(0) * kd_r;
			tempG = directionalLights[_i].GetIntensity(1) * kd_g;
			tempB = directionalLights[_i].GetIntensity(2) * kd_b;

 			float dotProduct = directionalLights[_i].returnDirection().DotProduct(TransformedVertices[i].getNormal());
			tempR = tempR * dotProduct;
			tempG = tempG * dotProduct;
			tempB = tempB * dotProduct; 

			totalR = totalR + tempR;
			totalG = totalG + tempG;
			totalB = totalB + tempB;
		}
		if (totalR < 0)
		{
			totalR = 0;
		}
		else if (totalR > 255)
		{
			totalR = 255;
		}

		if (totalG < 0)
		{
			totalG = 0;
		}
		else if (totalG > 255)
		{
			totalG = 255;
		}

		if (totalB < 0)
		{
			totalB = 0;
		}
		else if (totalB > 255)
		{
			totalB = 255;
		}

		TransformedVertices[i].SetColour((int)totalR, (int)totalG, (int)totalB);
	}
};

void Model::CalculateLightingAmbient(AmbientLight _ambientLight) 
{
	float totalR;
	float totalG;
	float totalB;
	float tempR;
	float tempG;
	float tempB;

	for (int i = 0; i < _polygons.size(); i++)
	{
		totalR = 0;
		totalG = 0;
		totalB = 0;

		tempR = _ambientLight.GetR() * ka_r;
		tempG = _ambientLight.GetG() * ka_g;
		tempB = _ambientLight.GetB() * ka_b;

		totalR = totalR + tempR;
		totalG = totalG + tempG;
		totalB = totalB + tempB;

		if (totalR < 0)
		{
			totalR = 0;
		}
		else if (totalR > 255)
		{
			totalR = 255;
		}

		if (totalG < 0)
		{
			totalG = 0;
		}
		else if (totalG > 255)
		{
			totalG = 255;
		}

		if (totalB < 0)
		{
			totalB = 0;
		}
		else if (totalB > 255)
		{
			totalB = 255;
		}

		_polygons[i].SetColour((int)totalR, (int)totalG, (int)totalB);
	}
};

void Model::CalculateLightingAmbientGouraud(AmbientLight _ambientLight)
{
	float totalR;
	float totalG;
	float totalB;
	float tempR;
	float tempG;
	float tempB;

	for (int i = 0; i < TransformedVertices.size(); i++)
	{
		totalR = 0;
		totalG = 0;
		totalB = 0;

		tempR = _ambientLight.GetR() * ka_r; 
		tempG = _ambientLight.GetG() * ka_g;
		tempB = _ambientLight.GetB() * ka_b;

		totalR = totalR + tempR;
		totalG = totalG + tempG;
		totalB = totalB + tempB;

		if (totalR < 0)
		{
			totalR = 0;
		}
		else if (totalR > 255)
		{
			totalR = 255;
		}

		if (totalG < 0)
		{
			totalG = 0;
		}
		else if (totalG > 255)
		{
			totalG = 255;
		}

		if (totalB < 0)
		{
			totalB = 0;
		}
		else if (totalB > 255)
		{
			totalB = 255;
		}

		TransformedVertices[i].SetColour((int)totalR, (int)totalG, (int)totalB);
	}
};

void Model::CalculateLightingPoint(std::vector<PointLight> PointLights) 
{
	float totalR;
	float totalG;
	float totalB;
	float tempR;
	float tempG;
	float tempB;

	for (int i = 0; i < _polygons.size(); i++)
	{
		totalR = (float)_polygons[i].GetR();
		totalG = (float)_polygons[i].GetG();
		totalB = (float)_polygons[i].GetB();

		for (int _i = 0; _i < PointLights.size(); _i++)
		{
			tempR = PointLights[_i].GetIntensity(0) * kd_r;
			tempG = PointLights[_i].GetIntensity(1) * kd_g;
			tempB = PointLights[_i].GetIntensity(2) * kd_b;

			Vertex point1 = _vertices.at(_polygons[i].GetIndex(0));
			Vertex point2 = PointLights[_i].GetPosition();
			Vector3D position = point1.subtract(point2);
			double d = sqrt(pow(position.GetX(), 2) + pow(position.GetY(), 2) + pow(position.GetZ(), 2));
			double  attentuation = 1 / (PointLights[_i].GetAttenuationCoefficients(0) + (PointLights[_i].GetAttenuationCoefficients(1) * d) + (PointLights[_i].GetAttenuationCoefficients(2) * pow(d, 2)));
			position.normalise();

			float dotProduct = position.DotProduct(_polygons[i].getNormal());
			tempR = tempR * dotProduct * (float)attentuation;
			tempG = tempG * dotProduct * (float)attentuation;
			tempB = tempB * dotProduct * (float)attentuation;

			totalR = totalR + tempR;
			totalG = totalG + tempG;
			totalB = totalB + tempB;
		}
		if (totalR < 0)
		{
			totalR = 0;
		}
		else if (totalR > 255)
		{
			totalR = 255;
		}

		if (totalG < 0)
		{
			totalG = 0;
		}
		else if (totalG > 255)
		{
			totalG = 255;
		}

		if (totalB < 0)
		{
			totalB = 0;
		}
		else if (totalB > 255)
		{
			totalB = 255;
		}

		_polygons[i].SetColour((int)totalR, (int)totalG, (int)totalB);
	}
};

void Model::CalculateLightingPointGouraud(std::vector<PointLight> PointLights)
{
	float totalR;
	float totalG;
	float totalB;
	float tempR;
	float tempG;
	float tempB;

	for (int i = 0; i < TransformedVertices.size(); i++)
	{
		totalR = (float)TransformedVertices[i].GetR();
		totalG = (float)TransformedVertices[i].GetG();
		totalB = (float)TransformedVertices[i].GetB();

		for (int _i = 0; _i < PointLights.size(); _i++)
		{
			tempR = PointLights[_i].GetIntensity(0) * kd_r;
			tempG = PointLights[_i].GetIntensity(1) * kd_g;
			tempB = PointLights[_i].GetIntensity(2) * kd_b;

			Vertex point1 = TransformedVertices[i];
			Vertex point2 = PointLights[_i].GetPosition();
			Vector3D position = point1.subtract(point2);
			double d = sqrt(pow(position.GetX(), 2) + pow(position.GetY(), 2) + pow(position.GetZ(), 2));
			double  attentuation = 1 / (PointLights[_i].GetAttenuationCoefficients(0) + (PointLights[_i].GetAttenuationCoefficients(1) * d) + (PointLights[_i].GetAttenuationCoefficients(2) * pow(d, 2)));
			position.normalise();

			float dotProduct = position.DotProduct(TransformedVertices[i].getNormal());
			tempR = tempR * dotProduct * (float)attentuation;
			tempG = tempG * dotProduct * (float)attentuation;
			tempB = tempB * dotProduct * (float)attentuation;

			totalR = totalR + tempR;
			totalG = totalG + tempG;
			totalB = totalB + tempB;
		}
		if (totalR < 0)
		{
			totalR = 0;
		}
		else if (totalR > 255)
		{
			totalR = 255;
		}

		if (totalG < 0)
		{
			totalG = 0;
		}
		else if (totalG > 255)
		{
			totalG = 255;
		}

		if (totalB < 0)
		{
			totalB = 0;
		}
		else if (totalB > 255)
		{
			totalB = 255;
		}

		TransformedVertices[i].SetColour((int)totalR, (int)totalG, (int)totalB);
	}
};

void Model::CalculateNormalVectors() 
{
	for (int i = 0; i < TransformedVertices.size(); i++)
	{
		Vector3D reset(0, 0, 0);
		TransformedVertices[i].SetNormal(reset);
		TransformedVertices[i].SetContributingCount(0);
	}
	for (int i = 0; i < _polygons.size(); i++)
	{
		Vector3D Vector0 = TransformedVertices.at(_polygons[i].GetIndex(0)).getNormal() + _polygons[i].getNormal();
		TransformedVertices.at(_polygons[i].GetIndex(0)).SetNormal(Vector0);
		int newCount = TransformedVertices.at(_polygons[i].GetIndex(0)).GetContributingCount() + 1;
		TransformedVertices.at(_polygons[i].GetIndex(0)).SetContributingCount(newCount);

		Vector3D Vector1 = TransformedVertices.at(_polygons[i].GetIndex(1)).getNormal() + _polygons[i].getNormal();
		TransformedVertices.at(_polygons[i].GetIndex(1)).SetNormal(Vector1);
		newCount = TransformedVertices.at(_polygons[i].GetIndex(1)).GetContributingCount() + 1;
		TransformedVertices.at(_polygons[i].GetIndex(1)).SetContributingCount(newCount);

		Vector3D Vector2 = TransformedVertices.at(_polygons[i].GetIndex(2)).getNormal() + _polygons[i].getNormal();
		TransformedVertices.at(_polygons[i].GetIndex(2)).SetNormal(Vector2);
		newCount = TransformedVertices.at(_polygons[i].GetIndex(2)).GetContributingCount() + 1;
		TransformedVertices.at(_polygons[i].GetIndex(2)).SetContributingCount(newCount);
	}
	for (int i = 0; i < TransformedVertices.size(); i++)
	{
		Vector3D newNormal(TransformedVertices[i].getNormal());
		newNormal.SetX(newNormal.GetX() / TransformedVertices[i].GetContributingCount());
		newNormal.SetY(newNormal.GetY() / TransformedVertices[i].GetContributingCount());
		newNormal.SetZ(newNormal.GetZ() / TransformedVertices[i].GetContributingCount());
		newNormal.normalise();
		TransformedVertices[i].SetNormal(newNormal);
	}
};
