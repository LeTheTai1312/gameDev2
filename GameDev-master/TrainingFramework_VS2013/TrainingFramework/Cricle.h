#pragma once


class Circle 
{
public:
	int m_iX;
	int m_iY;
	int id;
	int m_iRadius;
	void Update(float x, float y);
	void Render();
	void SetGiaTri(int x, int y, int id, int m_iRadius);
	Circle();
	~Circle();
};

