#include "PlayerController.h"

#include "InputManager.h"
#include "GameLogic.h"
#include "Object.h"

#include "glm/glm.hpp"


PlayerController::PlayerController(Object* playerable_character)
{
	_characterObject = playerable_character;

	_moveSpeed = 2.0f;

	GameLogic::GetInstance().AddUpdatableObj(this);
}

PlayerController::~PlayerController()
{
	
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

void PlayerController::Init()
{

}

void PlayerController::Update()
{
	Move();
}


void PlayerController::ReleaseMemory()
{
	delete this;
}