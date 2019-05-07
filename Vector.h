#pragma once
#include <math.h>
#include <cmath>
#include <DirectXMath.h>

namespace Vector {
	class Vector3
	{
	public:
		float x, y, z;
	public:
		static void Vector3::ToXMFLOAT3(DirectX::XMFLOAT3* destination, Vector3 v);


		Vector3 operator=(const Vector3 a) {
			return Vector3(this->x = a.x, this->y = a.y, this->z = a.z);
		}

		Vector3 operator+(const Vector3 a) {
			return Vector3(this->x + a.x, this->y + a.y, this->z + a.z);
		}

		Vector3 operator+=(const Vector3 a) {
			return Vector3(this->x += a.x, this->y += a.y, this->z += a.z);
		}

		Vector3 operator-(const Vector3 a) {
			return Vector3(this->x - a.x, this->y - a.y, this->z - a.z);
		}

		Vector3 operator-(const float a) {
			return Vector3(a - this->x, a - this->y, a - this->z);
		}

		Vector3 operator*(const Vector3 a) {
			return Vector3(this->x * a.x, this->y * a.y, this->z * a.z);
		}

		Vector3 operator*(const int a) {
			return Vector3(this->x * a, this->y * a, this->z * a);
		}

		Vector3 operator*(const float a) {
			return Vector3(this->x * a, this->y * a, this->z * a);
		}

		Vector3 operator*(const double a) {
			return Vector3(this->x * a, this->y * a, this->z * a);
		}

		Vector3 operator/(const Vector3 a) {
			return Vector3(this->x / a.x, this->y / a.y, this->z / a.z);
		}

		Vector3 operator/(const int a) {
			return Vector3(this->x / a, this->y / a, this->z / a);
		}

		Vector3 operator/(const float a) {
			return Vector3(this->x / a, this->y / a, this->z / a);
		}

		Vector3 operator/(const double a) {
			return Vector3(this->x / a, this->y / a, this->z / a);
		}

		Vector3 Sqr(Vector3 a) {
			return a * a;
		}

		static int Sqr(int a) {
			return a * a;
		}

		static Vector3 Abs(Vector3 a) {
			return Vector3(abs(a.x), abs(a.y), abs(a.z));
		}

		static float Dot(Vector3 a, Vector3 b, float angle) { return Magnitude(a) * Magnitude(b) * cos(angle); };
		static double Dot(Vector3 a, Vector3 b, double angle) { return Magnitude(a) * Magnitude(b) * cos(angle); };
		static float Dot(Vector3 a, Vector3 b) { return (a.x * b.x) + (a.y * b.y); };
		static Vector3 Cross(Vector3 a, Vector3 b) { return Vector3((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x)); };
		static float Magnitude(Vector3 a) { return sqrt(Sqr(a.x) + Sqr(a.y) + Sqr(a.z)); };

		Vector3(float _X, float _Y, float _Z);
		Vector3(float n = 0);
		~Vector3();
	};
}