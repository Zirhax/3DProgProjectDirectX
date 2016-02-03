#include "ObjectFactory.h"



ObjectFactory::ObjectFactory()
{
}


ObjectFactory::~ObjectFactory()
{
}

bool ObjectFactory::CreateObject(D3Object * storeIn, char * fileName, FactoryObjectFormat objectFormat)
{
	switch (objectFormat)
	{
	default:
		break;
	}
	return true;
}

bool ObjectFactory::ReadOBJ(D3Object * storeIn, char * fileName)
{
	ifstream fileIn;
	string special = "", line = "", line2 = "";
	istringstream inputString;
	vector<Vector3> vertices;
	vector<Vector3> normals;
	vector<Vector2> UV;
	vector<VertexModel> vertexData;
	Vector3 vtx = { 0, 0, 0 }, vn = { 0, 0, 0 };
	Vector2 vt = { 0, 0 };

	fileIn.open(fileName, ios::in);
	if (!fileIn.is_open())
	{
		return false;
	}

	while (std::getline(fileIn, line2))
	{
		inputString.str(line2);
		if (line2.substr(0, 2) == "v ")
		{
			// Vertex Position
			inputString >> special >> vtx.x >> vtx.y >> vtx.z;
			vertices.push_back(vtx);
		}
		else if (line2.substr(0, 2) == "vt")
		{
			// Vertex UV
			inputString >> special >> vt.x >> vt.y;
			UV.push_back(vt);
		}
		else if (line2.substr(0, 2) == "vn")
		{
			// Vertex Normal
			inputString >> special >> vn.x >> vn.y >> vn.z;
			normals.push_back(vn);
		}
		else if (line2.substr(0, 2) == "g ")
		{
			//Group name
		}
		else if (line2.substr(0, 7) == "mtllib ")
		{
			//Material name
		}
		else if (line2.substr(0, 2) == "f ")
		{
			//Vertex Normal Indices in format f v1/vt1/vn1
			char temp[512];
			strncpy(temp, line2.c_str(), sizeof(temp));
			temp[sizeof(temp) - 1] = 0;
			char* pos = strstr(temp, "f ");
			Vector3 faceIndices[3];
			sscanf(pos, "%s %i/%i/%i %i/%i/%i %i/%i/%i\n", &special, &faceIndices[0].x, &faceIndices[0].y, &faceIndices[0].z,
				&faceIndices[1].x, &faceIndices[1].y, &faceIndices[1].z,
				&faceIndices[2].x, &faceIndices[2].y, &faceIndices[2].z);
			//VertexModel tempModelData = {vertices[faceIndices[0].x - 1], UV[faceIndices[0].x], normals[faceIndices[0].z]};
			for (int i = 0; i < 3; i++)
				vertexData.push_back({ vertices[faceIndices[i].x - 1], UV[faceIndices[i].x - 1], normals[faceIndices[i].z - 1] });
		}
	}

	fileIn.close();
	return true;
}
