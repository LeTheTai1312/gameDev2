#pragma once
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "Texture.h"
#include "Shaders.h"
#include <vector>
#include<iostream>

using namespace std;

class model
{
public:
	GLuint vboId, iboId;
	Vertex* vertices;
	int* indices;
	float pos, normal, binormal, tangent, uv;
	int n, nr, num_vertice, num_indice;
	void init(char* l);
	void init2D(char* l);
	void free();



	model(const model&);
	model();
	~model();

private:

};

