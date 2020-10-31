#include "FileManager.h"
#include "Time.h"
#include "Renderer.h"
#include "GameLogic.h"
#include "PlayerController.h"
#include "Object_Camera.h"
#include "Object_Light.h"
#include "Object_Mesh.h"
#include "Object_Sphere.h"

#include <vector>


int main(void)
{
	// 상수
	const int tree_num = 48;
	const int buiding_num = 24;
	
	
	// 파일 매니저 객체 생성
	FileManager::GetInstance();

	// 렌더러 객체 생성 및 초기화
	Renderer::GetInstance().InitWindowSettings("Graphic Engine");
	Renderer::GetInstance().InitRenderSettings("vs.shader", "fs.shader");

	
	// 오브젝트 객체 생성
	Camera* main_camera = new Camera();
	Light* point_light = new Light();
	Sphere* ground = new Sphere("Ground");
	Mesh* car = new Mesh("Car");
	std::vector<Mesh*> trees;
	for (int i = 0; i < tree_num; i++)
	{
		trees.push_back(new Mesh("Tree"));
	}
	std::vector<Mesh*> buildings;
	for (int i = 0; i < buiding_num; i++)
	{
		buildings.push_back(new Mesh("Building"));
	}

	// 플레이어 컨트롤러 객체 생성
	PlayerController* player = new PlayerController(car);

	// 오브젝트 설정
	main_camera->Initialize(glm::vec3(0.0f, 115.0f, 21.0f), glm::vec3(0.0f, 100.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	ground->Initialize("Models/huge sphere.obj", "Textures/moon.dds");
	car->Initialize("Models/car.obj", "Textures/car.dds", true);
	for (int i = 0; i < tree_num; i++)
	{
		trees[i]->Initialize("Models/tree.obj", "Textures/tree.dds", true);

		glm::vec2 pos;
		switch (i % 12)
		{
		case 0:
			pos = glm::vec2(99.2f, 0.0f);
			break;
		case 1:
			pos = glm::vec2(95.9f, 25.6f);
			break;
		case 2:
			pos = glm::vec2(85.9f, 49.5f);
			break;
		case 3:
			pos = glm::vec2(70.1f, 70.1f);
			break;
		case 4:
			pos = glm::vec2(49.5f, 85.9f);
			break;
		case 5:
			pos = glm::vec2(25.6f, 95.9f);
			break;
		case 6:
			pos = glm::vec2(0.0f, 99.2f);
			break;
		case 7:
			pos = glm::vec2(-25.6f, 95.9f);
			break;
		case 8:
			pos = glm::vec2(-49.5f, 85.9f);
			break;
		case 9:
			pos = glm::vec2(-70.1f, 70.1f);
			break;
		case 10:
			pos = glm::vec2(-85.9f, 49.5f);
			break;
		case 11:
			pos = glm::vec2(-95.9f, 25.6f);
			break;
		}
		if (i < 24)
		{
			if (i >= 12)
			{
				pos *= -1.0f;
			}
			trees[i]->SetObjectLocation(-5.0f, pos.x, pos.y);
		}
		else
		{
			if (i >= 36)
			{
				pos *= -1.0f;
			}
			trees[i]->SetObjectLocation(5.0f, pos.x, pos.y);
		}
		trees[i]->SetObjectRotation(15.0f * i, 1.0f, 0.0f, 0.0f);

		trees[i]->AttachTo(ground);

		Renderer::GetInstance().AddObject(trees[i]);
	}
	for (int i = 0; i < buiding_num; i++)
	{
		buildings[i]->Initialize("Models/building.obj", "Textures/building.dds", true);

		glm::vec2 pos;
		switch (i % 6)
		{
		case 0:
			pos = glm::vec2(98.0f, 0.0f);
			break;
		case 1:
			pos = glm::vec2(84.9f, 49.0f);
			break;
		case 2:
			pos = glm::vec2(49.0f, 84.9f);
			break;
		case 3:
			pos = glm::vec2(0.0f, 98.0f);
			break;
		case 4:
			pos = glm::vec2(-49.0f, 84.9f);
			break;
		case 5:
			pos = glm::vec2(-84.9f, 49.0f);
			break;
		}
		if (i < 12)
		{
			if (i >= 6)
			{
				pos *= -1.0f;
			}
			buildings[i]->SetObjectLocation(-13.0f, pos.x, pos.y);
		}
		else
		{
			if (i >= 18)
			{
				pos *= -1.0f;
			}
			buildings[i]->SetObjectLocation(13.0f, pos.x, pos.y);
		}
		buildings[i]->SetObjectRotation(30.0f * i, 1.0f, 0.0f, 0.0f);
		buildings[i]->SetObjectScale(0.5f, 0.5f, 0.5f);

		buildings[i]->AttachTo(ground);

		Renderer::GetInstance().AddObject(buildings[i]);
	}
	
	point_light->SetObjectLocation(0.0f, 100.3f, -4.0f);
	ground->SetObjectLocation(0.0f, 0.0f, 0.0f);
	car->SetObjectLocation(0.0f, 100.3f, 0.0f);

	point_light->AttachTo(car);


	// 렌더링 할 객체 추가
	Renderer::GetInstance().AddObject(ground);
	Renderer::GetInstance().AddObject(car);
	
	// 카메라 설정
	Renderer::GetInstance().AddCamera(main_camera);

	// 빛 추가
	Renderer::GetInstance().AddLight(point_light);

	// 업데이트 할 객체 추가
	GameLogic::GetInstance().AddUpdatableObj(ground);

	
	// 루프
	do
	{
		Time::GetInstance().Tick();
		
		player->Move();
		
		Renderer::GetInstance().Draw();
		GameLogic::GetInstance().Update();
	}
	while (Renderer::GetInstance().IsWindowClose());


	// 메모리 해제
	main_camera->ReleaseMemory();
	point_light->ReleaseMemory();
	ground->ReleaseMemory();
	car->ReleaseMemory();
	for (int i = 0; i < trees.size(); i++)
	{
		trees[i]->ReleaseMemory();
	}
	for (int i = 0; i < buildings.size(); i++)
	{
		buildings[i]->ReleaseMemory();
	}
	Renderer::GetInstance().ReleaseMemory();
	GameLogic::GetInstance().ReleaseMemory();
	
	return 0;
}