#pragma once
#include "../Utilities/utilities.h"
#include "Animation2D.h"

class BotFish: public Animation2D
{
public:
	BotFish();
	~BotFish();
	void bite();
	void disapear();
	void scoreScene(int);
	void update_animation_move_boss(float);

private:

};
