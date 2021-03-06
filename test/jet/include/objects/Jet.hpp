#pragma once

#include <GFK/Math/Vector3.hpp>
#include <GFK/Math/Quaternion.hpp>
#include <GFK/Math/Matrix.hpp>
#include <GFK/System/GameTime.hpp>

using namespace gfk;

namespace jetGame
{

class Jet
{
public:
	Jet();
	Jet(const Vector3 &pos, const Vector3 &initialForward, const Vector3 &initialUp);
	~Jet();

	void Reset();
	void Update(float throttleAmt, float rollInput, float pitchInput, float yawInput, bool thrusterEnabled, const GameTime &gameTime);
	Vector3 GetPosition() const;
	void SetPosition(const Vector3 &pos);
	Quaternion GetRotation() const;
	void SetRotation(const Quaternion &rot);
	Vector3 GetUp();
	Vector3 GetForward();
	Vector3 GetRight();
	Matrix GetTransform();
protected:
private:
	static const float IDLE_RPM;

	int health;
	Vector3 position;
	float throttle;
	float engineRPM;

	Vector3 initialUp;
	Vector3 initialRight;

	Vector3 forward;
	Vector3 up;
	Vector3 right;

	Quaternion rotQuat;

	void ReOrient();
};

}
