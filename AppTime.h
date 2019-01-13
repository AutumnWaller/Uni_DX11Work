#pragma once

#include <windows.h>
class AppTime
{
public:
	static float DeltaTime();
	static void Timer(float deltaTime, float timeInSeconds, float &changeVar, float constVar);
};