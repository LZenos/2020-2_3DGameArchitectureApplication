#include "CompositeObject.h"
#include "Renderer.h"
#include "RenderableObject.h"

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"


CompositeObject::CompositeObject(std::string obj_name) : Object(obj_name)
{
	_components = new std::vector<Object*>();
}

void CompositeObject::Init()
{
	Object::Init();
	
	for (size_t i = 0; i < _components->size(); i++)
	{
		(*_components)[i]->Init();
	}
}

void CompositeObject::Update()
{
	for (size_t i = 0; i < _components->size(); i++)
	{
		(*_components)[i]->Update();
	}
}

void CompositeObject::OnCollision(BoxCollider* other)
{
	for (size_t i = 0; i < _components->size(); i++)
	{
		(*_components)[i]->OnCollision(other);
	}
}

void CompositeObject::ReleaseMemory()
{
	for (size_t i = 0; i < _components->size(); i++)
	{
		_components->at(i)->ReleaseMemory();
	}
	delete _components;
}


void CompositeObject::AttachComponent(Object* new_component)
{
	_components->push_back(new_component);
	new_component->SetParent(this);
}

template <typename T>
T* CompositeObject::GetComponent()
{
	T* obj_cast = nullptr;

	for (size_t i = 0; i < _components->size(); i++)
	{
		obj_cast = (*_components)[i]->Cast<T>();

		if (obj_cast != nullptr)
		{
			break;
		}
	}

	return obj_cast;
}

void CompositeObject::SearchRenderableObjFromSceneGraph()
{
	RenderableObject* temp = nullptr;
	temp = dynamic_cast<RenderableObject*>(this);
	if (temp != nullptr)
	{
		Renderer::GetInstance().AddObject(temp);
	}
	
	for (size_t i = 0; i < _components->size(); i++)
	{
		(*_components)[i]->SearchRenderableObjFromSceneGraph();
	}
}