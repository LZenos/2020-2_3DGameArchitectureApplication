#pragma once

#include "ICleanup.h"
#include "IUpdatable.h"


class Object;


class PlayerController : public IUpdatable, public ICleanUp
{
private:
	Object* _characterObject;

	float _moveSpeed;

public:
	PlayerController(Object* playable_character);
	~PlayerController();

	void SetSpeed(float new_speed);

	void Move();

	virtual void Init() override;
	
	virtual void Update() override;

	virtual void ReleaseMemory() override;
};