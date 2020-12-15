#include "PlayerController.h"

#include "InputManager.h"
#include "GameLogic.h"
#include "Object.h"

#include "../glm/glm.hpp"


PlayerController::PlayerController() : NonRenderableObject("Player Controller")
{
	_characterObject = nullptr;

	_moveSpeed = 2.0f;
}


void PlayerController::Update()
{
	Move();
}


void PlayerController::SetPlayableCharacter(Object* character_obj)
{
	_characterObject = character_obj;
}

void PlayerController::SetSpeed(float new_speed)
{
	_moveSpeed = new_speed * ((new_speed > 0) - (new_speed < 0));
}

void PlayerController::Move()
{
	switch (InputManager::GetInstance().GetKeyDown())
	{
	case Movement::LEFT:
		if (_characterObject->GetObjectLocation().x >= 0)
		{
			glm::vec3 pos = _characterObject->GetObjectLocation();
			pos.x -= _moveSpeed;

			_characterObject->SetObjectLocation(pos.x, pos.y, pos.z);
		}
		break;

	case Movement::RIGHT:
		if (_characterObject->GetObjectLocation().x <= 0)
		{
			glm::vec3 pos = _characterObject->GetObjectLocation();
			pos.x += _moveSpeed;

			_characterObject->SetObjectLocation(pos.x, pos.y, pos.z);
		}
		break;
	}
}