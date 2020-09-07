#pragma once
#include "../Utilities/utilities.h"
#include "Vertex.h"
#include "model.h"
#include "Texture.h"
#include <vector>
#include <math.h>
#include "Matran.h"

class Objects
{
public:

	Matrix scaleMatrix;
	Matrix rotationMatrix;
	Matrix translationMatrix;
	Matrix Rx, Ry, Rz;
	Matrix wMatrix, vMatrix, pMatrix, wvpMatrix;
	float sxw, syw, szw, rxw, ryw, rzw, txw, tyw, tzw;
	void set_matrix(Matrix v);
	void set_world(float s, float rx, float ry, float rz, float tx, float ty, float tz);
	void set_wvp(Matrix v);
	void draw();
	//void draw2D(Matrix Vp);

	void update_world(float s, float x, float y, float z, float tx, float ty, float tz);
	int textureNum, cubeTextureNum;
	int models;
	int *texture;
	int *cubeTexture;
	Shaders shaders;
	//char vs, fs;



	Objects();
	~Objects();

private:

};
