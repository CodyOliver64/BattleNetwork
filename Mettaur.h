#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Projectile.h"
#include "Enemy.h"

using namespace sf;

class Mettaur : public Enemy
{
public:

	Mettaur(int id);
	
	void MoveEnemy(int frame);

	void ChangeAnimation(int num);

	void Attack(int frameCounter);
};