#include "Object.h"

#include "FileManager.h"


Object::Object(std::string object_name)
{
	_objName = object_name;
	
	_worldPosition = glm::vec3(0, 0, 0);
	_worldRotationDegree = 0.0f;
	_worldRotationAxis = glm::vec3(0, 1, 0);
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);

	_parent = nullptr;
}

Object::~Object()
{
	
}


std::string Object::GetName() const
{
	return _objName;
}


void Object::SetObjectLocation(float x, float y, float z)
{
	_worldPosition = glm::vec3(x, y, z);
}
void Object::SetObjectLocation(glm::vec3 world_pos)
{
	_worldPosition = world_pos;
}

glm::vec3 Object::GetObjectLocation() const
{
	return _worldPosition;
}


void Object::SetObjectRotation(float degree, float x, float y, float z)
{
	_worldRotationDegree = degree;
	_worldRotationAxis = glm::vec3(x, y, z);
}

float Object::GetObjectRotationDegree() const
{
	return _worldRotationDegree;
}
glm::vec3 Object::GetObjectRotationAxis() const
{
	return _worldRotationAxis;
}


void Object::SetObjectScale(float x, float y, float z)
{
	_scale = glm::vec3(x, y, z);
}

glm::vec3 Object::GetObjectScale() const
{
	return _scale;
}


void Object::AttachTo(Object* parent)
{
	_parent = parent;

	_worldPosition = _worldPosition - _parent->GetObjectLocation();
}

Object* Object::GetParent() const
{
	return _parent;
}