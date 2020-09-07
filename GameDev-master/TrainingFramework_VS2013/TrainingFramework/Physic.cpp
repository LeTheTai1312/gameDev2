#include "stdafx.h"
#include "Physic.h"

bool Physic::checkCoRec(Rectangl rec, Circle cir)
{
    return false;
}

bool Physic::checkCoCirCir(Circle cir1, Circle cir2)
{
	float x = (cir1.m_iX - cir2.m_iX) * (cir1.m_iX - cir2.m_iX) + (cir1.m_iY - cir2.m_iY) * (cir1.m_iY - cir2.m_iY);
	float d = (cir1.m_iRadius + cir2.m_iRadius)* (cir1.m_iRadius + cir2.m_iRadius);
	if (x < d) return true;
    return false;
}

bool Physic::checkColRecRec(Rectangl Rect1, Rectangl Rect2)
{
	int DistSubX = (Rect1.m_iX + (Rect1.m_iWidth / 2)) - (Rect2.m_iX + (Rect2.m_iWidth) / 2);
	if (DistSubX < 0) DistSubX = DistSubX * (-1);

	int DistW = (Rect1.m_iWidth + Rect2.m_iWidth) / 2;

	int DistSubY = (Rect1.m_iY + (Rect1.m_iHeight / 2)) - (Rect2.m_iY + (Rect2.m_iHeight) / 2);
	if (DistSubY < 0) DistSubY = DistSubY * (-1);

	int DistH = (Rect1.m_iHeight + Rect2.m_iHeight) / 2;

	if (DistSubX <= DistW && DistSubY <= DistH)
		return true;
    return false;
}
