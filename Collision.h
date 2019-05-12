#pragma once
#include "Vector.h"
#include "Transform.h"
class Transform;
class Collision
{
private:
	Transform* _pTransform = nullptr;
	float boundRadius = 0;
public:
	Collision(Transform* _transform);
	bool CollisionCheck(Vector::Vector3 _position, float _radius);
	void SetRadius(float _radius);
	float GetRadius() { return boundRadius; };
	~Collision();
};

