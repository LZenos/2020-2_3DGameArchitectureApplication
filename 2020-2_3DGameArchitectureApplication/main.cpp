#include "Engine/Time.h"
#include "Engine/Renderer.h"
#include "Engine/GameLogic.h"
#include "Engine/PlayerController.h"
#include "Engine/Object_Root.h"
#include "Engine/Object_Camera.h"
#include "Engine/Object_Light.h"
#include "Engine/Object_BoxCollider.h"
#include "Engine/Object_Mesh.h"
#include "SpinningSphere.h"
#include "PlayerObject.h"

#include <vector>


int main(void)
{
	// 상수
	const int tree_num = 24;
	const int buiding_num = 12;
	
	
	// 렌더러 객체 초기화
	Renderer::GetInstance().InitWindowSettings("Graphic Engine");
	Renderer::GetInstance().InitRenderSettings();

	
	// 루트 씬 객체 생성. 모든 객체가 여기에 컴포넌트식으로 붙게 되며, 관리와 삭제가 계층식으로 이루어집니다.
	RootScene* root_scene = new RootScene("Root Scene");

	// 오브젝트(컴포넌트) 객체 생성
	Camera* main_camera = new Camera();

	PlayerController* playerControl = new PlayerController();
	PlayerObject* playerCharacter = new PlayerObject();
	BoxCollider* playerCollider = new BoxCollider("Player Collider");
	Light* point_light = new Light();

	SpinningSphere* ground = new SpinningSphere("Ground");
	std::vector<Mesh*> trees;
	for (int i = 0; i < tree_num; i++)
	{
		trees.push_back(new Mesh("Tree"));
	}
	std::vector<BoxCollider*> treeColliders;
	for (int i = 0; i < tree_num; i++)
	{
		treeColliders.push_back(new BoxCollider("Tree Collider"));
	}
	std::vector<Mesh*> buildings;
	for (int i = 0; i < buiding_num; i++)
	{
		buildings.push_back(new Mesh("Building"));
	}
	float tree_positioning[tree_num] = {
		-2, -2, -2,  0, -2, -2,  0,  0,  0, -2, -2, -2,
		 2,  2,  2,  2,  2,  0,  0,  2,  2,  2,  0,  0
	};

	// 오브젝트 설정
	main_camera->Initialize(glm::vec3(0.0f, 115.0f, 21.0f), glm::vec3(0.0f, 100.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	playerCharacter->Initialize("Models/car.obj", "Textures/car.dds");
	playerCharacter->SetObjectLocation(0.0f, 100.3f, 0.0f);
	playerCollider->SetObjectLocation(0.0f, 100.3f, 0.0f);
	playerCollider->SetBoxExtent(1.0f, 1.0f, 2.0f);
	point_light->SetObjectLocation(0.0f, 100.3f, -4.0f);
	playerControl->SetPlayableCharacter(playerCharacter);

	root_scene->AttachComponent(main_camera);
	root_scene->AttachComponent(playerControl);
	root_scene->AttachComponent(playerCharacter);
	playerCharacter->AttachComponent(playerCollider);
	playerCharacter->AttachComponent(point_light);

	ground->Initialize("Models/huge sphere.obj", "Textures/moon.dds");
	root_scene->AttachComponent(ground);
	for (int i = 0; i < tree_num; i++)
	{
		trees[i]->Initialize("Models/tree.obj", "Textures/tree.dds");
		treeColliders[i]->SetBoxExtent(0.5f, 0.5f, 0.5f);

		glm::vec2 pos;
		switch (i % 6)
		{
		case 0:
			pos = glm::vec2(99.2f, 0.0f);
			break;
		case 1:
			pos = glm::vec2(85.9f, 49.5f);
			break;
		case 2:
			pos = glm::vec2(49.5f, 85.9f);
			break;
		case 3:
			pos = glm::vec2(0.0f, 99.2f);
			break;
		case 4:
			pos = glm::vec2(-49.5f, 85.9f);
			break;
		case 5:
			pos = glm::vec2(-85.9f, 49.5f);
			break;
		}
		if (i < 12)
		{
			if (i >= 6)
			{
				pos *= -1.0f;
			}
			trees[i]->SetObjectLocation(tree_positioning[i], pos.x, pos.y);
		}
		else
		{
			if (i >= 18)
			{
				pos *= -1.0f;
			}
			trees[i]->SetObjectLocation(tree_positioning[i], pos.x, pos.y);
		}
		trees[i]->SetObjectRotation(30.0f * i, 1.0f, 0.0f, 0.0f);

		treeColliders[i]->SetObjectLocation(trees[i]->GetObjectLocation());

		ground->AttachComponent(trees[i]);
		trees[i]->AttachComponent(treeColliders[i]);
	}
	for (int i = 0; i < buiding_num; i++)
	{
		buildings[i]->Initialize("Models/building.obj", "Textures/building.dds");

		glm::vec2 pos;
		switch (i % 3)
		{
		case 0:
			pos = glm::vec2(98.0f, 0.0f);
			break;
		case 1:
			pos = glm::vec2(49.0f, 84.9f);
			break;
		case 2:
			pos = glm::vec2(-49.0f, 84.9f);
			break;
		}
		if (i < 6)
		{
			if (i >= 3)
			{
				pos *= -1.0f;
			}
			buildings[i]->SetObjectLocation(-13.0f, pos.x, pos.y);
		}
		else
		{
			if (i >= 9)
			{
				pos *= -1.0f;
			}
			buildings[i]->SetObjectLocation(13.0f, pos.x, pos.y);
		}
		buildings[i]->SetObjectRotation(60.0f * i, 1.0f, 0.0f, 0.0f);
		buildings[i]->SetObjectScale(0.5f, 0.5f, 0.5f);

		ground->AttachComponent(buildings[i]);
	}

	
	// Init 호출
	GameLogic::GetInstance().InitScene();
	
	// 루프
	do
	{
		Time::GetInstance().Tick();
		
		Renderer::GetInstance().Render();
		GameLogic::GetInstance().UpdateScene();
	}
	while (Renderer::GetInstance().IsWindowClose());


	// 메모리 해제
	root_scene->ReleaseMemory();
	Renderer::GetInstance().ReleaseMemory();
	GameLogic::GetInstance().ReleaseMemory();
	trees.clear();
	buildings.clear();
	
	return 0;
}