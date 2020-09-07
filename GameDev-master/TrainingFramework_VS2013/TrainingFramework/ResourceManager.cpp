#include "stdafx.h"
#include "ResourceManager.h"
#include<stdio.h>

using namespace std;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	for (int i = 0; i < modelsNum; i++) {
		glDeleteBuffers(1, &models[i].vboId);
		glDeleteBuffers(1, &models[i].iboId);
	}
	delete[] models;
	delete[] TD_Textures;
	delete[] cube_Textures;
	delete[] shader;
}

void ResourceManager::loadResource(char* l) {
	loadElementAnim("../Resources/sprites (1).txt");
	int modelNum, modelID; char modelLink[100];
	int TDTextureNum, TDTextureID; char TDTextureLink[100];
	int cubeTextureNum, cubeTextureID; char cubeTextureLink[100], tiling[100];
	int shaderNum, shaderID; char shaderVSLink[260], shaderFSLink[260];
	FILE* file;
	file = fopen(l, "r");
	fscanf(file, "#Models: %d\n", &modelNum);
	this->modelsNum = modelNum;
	models = new model[modelNum];
	for (int i = 0; i < modelNum; i++) {
		fscanf(file, "ID %d\n", &modelID);
		fscanf(file, "FILE %s\n", modelLink);
		models[modelID].init(modelLink);
	}
	fscanf(file, "#2D Textures: %d\n", &TDTextureNum);
	TD_Textures = new Texture[TDTextureNum];
	for (int i = 0; i < TDTextureNum; i++) {
		fscanf(file, "ID %d\n", &TDTextureID);
		fscanf(file, "FILE %s\n", TDTextureLink);
		fscanf(file, "TILING %s\n", tiling);
		TD_Textures[TDTextureID].loadTexture2D(TDTextureLink);
		tilingTD[TDTextureID] = tiling;
	}
	fscanf(file, "#Cube Textures: %d\n", &cubeTextureNum);
	cube_Textures = new Texture[1];
	// Generate a texture object
	glGenTextures(1, &cube_Textures[0].cubeTextureID);
	// Bind the texture object
	glBindTexture(GL_TEXTURE_CUBE_MAP, cube_Textures[0].cubeTextureID);
	for (int i = 0; i < cubeTextureNum; i++) {
		fscanf(file, "ID %d\n", &cubeTextureID);
		fscanf(file, "FILE %s\n", cubeTextureLink);
		fscanf(file, "TILING %s\n", tiling);
		GLint width, height, bpp;
		char* imageData = LoadTGA(cubeTextureLink, &width, &height, &bpp);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		cube_Textures[0].cubePixels.push_back(cubeTextureLink);
		//cube_Textures[cubeTextureID].loadCubeTexture(cubeTextureLink);
		//cube_Textures[cubeTextureID].loadTexture(cubeTextureLink);
		tilingCube[cubeTextureID] = tiling;
	}
	//cube_Textures[0].loadCubeTexture();

	fscanf(file, "#Shaders: %d\n", &shaderNum);
	shader = new Shaders[shaderNum];
	for (int i = 0; i < shaderNum; i++) {
		fscanf(file, "ID %d\n", &shaderID);
		fscanf(file, "VS %s\n", shaderVSLink);
		fscanf(file, "FS %s\n", shaderFSLink);
		memcpy(shader[shaderID].fs, shaderFSLink, 100);
		memcpy(shader[shaderID].vs, shaderVSLink, 100);
		shader[shaderID].Init(shaderVSLink, shaderFSLink);
		//cout << shader[shaderID].fs;
	}
	fclose(file);
}

void ResourceManager::loadElementAnim(char* l)
{
	int index, num;
	float a, b, c, d, e, f, g;
	FILE* file;

	file = fopen(l, "r");
	fscanf(file, "Num: %d\n", &num);
	for (int i = 0; i < num; i++) {
		fscanf(file, "%d. %f,%f,%f,%f,%f,%f,%f\n", &index, &a, &b, &c, &d, &e, &f, &g);
		vector<float> frame;
		frame.push_back(a);
		frame.push_back(b);
		frame.push_back(c);
		frame.push_back(d);
		frame.push_back(e);
		frame.push_back(f);
		frame.push_back(g);
		frames.push_back(frame);
	}
	fclose(file);
}

void ResourceManager::free() {
	delete[] models;
	delete[] TD_Textures;
	delete[] cube_Textures;
	delete[] shader;
}