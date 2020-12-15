#include "PlayerObject.h"
#include "Engine/Object_BoxCollider.h"

#include <iostream>


PlayerObject::PlayerObject() : RenderableObject("Player Character")
{
	_score = 100;
}


void PlayerObject::OnCollision(BoxCollider* collider)
{
	_score--;
	glm::vec3 world_pos = collider->GetObjectWorldLocation();
	std::cout << "Score Decreased: " << _score << std::endl;
}