#pragma once

#include <string>
#include <fstream>
#include "Object.h"
#include "Grid.h"
#include "Cube.h"
#include "Ball.h"
#include "Car.h"
#include "Dome.h"
#include "Goal.h"
using namespace std;
class FileManager
{
public:
	FileManager();
	char* Read(char* filePath);
	void Write(char* filePath, char* data);
	void ConvertRBD(char* filePath, vector<Object*> *objects);
	void ConvertRBS(char* filePath, vector<string> *paths);
	Object* GetObjectFromString(string str);
	~FileManager();
};