#pragma once

namespace gfk
{

class Vector3;
class Matrix;

class Quaternion
{
public:
	float X, Y, Z, W;
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(Vector3 vector, float w);
	~Quaternion();

	static const Quaternion Identity;

	static void Add(const Quaternion &q1, const Quaternion &q2, Quaternion &result);
	static Quaternion Concatenate(const Quaternion &q1, const Quaternion &q2);
	static void Concatenate(const Quaternion &q1, const Quaternion &q2, Quaternion &result);
	static Quaternion Conjugate(const Quaternion &value);
	static void Conjugate(const Quaternion &value, Quaternion &result);
	static Quaternion CreateFromAxisAngle(const Vector3 &axis, float angle);
	static void CreateFromAxisAngle(const Vector3 &axis, float angle, Quaternion &result);
	static Quaternion CreateFromRotationMatrix(const Matrix &matrix);
	static void CreateFromRotationMatrix(const Matrix &matrix, Quaternion &result);
	static Quaternion CreateFromBasisVectors(const Vector3 &right, const Vector3 &up);
	static void CreateFromBasisVectors(const Vector3 &right, const Vector3 &up, Quaternion &result);
	static Quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll);
	static void CreateFromYawPitchRoll(float yaw, float pitch, float roll, Quaternion &result);
	static void Divide(const Quaternion &q1, const Quaternion &q2, Quaternion &result);
	static float Dot(const Quaternion &q1, const Quaternion &q2);
	static void Dot(const Quaternion &q1, const Quaternion &q2, float &result);
	static Quaternion Inverse(const Quaternion &value);
	static void Inverse(const Quaternion &value, Quaternion &result);
	static Quaternion Lerp(const Quaternion &q1, const Quaternion &q2, float amount);
	static void Lerp(const Quaternion &q1, const Quaternion &q2, float amount, Quaternion &result);
	static void Multiply(const Quaternion &q, float scalar, Quaternion &result);
	static void Multiply(const Quaternion &q1, const Quaternion &q2, Quaternion &result);
	static Quaternion Slerp(const Quaternion &q1, const Quaternion &q2, float amount);
	static void Slerp(const Quaternion &q1, const Quaternion &q2, float amount, Quaternion &result);
	static void Subtract(const Quaternion &q1, const Quaternion &q2, Quaternion &result);
	static Quaternion Negate(const Quaternion &value);
	static void Negate(const Quaternion &value, Quaternion &result);
	static Quaternion Normalize(const Quaternion &value);
	static void Normalize(const Quaternion &value, Quaternion &result);

	void Conjugate();
	float Length();
	float LengthSquared();
	void Normalize();

	Quaternion operator+= (const Quaternion &op2);
	Quaternion operator-= (const Quaternion &op2);
	Quaternion operator*= (float scalar);
	Quaternion operator*= (const Quaternion &op2);
	Quaternion operator/= (float divisor);
protected:
private:
};

Quaternion operator+ (const Quaternion &op1, const Quaternion &op2);
Quaternion operator- (const Quaternion &op1, const Quaternion &op2);
Quaternion operator- (const Quaternion &op1);
Quaternion operator* (const Quaternion &op1, const Quaternion &op2);
Quaternion operator* (const Quaternion &op1, float op2);
Vector3 operator* (const Quaternion &op1, const Vector3 &op2);
Quaternion operator/ (const Quaternion &op1, const Quaternion &op2);

}
