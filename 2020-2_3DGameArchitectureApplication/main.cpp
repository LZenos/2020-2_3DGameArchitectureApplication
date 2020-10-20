#include "FileManager.h"
#include "Renderer.h"
#include "Object_Camera.h"
#include "Object_Mesh.h"
#include "Object_Sphere.h"


int main(void)
{
	// 파일 매니저 객체 생성
	FileManager::GetInstance();


	// 렌더러 객체 생성 및 초기화
	Renderer::GetInstance();

	Renderer::GetInstance().InitWindowSettings("Graphic Engine");
	Renderer::GetInstance().InitRenderSettings("vs.shader", "fs.shader");
	Renderer::GetInstance().InitLightPosition(0.0f, 3.0f, 1.5f);

	
	// 오브젝트 객체 생성 및 설정
	Camera* main_camera = new Camera();
	Mesh* cube_1 = new Mesh("Left Cube");
	Mesh* cube_2 = new Mesh("Right Cube");
	Sphere* sphere_1 = new Sphere();
	Sphere* sphere_2 = new Sphere("Moon");

	cube_1->Initialize("cube.obj", "moon.dds");
	cube_2->Initialize("cube.obj", "cube.DDS", true);
	sphere_1->Initialize();
	sphere_2->Initialize("moon.dds");

	main_camera->SetObjectLocation(5.0f, 5.0f, 11.0f);
	cube_1->SetObjectLocation(-3.0f, 0.0f, 0.0f);
	cube_2->SetObjectLocation(3.0f, 0.0f, 0.0f);
	sphere_1->SetObjectLocation(0.0f, 0.0f, 0.0f);
	sphere_2->SetObjectLocation(-1.5f, 3.0f, -4.0f);


	// 렌더링 할 객체 추가
	Renderer::GetInstance().AddObject(cube_1);
	Renderer::GetInstance().AddObject(cube_2);
	Renderer::GetInstance().AddObject(sphere_1);
	Renderer::GetInstance().AddObject(sphere_2);
	
	// 카메라 설정
	Renderer::GetInstance().AddCamera(main_camera);

	// 업데이트 할 객체 추가 (임시 구현. 렌더러에서 할 일은 아닌 것 같다...)
	Renderer::GetInstance().AddUpdatableObj(main_camera);
	Renderer::GetInstance().AddUpdatableObj(cube_1);
	Renderer::GetInstance().AddUpdatableObj(cube_2);
	Renderer::GetInstance().AddUpdatableObj(sphere_1);
	Renderer::GetInstance().AddUpdatableObj(sphere_2);

	
	// 그리기
	do
	{
		Renderer::GetInstance().Draw();
		
		Renderer::GetInstance().Update();
	}
	while (Renderer::GetInstance().IsWindowClose());


	// 메모리 해제
	main_camera->ReleaseMemory();
	cube_1->ReleaseMemory();
	cube_2->ReleaseMemory();
	sphere_1->ReleaseMemory();
	sphere_2->ReleaseMemory();
	Renderer::GetInstance().ReleaseMemory();
	
	return 0;
}