#pragma once

#include "Object.h"


class RenderableObject : public Object
{
protected:
	std::vector<glm::vec3> _vertexes;
	std::vector<glm::vec2> _uvs;
	std::vector<glm::vec3> _normals;
	GLuint _texture;

	GLuint _vertexBuffer;
	GLuint _uvBuffer;
	GLuint _normalBuffer;

public:
	RenderableObject(std::string object_name);
	~RenderableObject();

	GLuint GetTexture() const;

	GLuint GetVertexBuffer() const;
	GLuint GetUVBuffer() const;
	GLuint GetNormalBuffer() const;

	size_t GetVertexSize() const;

	virtual void ReleaseMemory() override;
};