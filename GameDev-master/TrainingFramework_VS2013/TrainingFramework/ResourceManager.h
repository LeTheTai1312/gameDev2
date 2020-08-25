#pragma once
#include "../Utilities/utilities.h"
#include "Texture.h"
#include "Shaders.h"
#include "model.h"
#include <vector>
#include<iostream>

class ResourceManager
{
public:

	//std::vector <model*> models;
	//std::vector <Texture*> TD_Textures;
	char* tilingTD[100];
	//std::vector <Texture*> cube_Textures;
	char* tilingCube[100];
	//std::vector <Shaders*> shader;
	int modelsNum;
	model* models;
	Texture* TD_Textures;
	Texture* cube_Textures;
	Shaders* shader;
	vector<vector<float>> frames;

	void loadResource(char* l);
	void loadElementAnim(char* l);
	void free();

	ResourceManager();
	~ResourceManager();

private:

};
