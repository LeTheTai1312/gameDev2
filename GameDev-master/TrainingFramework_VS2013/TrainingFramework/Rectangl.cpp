#include "stdafx.h"
#include "Rectangl.h"


Rectangl::~Rectangl()
{
}
Rectangl::Rectangl() {
	
	
}
void Rectangl::SetGiatri(int x, int y, int width, int height, int id) {
	this->m_iX = x;
	this->m_iY = y;
	this->m_iHeight = height;
	this->m_iWidth = width;
	this->id = id;
}
void Rectangl::Update(float x, float y) {
	
}