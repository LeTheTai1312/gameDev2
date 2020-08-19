#pragma once
#include "../Utilities/utilities.h"

class Shaders 
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260], vs[100];
	char fileFS[260], fs[100];
	GLint positionAttribute;
	GLint colorAttribute;
	GLint uvAttribute;
	//int iTextureLoc;
	GLint WVP;
	int* m_texture;
	
	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};