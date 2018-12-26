#include "AppTime.h"

float AppTime::DeltaTime()
{
	static float t = 0.0f;
	static float prevTime = t;
	static DWORD dwTimeStart = 0;
	DWORD dwTimeCur = GetTickCount();

	if (dwTimeStart == 0)
		dwTimeStart = dwTimeCur;

	t = (dwTimeCur - dwTimeStart) / 1000.0f;
	float deltaTime = (t - prevTime);
	prevTime = t;
	return deltaTime;
}

void AppTime::Timer(float deltaTime, float timeInSeconds, float &changeVar, float constVar)
{
	static float timer = 0;
	if (timer <= 0) {
		changeVar += constVar;
		timer = timeInSeconds;
	}
	else
		timer -= deltaTime;
}
