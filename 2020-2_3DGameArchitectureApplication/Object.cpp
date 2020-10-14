#include "Object.h"

#include "FileManager.h"


Object::Object(std::string object_name)
{
	_objName = object_name;
	
	_worldPosition = glm::vec3(0, 0, 0);
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
glm::vec3 Object::GetObjectLocation() const
{
	return _worldPosition;
}