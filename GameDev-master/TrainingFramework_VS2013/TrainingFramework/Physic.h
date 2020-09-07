#pragma once
#include "Rectangl.h"
#include "Cricle.h"
class Physic
{
public:
	bool checkCoRec(Rectangl rec, Circle cir);
	bool checkCoCirCir(Circle cir1, Circle cir2);
	bool checkColRecRec(Rectangl rec1, Rectangl rec2);
};

