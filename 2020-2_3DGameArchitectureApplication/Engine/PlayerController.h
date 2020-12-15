#pragma once

#include "NonRenderableObject.h"


class Object;


class PlayerController : public NonRenderableObject
{
private:
	Object* _characterObject;

	float _moveSpeed;

public:
	PlayerController();


	virtual void Update() override;


	void SetPlayableCharacter(Object* character_obj);

	void SetSpeed(float new_speed);

	void Move();
};