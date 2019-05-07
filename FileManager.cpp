#include "FileManager.h"


FileManager::FileManager(){
	
}

char* FileManager::Read(char * filePath)
{
	fstream file = fstream(filePath, ios_base::in | ios_base::ate);
	streampos end = file.tellg();
	file.seekg(0, ios::beg);
	char* storage = new char[end];
	file.read(storage, end);
	file.close();
	return storage;
}



void FileManager::Write(char* filePath, char* data)
{
	fstream file = fstream(filePath, ios_base::out | ios_base::app);
	file.put('\n');
	for (int i = 0; i < strlen(data); i++) {
		file.put(data[i]);
	}
	file.put('\n');
	file.close();
}

void FileManager::ConvertRBD(char* filePath, vector<Object*> *objects)
{
	char* data = Read(filePath);
	int dataLength = strlen(data);
	Object* object = nullptr;
	char objName[3] = {' ', ' ', ' '};
	float posX = 0, posY = 0, posZ = 0, scaX = 1, scaY = 1, scaZ = 1, rotX = 0, rotY = 0, rotZ = 0;
	int tileW = 0, tileL = 0;
	for (int i = 0; i < dataLength; i) {
		if (data[i] == '~') {
			for (int j = 0; j < 3; j++) {
				objName[j] = data[(i + j) + 1];
			}
			i += 4;
			string str = objName;
			str.erase(3, string::npos);
			object = GetObjectFromString(str);
		}

		if (data[i] == '\n' || data[i] == ' ')
			i++;

		if (data[i] == 'p') {
			i += 2;
			string position = "";
			int counter = 0;
			for (int j = 0; j < 6; j++) {
				if (data[i + j] == '\n') {
					posZ = stof(position);
					i += j;
					break;
				}
				if (data[i + j] == ',')
				{
					switch (counter) {
					case 0:
						posX = stof(position);
						break;
					case 1:
						posY = stof(position);
						break;
					}
					i++;
					i += j;
					j = 0;
					counter++;
					position.clear();
				}
				position += data[i + j];
			}
			object->SetStartingPosition(Vector::Vector3(posX, posY, posZ));
			i++;
		}
		if (data[i] == 's') {
			i += 2;
			string scale = "";
			int counter = 0;
			for (int j = 0; j < 6; j++) {
				if (data[i + j] == '\n') {
					scaZ = stof(scale);
					i += j;
					break;
				}
				if (data[i + j] == ',')
				{
					switch (counter) {
					case 0:
						scaX = stof(scale);
						break;
					case 1:
						scaY = stof(scale);
						break;
					}
					i++;
					i += j;
					j = 0;
					counter++;
					scale.clear();
				}
				scale += data[i + j];
			}
			object->SetScale(scaX, scaY, scaZ);
			i++;

		}
		if (data[i] == 'r') {
			i += 2;
			string rotation = "";
			int counter = 0;
			for (int j = 0; j < 6; j++) {
				if (data[i + j] == '\n')
				{
					rotZ = stof(rotation);
					i += j;
					break;
				}
				if (data[i + j] == ',')
				{
					switch (counter) {
					case 0:
						rotX = stof(rotation);
						break;
					case 1:
						rotY = stof(rotation);
						break;
					}
					i++;
					i += j;
					j = 0;
					counter++;
					rotation.clear();
				}
				rotation += data[i + j];
			}
			object->SetRotation(rotX, rotY, rotZ);
			i++;
		}

		if (data[i] == 't') { //Grid-only tiling
			i += 2;
			string tiling = "";
			int counter = 0;
			for (int j = 0; j < 6; j++) {
				if (data[i + j] == '\n')
				{
					tileL = stof(tiling);
					i += j;
					break;
				}
				if (data[i + j] == ',')
				{
					if (counter == 0) {
						tileW = stof(tiling);
					}
					i++;
					i += j;
					j = 0;
					counter++;
					tiling.clear();
				}
				tiling += data[i + j];
			}
			i++;
			Grid *grid = (Grid*)object;
			grid->SetSize(tileW, tileL);
			object = grid;
		}


		if (object) {
			objects->emplace_back(object);
			i++;
			if (data[i] != '~')
				return;
		}
	}
}

void FileManager::ConvertRBS(char * filePath, vector<string> *paths)
{
	char* data = Read(filePath);
	string value;
	for (int i = 0; i < strlen(data); i++) {
		if (data[i] == ';')
			break;
		if (data[i] == '\n') {
			paths->emplace_back(value);
			value = "";
		}
		else
			value += data[i];
	}
}


Object* FileManager::GetObjectFromString(string str) {
	if (str == "Car") 
		return new Car();
	if (str == "Bal")
		return new Ball();
	if (str == "Dom")
		return new Dome();
	if (str == "Grd")
		return new Grid();
	if (str == "Goa")
		return new Goal();
	//Goal posts
	return nullptr;
}

FileManager::~FileManager()
{
}
