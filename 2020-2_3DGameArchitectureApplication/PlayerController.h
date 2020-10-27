#pragma once


class Object;


class PlayerController
{
private:
	Object* _characterObject;

	float _moveSpeed;

public:
	PlayerController(Object* playable_character);
	~PlayerController();

	void SetSpeed(float new_speed);

	void Move();
};