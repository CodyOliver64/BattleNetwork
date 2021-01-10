#include "Mettaur.h"
#include "TextureHolder.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h> 

Mettaur::Mettaur(int id)
{
	m_EnemyTexture = TextureHolder::GetTexture("graphics/mettaur.png");
	m_EnemySprite.setTexture(m_EnemyTexture);
	m_EnemySprite.setTextureRect(IntRect(0, 0, 54, 58));
	m_EnemySprite.setScale(sf::Vector2f(4.f, 4.f));
	m_EnemySprite.setPosition(sf::Vector2f(855.f - (190 * id), 270.f + (140 * id))); //FIXME - hard coded start positions for 2 enemies, update to be random
	currentEnemyPos.x = 855.f - (190 * id);
	currentEnemyPos.y = 270.f + (140 * id);

	m_HitTexture = TextureHolder::GetTexture("graphics/spell_bullet_hit.png");
	m_HitSprite.setTexture(m_HitTexture);
	m_HitSprite.setTextureRect(IntRect(30, 0, 30, 24));
	m_HitSprite.setScale(sf::Vector2f(4.f, 4.f));
	m_HitSprite.setPosition(sf::Vector2f(currentEnemyPos.x + 45, currentEnemyPos.y + 80));

	healthFont.loadFromFile("fonts/mmbnthick_regular.ttf");

	healthText.setFont(healthFont);
	healthText.setCharacterSize(50);
	healthText.setFillColor(Color::White);
	healthText.setPosition(currentEnemyPos.x + 545, currentEnemyPos.y + 230);

	std::stringstream s;
	s << "" << health;
	healthText.setString(s.str());

	hurtBuffer.loadFromFile("sounds/hurt.ogg");
	hurtSound.setBuffer(hurtBuffer);
	hurtSound.setVolume(1.5f);

	deadBuffer.loadFromFile("sounds/explode_once.ogg");
	deadSound.setBuffer(deadBuffer);
	deadSound.setVolume(1.5f);

	enemyNum = id;
}

void Mettaur::ChangeAnimation(int num)
{
	if (num == 1)
		m_EnemySprite.setTextureRect(IntRect(162, 0, 54, 58));
	if (num == 2)
		m_EnemySprite.setTextureRect(IntRect(320, 0, 54, 58));
	if (num == 3)
		m_EnemySprite.setTextureRect(IntRect(432, 0, 54, 58));
	if (num == 0)
		m_EnemySprite.setTextureRect(IntRect(0, 0, 54, 58));
}

void Mettaur::MoveEnemy(int frame)
{
	if (allowMovement == false)
		return;

	srand(time(NULL) * (enemyNum + 1));
	int randomMove = (rand() % 4) + 1;

	//Move Up
	if (frame % 300 == 0 && randomMove == 1 && currentEnemyPos.y > 130)
	{
		currentEnemyPos.y = currentEnemyPos.y - 140;

		// Check if the square is already occupied 
		for (Enemy *ally : allyEnemies)
		{
			if (currentEnemyPos.x == ally->currentEnemyPos.x && currentEnemyPos.y == ally->currentEnemyPos.y && ally->isAlive)
			{
				currentEnemyPos.y = currentEnemyPos.y + 140;
				return;
			}
		}

		m_EnemySprite.setPosition(currentEnemyPos.x, currentEnemyPos.y);
		m_HitSprite.setPosition(currentEnemyPos.x + 45, currentEnemyPos.y + 80);
		healthText.setPosition(currentEnemyPos.x + 545, currentEnemyPos.y + 230);
	}
	// Move Down
	if (frame % 300 == 0 && randomMove == 2 && currentEnemyPos.y < 410)
	{
		currentEnemyPos.y = currentEnemyPos.y + 140;

		for (Enemy *ally : allyEnemies)
		{
			if (currentEnemyPos.x == ally->currentEnemyPos.x && currentEnemyPos.y == ally->currentEnemyPos.y && ally->isAlive)
			{
				currentEnemyPos.y = currentEnemyPos.y - 140;
				return;
			}
		}

		m_EnemySprite.setPosition(currentEnemyPos.x, currentEnemyPos.y);
		m_HitSprite.setPosition(currentEnemyPos.x + 45, currentEnemyPos.y + 80);
		healthText.setPosition(currentEnemyPos.x + 545, currentEnemyPos.y + 230);
	}
	// Move Right
	if (frame % 300 == 0 && randomMove == 3 && currentEnemyPos.x < 855)
	{
		currentEnemyPos.x = currentEnemyPos.x + 190;

		for (Enemy *ally : allyEnemies)
		{
			if (currentEnemyPos.x == ally->currentEnemyPos.x && currentEnemyPos.y == ally->currentEnemyPos.y && ally->isAlive)
			{
				currentEnemyPos.x = currentEnemyPos.x - 190;
				return;
			}
		}

		m_EnemySprite.setPosition(currentEnemyPos.x, currentEnemyPos.y);
		m_HitSprite.setPosition(currentEnemyPos.x + 45, currentEnemyPos.y + 80);
		healthText.setPosition(currentEnemyPos.x + 545, currentEnemyPos.y + 230);
	}
	// Move Left
	if (frame % 300 == 0 && randomMove == 4 && currentEnemyPos.x > 475)
	{
		currentEnemyPos.x = currentEnemyPos.x - 190;

		for (Enemy *ally : allyEnemies)
		{
			if (currentEnemyPos.x == ally->currentEnemyPos.x && currentEnemyPos.y == ally->currentEnemyPos.y && ally->isAlive)
			{
				currentEnemyPos.x = currentEnemyPos.x + 190;
				return;
			}
		}

		m_EnemySprite.setPosition(currentEnemyPos.x, currentEnemyPos.y);
		m_HitSprite.setPosition(currentEnemyPos.x + 45, currentEnemyPos.y + 80);
		healthText.setPosition(currentEnemyPos.x + 545, currentEnemyPos.y + 230);
	}
}

void Mettaur::Attack(int frameCounter)
{
	if (!isAlive)
		return;

	// Begin enemy attack animation (FIXME - frame rate independence)
	if (frameCounter == 700 || frameCounter == 1700 || frameCounter == 2700 || frameCounter == 3700 || frameCounter == 4700 || frameCounter == 5700 || frameCounter == 6700 || frameCounter == 7700 || frameCounter == 8700)
	{
		ChangeAnimation(1);
		allowMovement = false;
	}
	else if (frameCounter == 770 || frameCounter == 1770 || frameCounter == 2770 || frameCounter == 3770 || frameCounter == 4770 || frameCounter == 5770 || frameCounter == 6770 || frameCounter == 7770 || frameCounter == 8770)
	{
		ChangeAnimation(2);
	}
	else if (frameCounter == 840 || frameCounter == 1840 || frameCounter == 2840 || frameCounter == 3840 || frameCounter == 4840 || frameCounter == 5840 || frameCounter == 6840 || frameCounter == 7840 || frameCounter == 8840)
	{
		ChangeAnimation(3);

		// Launch projectile
		shockwave.Launch(currentEnemyPos.x - 170, currentEnemyPos.y + 30);
		shockwave.isActive = true;
	}
	else if (frameCounter == 910 || frameCounter == 1910 || frameCounter == 2910 || frameCounter == 3910 || frameCounter == 4910 || frameCounter == 5910 || frameCounter == 6910 || frameCounter == 7910 || frameCounter == 8910)
	{
		allowMovement = true;
		ChangeAnimation(0);
	}
}