#pragma once
#include "Object.h"
class Skybox : public Object
{
	ID3D11Texture2D* textures[6];
public:
	Skybox();
	~Skybox();
};

