#include "Object.h"

#include "GameLogic.h"


Object::Object(std::string object_name)
{
	_objName = object_name;
	
	_position = glm::vec3(0, 0, 0);
	_rotationDegree = 0.0f;
	_rotationAxis = glm::vec3(0, 1, 0);
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);

	_parent = nullptr;

	GameLogic::GetInstance().AddUpdatableObj(this);
}


std::string Object::GetName() const
{
	return _objName;
}


void Object::SetObjectLocation(float x, float y, float z)
{
	_position = glm::vec3(x, y, z);
}
void Object::SetObjectLocation(glm::vec3 local_pos)
{
	_position = local_pos;
}

glm::vec3 Object::GetObjectLocation() const
{
	return _position;
}


void Object::SetObjectRotation(float degree, float x, float y, float z)
{
	_rotationDegree = degree;
	_rotationAxis = glm::vec3(x, y, z);
}

float Object::GetObjectRotationDegree() const
{
	return _rotationDegree;
}
glm::vec3 Object::GetObjectRotationAxis() const
{
	return _rotationAxis;
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

	_position -= _parent->GetObjectLocation();
	_rotationDegree -= _parent->GetObjectRotationDegree();
	_scale = glm::vec3(
		_scale.x / _parent->GetObjectScale().x,
		_scale.y / _parent->GetObjectScale().y,
		_scale.z / _parent->GetObjectScale().z);
}

bool Object::IsChild() const
{
	return (_parent != nullptr);
}

Object* Object::GetParent() const
{
	return _parent;
}