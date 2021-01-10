#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Enemy.h"

using namespace sf;

class Player
{
public:
	Sprite m_PlayerSprite;
	Texture m_PlayerTexture;

	Sprite m_BusterFireSprite;
	Texture m_BusterFireTexture;

	Font healthFont;
	Text healthText;

	Vector2f currentPlayerPos;
	int moveCounter = 0;
	bool canMove = false;
	bool canShoot = false;
	bool showBusterFire = false;

	bool recentHit = false;
	int frameLastHit = 0;

	float health = 70.f;
	
	Enemy *currentEnemies[3];

	SoundBuffer busterBuffer;
	Sound busterSound;

	SoundBuffer deadBuffer;
	Sound deadSound;

	SoundBuffer hurtBuffer;
	Sound hurtSound;

	Player();

	void handleInput(int frame);
	void Shoot();
	void NoShoot();

	Sprite getPlayerSprite();
	Sprite getBusterFireSprite();
	bool getShowBusterFire();
	bool checkBusterHit();
	void checkPlayerHit(int frameCounter);
	Text getHealthText();
	Vector2f getPlayerPos();

};