#pragma once

#include <vector>

#include "include/GL/glew.h"
#include "glm/glm.hpp"


class FileManager
{
private:
	FileManager() {}

public:
	~FileManager() {}

	static FileManager& GetInstance();
	
	bool LoadObjSimple(
		const char* path,
		std::vector<glm::vec3>& out_vertexes,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals);

	void LoadObj(
		const char* path,
		std::vector<glm::vec3>& out_vertexes,
		std::vector<glm::vec2>& out_uvs,
		std::vector<glm::vec3>& out_normals);

	GLuint LoadDDS(const char* path);

	GLuint LoadShader(const char* vs_path, const char* fs_path);
};