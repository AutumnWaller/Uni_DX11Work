#include "Collision.h"

using namespace Vector;

Collision::Collision(Transform* _transform)
{
	_pTransform = _transform;
}

bool Collision::CollisionCheck(Vector3 _position, float _radius)
{
	Vector3 dist = Vector3::Abs(_position - _pTransform->GetPosition());
	float sumRadii = _radius + boundRadius;

	if (dist.x > sumRadii)
		return false;
	if (dist.y > sumRadii)
		return false;
	if (dist.z > sumRadii)
		return false;
	return true;
}

void Collision::SetRadius(float _radius)
{
	boundRadius = _radius;
}

Collision::~Collision()
{
}
