#include "Object_Sphere.h"

#include "FileManager.h"


bool Sphere::Initialize(const char* dds_file_path)
{
	// obj 파일 로드
	bool res = FileManager::GetInstance().LoadObjAdvanced("sphere.obj", _vertexes, _uvs, _normals);

	if (!res)
	{
		printf("Loading obj file has failed. Upgrade parser or change your model less complicated.\n");
		return res;
	}


	// dds 파일 로드
	if (dds_file_path == "Default")
	{
		_texture = FileManager::GetInstance().LoadDDS("earth.dds");
	}
	else
	{
		_texture = FileManager::GetInstance().LoadDDS(dds_file_path);
	}


	// obj 정점 정보 바인드
	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, _vertexes.size() * sizeof(glm::vec3), &_vertexes[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, _uvs.size() * sizeof(glm::vec2), &_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &_normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(glm::vec3), &_normals[0], GL_STATIC_DRAW);
}