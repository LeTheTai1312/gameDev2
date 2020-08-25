#include "stdafx.h"
#include "Cricle.h"

Circle::~Circle() {

}
Circle::Circle() {
	

}
void Circle::Update(float x, float y) {

}
void Circle::Render() {
}

void Circle::SetGiaTri(int x, int y, int id, int radius)
{
	this->m_iX = x;
	this->m_iY = y;
	this->m_iRadius = radius;
	this->id = id;
}
