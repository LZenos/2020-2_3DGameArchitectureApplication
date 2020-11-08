#pragma once

#include "Object.h"

#include "glm/glm.hpp";
#include "glm/gtc/matrix_transform.hpp"


class RenderableObject : public Object
{
private:
	GLuint _vertexArrayID;
	GLuint _programID;
	GLuint _matrixID;
	GLuint _viewMatrixID;
	GLuint _modelMatrixID;
	GLuint _textureID;
	GLuint _lightID;

	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
	glm::mat4 _modelMatrix;
	glm::mat4 _MVP;

	std::vector<glm::vec3> _vertexes;
	std::vector<glm::vec2> _uvs;
	std::vector<glm::vec3> _normals;

	GLuint _texture;

	GLuint _vertexBuffer;
	GLuint _uvBuffer;
	GLuint _normalBuffer;

public:
	RenderableObject(std::string object_name);

	virtual void Initialize(const char* obj_file_path, const char* dds_file_path, const char* vs_path = "vs.shader", const char* fs_path = "fs.shader");


	virtual void Init() override;

	virtual void Update() override;

	virtual void Render() override;


	void UniformShaderRelativeLightPos(glm::vec3 light_worldPos);	

	void SetMVP(glm::mat4 model, glm::mat4 view, glm::mat4 projection);


	GLuint GetTexture() const;

	GLuint GetVertexBuffer() const;
	GLuint GetUVBuffer() const;
	GLuint GetNormalBuffer() const;

	size_t GetVertexSize() const;

	virtual void ReleaseMemory() override;
};