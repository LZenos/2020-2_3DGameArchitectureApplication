#pragma once

#include "Object.h"


class CompositeObject : public Object
{
private:
	std::vector<Object*>* _components;

public:
	CompositeObject(std::string obj_name);


	virtual void Init() override;

	virtual void Update() override;

	virtual void Render() override = 0;

	virtual void OnCollision(BoxCollider* other) override;

	virtual void ReleaseMemory() override;


	void AttachComponent(Object* new_component);

	template <typename T> T* GetComponent();

	virtual void SearchRenderableObjFromSceneGraph() override;
};