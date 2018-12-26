#pragma once

#include <windows.h>
static class AppTime
{
public:
	static float DeltaTime();
	static void Timer(float deltaTime, float timeInSeconds, float &changeVar, float constVar);
};