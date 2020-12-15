#pragma once

#include "NonRenderableObject.h"


class BoxCollider : public NonRenderableObject
{
private:
	glm::vec3 _boxExtent;

public:
	BoxCollider(std::string obj_name);


	void SetBoxExtent(glm::vec3 box_extent);
	void SetBoxExtent(float x, float y, float z);

	glm::vec3 GetBoxExtent() const;


	void ReportCollision(BoxCollider* other);
};