#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Projectile.h"
#include "Enemy.h"

using namespace sf;

class Canodumb : public Enemy
{
public:

	bool enteredLOS = false;
	bool recentAttack = false;
	int currentCounter = 0;
	
	Canodumb(int id);

	void ChangeAnimation(int num);

	void Attack(int frameCounter, float playerRow);
};
