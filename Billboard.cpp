#include "Billboard.h"



Billboard::Billboard()
{
	_pModelPath = "Models/billboard.obj";
	type = StaticStructs::BILLBOARD;
	invertTexCoords = true;
}


Billboard::~Billboard()
{
}
