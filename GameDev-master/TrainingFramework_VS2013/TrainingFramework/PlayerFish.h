#pragma once
#include "../Utilities/utilities.h"
#include "Animation2D.h"


class PlayerFish: public Animation2D
{
public:
	PlayerFish();
	~PlayerFish();
	void bite();
	void disapear();
	void scoreScene(int);
	void update_animation_move_player(int x, int y);
private:
};
