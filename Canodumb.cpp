#include "Canodumb.h"
#include "TextureHolder.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h> 

Canodumb::Canodumb(int id)
{
	m_EnemyTexture = TextureHolder::GetTexture("graphics/canodumb_atlas.png");
	m_EnemySprite.setTexture(m_EnemyTexture);
	m_EnemySprite.setTextureRect(IntRect(25, 0, 45, 58));
	m_EnemySprite.setScale(sf::Vector2f(4.f, 4.f));
	m_EnemySprite.setPosition(sf::Vector2f(855.f, 270.f - (140 * id))); //FIXME - hard coded start positions for 2 enemies, update to be random
	currentEnemyPos.x = 855.f;
	currentEnemyPos.y = 270.f - (140 * id);

	m_HitTexture = TextureHolder::GetTexture("graphics/spell_bullet_hit.png");
	m_HitSprite.setTexture(m_HitTexture);
	m_HitSprite.setTextureRect(IntRect(30, 0, 30, 24));
	m_HitSprite.setScale(sf::Vector2f(4.f, 4.f));
	m_HitSprite.setPosition(sf::Vector2f(currentEnemyPos.x + 45, currentEnemyPos.y + 80));

	shockwave.m_ProjectileTexture = TextureHolder::GetTexture("graphics/canodumb_atlas.png");
	shockwave.m_ProjectileSprite.setTexture(shockwave.m_ProjectileTexture);
	shockwave.m_ProjectileSprite.setTextureRect(IntRect(0, 180, 41, 46));

	shockwave.waveBuffer.loadFromFile("sounds/guard_hit.ogg");
	shockwave.waveSound.setBuffer(shockwave.waveBuffer);

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

void Canodumb::ChangeAnimation(int num)
{
	if (num == 1)
		m_EnemySprite.setTextureRect(IntRect(70, 0, 45, 58));
	if (num == 2)
		m_EnemySprite.setTextureRect(IntRect(115, 0, 45, 58));
	if (num == 3)
		m_EnemySprite.setTextureRect(IntRect(160, 0, 45, 58));
	if (num == 0)
		m_EnemySprite.setTextureRect(IntRect(25, 0, 45, 58));
}

void Canodumb::Attack(int frameCounter, float playerRow)
{
	if (!isAlive)
		return;

	if (currentEnemyPos.y == playerRow && !recentAttack && currentCounter < 9400)
	{
		enteredLOS = true;
		currentCounter = frameCounter;
	}

	if (enteredLOS)
	{
		// Begin enemy attack animation (FIXME - frame rate independence)

		if (frameCounter == currentCounter)
		{
			ChangeAnimation(1);
			recentAttack = true;
		}
		
		else if (frameCounter == currentCounter + 70)
		{
			ChangeAnimation(2);
		}
		else if (frameCounter == currentCounter + 140)
		{
			ChangeAnimation(3);

			// Launch projectile
			shockwave.Launch(currentEnemyPos.x - 170, currentEnemyPos.y + 30);
			shockwave.isActive = true;
		}
		else if (frameCounter == currentCounter + 210)
		{
			ChangeAnimation(0);
		}
		else if (frameCounter == currentCounter + 600)
		{
			ChangeAnimation(0);
			enteredLOS = false;
			recentAttack = false;
		}
	}
}