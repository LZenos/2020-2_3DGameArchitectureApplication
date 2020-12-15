#include "Object.h"
#include "GameLogic.h"
#include "Object_Root.h"


Object::Object(std::string object_name)
{
	_objName = object_name;

	_position = glm::vec3(0, 0, 0);
	_rotationDegree = 0.0f;
	_rotationAxis = glm::vec3(0, 1, 0);
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);

	_parent = nullptr;
}


void Object::Init()
{
	if (IsChild())
	{
		SetObjectLocation(GetObjectLocation() - _parent->GetObjectLocation());
		SetObjectRotation(
			GetObjectRotationDegree() - _parent->GetObjectRotationDegree(),
			GetObjectRotationAxis().x,
			GetObjectRotationAxis().y,
			GetObjectRotationAxis().z);
		SetObjectScale(
			GetObjectScale().x / _parent->GetObjectScale().x,
			GetObjectScale().y / _parent->GetObjectScale().y,
			GetObjectScale().z / _parent->GetObjectScale().z);
	}
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

glm::vec3 Object::GetObjectWorldLocation()
{
	glm::vec4 world_pos = glm::vec4(GetObjectLocation(), 1.0f);
	Object* generation = this;

	while (generation->IsChild())
	{
		generation = generation->GetParent();
		glm::mat4 pPos = glm::translate(glm::mat4(1.0f), generation->GetObjectLocation());
		glm::mat4 pRot = glm::rotate(glm::mat4(1.0f), glm::radians(generation->GetObjectRotationDegree()), generation->GetObjectRotationAxis());
		world_pos = pPos * pRot * world_pos;
	}

	return world_pos;
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


void Object::SetParent(Object* parent)
{
	_parent = parent;
}

Object* Object::GetParent() const
{
	return _parent;
}

bool Object::IsChild() const
{
	return (_parent != nullptr);
}


template <typename T>
T* Object::Cast(Object* obj_to_cast)
{
	T* casted = nullptr;

	try
	{
		casted = dynamic_cast<T*>(obj_to_cast);

		if (casted == nullptr)
		{
			throw casted;
		}
	}
	catch (T* cast_failed)
	{
		//cout << "Cast has failed." << endl;
	}

	return casted;
}
template <typename T>
bool Object::CheckType(Object* obj)
{
	T* type = nullptr;

	type = Cast<T>(obj);

	if (type != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}