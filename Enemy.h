#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Projectile.h"

using namespace sf;

class Enemy
{
public:
	Sprite m_EnemySprite;
	Texture m_EnemyTexture;

	Sprite m_HitSprite;
	Texture m_HitTexture;


	float health = 50.f;
	int enemyNum;
	int frameOfDeath;
	bool showHitSprite = false;
	bool allowMovement = true;
	bool isAlive = true;
	bool showShockwave = false;
	bool recentDeath = false;

	Vector2f currentEnemyPos;

	Font healthFont;
	Text healthText;

	SoundBuffer hurtBuffer;
	Sound hurtSound;

	SoundBuffer deadBuffer;
	Sound deadSound;

	Projectile shockwave;

	Enemy *allyEnemies[2]; // make dynamic to hold more allies

	Sprite getSprite();
	Text getHealthText();
	Vector2f getEnemyPos();
	bool getShowHitSprite();
	Sprite getHitSprite();
	Projectile getProjectile();

	void TakeDamage(int damage);

	bool CheckForDeath(int frameCounter);
};