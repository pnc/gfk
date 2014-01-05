#include <GFK/Graphics/Camera.hpp>
#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <GFK/Input/Keyboard.hpp>
#include <iostream>
#include <cmath>

namespace gfk
{

Matrix Camera::GetView()
{
	Matrix::CreateLookAt(pos, Vector3(0, 0, 0), Vector3::Up, view);
	return view;
}

Matrix Camera::GetProjection()
{
	Matrix::CreatePerspectiveFieldOfView(MathHelper::Pi * 0.25f, 1280.0f / 720.0f, 0.1f, 1000.0f, projection);
	return projection;
}

void Camera::Update(float dt)
{
	totalTime += dt;

	pos.Z = 4;

	if (Keyboard::IsKeyDown(Keys::Left))
	{
		pos.X -= 50 * dt;
	}

	if (Keyboard::IsKeyDown(Keys::Right))
	{
		pos.X += 50 * dt;
	}

	if (Keyboard::IsKeyDown(Keys::Up))
	{
		pos.Y += 10 * dt;
	}

	if (Keyboard::IsKeyDown(Keys::Down))
	{
		pos.Y -= 10 * dt;
	}

	// pos.X = (float)cos(totalTime) * 5;
	// pos.Y = 2;
	// pos.Z = (float)sin(totalTime) * 5;
}

}