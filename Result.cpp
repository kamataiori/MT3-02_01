#include "Result.h"

Result::Result()
{
}

void Result::Initialize()
{
	cameraTranslate = { 0.0f,1.9f,-6.49f };
	cameraRotate = { 0.26f,0.0f,0.0f };
	rotate = {};
	translate = {};
	worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
	cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
	viewMatrix = Inverse(cameraMatrix);
	projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	worldviewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
	sphere.center.x = 0;
	sphere.center.y = 0;
	sphere.center.z = 0;
	sphere.radius = 0.5f;
	sphere2.center.x = 0;
	sphere2.center.y = 0;
	sphere2.center.z = 0;
	sphere2.radius = 0.8f;
	distance = isColliding(sphere, sphere2);
	/*if (distance <= sphere.radius + sphere2.radius)
	{

	}*/

}

void Result::Updata()
{

}

void Result::Draw()
{

	DrawGrid(worldviewProjectionMatrix, viewportMatrix);
	DrawSphere(sphere, worldviewProjectionMatrix, viewportMatrix, 0xAAAAAAFF);
	if (distance >= sphere.radius + sphere2.radius)
	{
		DrawSphere(sphere2, worldviewProjectionMatrix, viewportMatrix, 0xAAAAAAFF);
	}
	else if (distance <= sphere.radius + sphere2.radius)
	{
		DrawSphere(sphere2, worldviewProjectionMatrix, viewportMatrix, 0xAA0000FF);
	}

	/*if (distance)
	{
		DrawSphere(sphere2, worldviewProjectionMatrix, viewportMatrix, 0xAA0000FF);
	}
	else if (!distance)
	{
		DrawSphere(sphere2, worldviewProjectionMatrix, viewportMatrix, 0xAAAAAAFF);
	}*/

	//ImGui
	ImGui::Begin("Window");
	ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
	ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
	ImGui::DragFloat3("SphereTranslate", &sphere.center.x, 0.01f);
	ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);

	ImGui::DragFloat3("Sphere2Translate", &sphere2.center.x, 0.01f);
	ImGui::DragFloat("Sphere2Radius", &sphere2.radius, 0.01f);
	ImGui::End();

	/*ImGui::Begin("Window");
	ImGui::DragFloat("SphereRadius", &sphere.radius, 0.01f);
	ImGui::End();*/
}
