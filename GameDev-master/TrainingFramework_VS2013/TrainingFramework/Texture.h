#pragma once
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include <vector>
#include<iostream>
#include<stdio.h>
#include<string.h>

class Texture
{
public:
	
	GLint width, height, bpp;
	int w, h, nrChanels;
	GLuint cubeTextureID;
	unsigned int textureID;
	std::vector <char*> cubePixels;
	/*{
		"../Resources/Textures/right.tga",
		"../Resources/Textures/left.tga",
		"../Resources/Textures/top.tga",
		"../Resources/Textures/bottom.tga",
		"../Resources/Textures/front.tga",
		"../Resources/Textures/back.tga"
	};*/
	//void loadTexture(char* l);
	void loadTexture2D(char* l);
	void loadCubeTexture();
	void loadImageData(char* l, int i);
	Texture();
	~Texture();

private:

};
