#include "stdafx.h"
#include "model.h"
#include "Globals.h"
#include <stdio.h>
#include <vector>
#define PI 3.141592653589
using namespace std;

model::model(const model& m)
{
	this->binormal = m.binormal;
	this->iboId = m.iboId;
	this->indices = m.indices;
	this->n = m.n;
	this->normal = m.normal;
	this->nr = m.nr;
	this->num_indice = m.num_indice;
	this->num_vertice = m.num_vertice;
	this->pos = m.pos;
	this->tangent = m.tangent;
	this->uv = m.uv;
	this->vboId = m.vboId;
	this->vertices = m.vertices;
}

model::model()
{
}

model::~model()
{
}

void model::init(char* l) { 
	int i;
	float posx, posy, posz, normx, normy, normz, bnx, bny, bnz, tgtx, tgty, tgtz, uvx, uvy;
	FILE *file;
	file = fopen(l, "r");
	fscanf(file, "NrVertices: %d\n", &num_vertice);
	vertices = new Vertex[num_vertice];
	for (int j = 0; j < num_vertice; j++) {
		fscanf(file, "%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\n",
			&i, &posx, &posy, &posz, &normx, &normy, &normz, &bnx, &bny, &bnz, &tgtx, &tgty, &tgtz, &uvx, &uvy);
			vertices[i].pos.x = posx; vertices[i].pos.y = posy; vertices[i].pos.z = posz;
			vertices[i].normal.x = normx; vertices[i].normal.y = normy; vertices[i].normal.z = normz;
			vertices[i].binormal.x = bnx; vertices[i].binormal.y = bny; vertices[i].binormal.z = bnz;
			vertices[i].tangent.x = tgtx; vertices[i].tangent.y = tgty; vertices[i].tangent.z = tgtz;
			vertices[i].uv.x = uvx; vertices[i].uv.y = uvy;
	}
	fscanf(file, "NrIndices: %d\n", &num_indice);
	indices = new int[num_indice];
	for (int j = 0; j < num_indice/3; j++) {
		fscanf(file, " %d.    %d,    %d,    %d\n", &nr, &indices[3*j+0], &indices[3*j+1], &indices[3*j+2]);
	}
	fclose(file);

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*(num_vertice), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*num_indice, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glEnable(GL_DEPTH_TEST);
	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	//texture.loadTexture(m);

	//return myShaders.Init(vs, fs);
}

void model::init2D(char* l)
{
	
}

void model::free() {
	delete[] vertices;
	delete[] indices;
}


