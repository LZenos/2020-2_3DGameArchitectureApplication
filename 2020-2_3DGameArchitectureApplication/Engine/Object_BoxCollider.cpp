#include "Object_BoxCollider.h"
#include "GameLogic.h"


BoxCollider::BoxCollider(std::string obj_name) : NonRenderableObject(obj_name)
{
	_boxExtent = glm::vec3(1.0f, 1.0f, 1.0f);

	GameLogic::GetInstance().AddCollider(this);
}


void BoxCollider::SetBoxExtent(glm::vec3 box_extent)
{
	_boxExtent = box_extent;
}
void BoxCollider::SetBoxExtent(float x, float y, float z)
{
	_boxExtent = glm::vec3(x, y, z);
}

glm::vec3 BoxCollider::GetBoxExtent() const
{
	return _boxExtent;
}


void BoxCollider::ReportCollision(BoxCollider* other)
{
	Object* this_generation = this;
	Object* generation = this_generation->GetParent();
	while (generation->IsChild())
	{
		this_generation = this_generation->GetParent();
		generation = generation->GetParent();
	}
	this_generation->OnCollision(other);
}