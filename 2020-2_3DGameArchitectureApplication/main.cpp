#include "FileManager.h"
#include "Renderer.h"
#include "Object_Camera.h"
#include "Object_Mesh.h"
#include "Object_Sphere.h"


int main(void)
{
	// ���� �Ŵ��� ��ü ����
	FileManager::GetInstance();


	// ������ ��ü ���� �� �ʱ�ȭ
	Renderer* renderer = new Renderer();

	renderer->InitWindowSettings("Graphic Engine");
	renderer->InitRenderSettings("vs.shader", "fs.shader");
	renderer->InitLightPosition(0.0f, 3.0f, 1.5f);

	
	// ������Ʈ ��ü ���� �� ����
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


	// ī�޶� ����
	renderer->BindCamera(main_camera);

	
	// �׸���
	do
	{
		renderer->ClearScreen();

		renderer->Draw(cube_1);
		renderer->Draw(cube_2);
		renderer->Draw(sphere_1);
		renderer->Draw(sphere_2);

		renderer->EndDraw();
	}
	while (renderer->IsWindowClose());


	// �޸� ����
	main_camera->ReleaseMemory();
	cube_1->ReleaseMemory();
	cube_2->ReleaseMemory();
	sphere_1->ReleaseMemory();
	sphere_2->ReleaseMemory();
	renderer->ReleaseMemory();
	
	return 0;
}