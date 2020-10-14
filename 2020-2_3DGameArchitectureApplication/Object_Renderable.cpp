#include "Object_Renderable.h"

#include "FileManager.h"


RenderableObject::RenderableObject(std::string object_name) : Object(object_name)
{
	_vertexes.clear();
	_uvs.clear();
	_normals.clear();
}

RenderableObject::~RenderableObject()
{

}


GLuint RenderableObject::GetTexture() const
{
	return _texture;
}

GLuint RenderableObject::GetVertexBuffer() const
{
	return _vertexBuffer;
}
GLuint RenderableObject::GetUVBuffer() const
{
	return _uvBuffer;
}
GLuint RenderableObject::GetNormalBuffer() const
{
	return _normalBuffer;
}

size_t RenderableObject::GetVertexSize() const
{
	return _vertexes.size();
}

void RenderableObject::ReleaseMemory()
{
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_uvBuffer);
	glDeleteBuffers(1, &_normalBuffer);
	glDeleteTextures(1, &_texture);

	_vertexes.clear();
	_uvs.clear();
	_normals.clear();

	delete this;
}