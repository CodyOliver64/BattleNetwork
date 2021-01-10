#include "Projectile.h"
#include "TextureHolder.h"
#include <iostream>

Projectile::Projectile()
{
	m_ProjectileTexture = TextureHolder::GetTexture("graphics/spell_wave.png");
	m_ProjectileSprite.setTexture(m_ProjectileTexture);
	m_ProjectileSprite.setTextureRect(IntRect(0, 0, 41, 46));
	m_ProjectileSprite.setScale(sf::Vector2f(4.f, 4.f));

	waveBuffer.loadFromFile("sounds/wave.ogg");
	waveSound.setBuffer(waveBuffer);
	waveSound.setVolume(1.5f);
}

Sprite Projectile::getProjectileSprite()
{
	return m_ProjectileSprite;
}

Vector2f Projectile::getPosition()
{
	return  m_ProjectileSprite.getPosition();
}

void Projectile::Launch(float x, float y)
{
	m_ProjectileSprite.setPosition(sf::Vector2f(x, y));
	isActive = true;
	waveSound.play();
}

bool Projectile::Update(int frameCounter)
{
	if (!isActive)
		return false;

	float currentXPos = m_ProjectileSprite.getPosition().x;
	float currentYPos = m_ProjectileSprite.getPosition().y;


	if (frameCounter == 960 || frameCounter == 1080 || frameCounter == 1200 || frameCounter == 1320 || frameCounter == 1440 || frameCounter == 1960 || frameCounter == 2080 || frameCounter == 2200 || frameCounter == 2320 || frameCounter == 2440 || frameCounter == 2960 || frameCounter == 3080 || frameCounter == 3200 || frameCounter == 3320 || frameCounter == 3440 || frameCounter == 3960 || frameCounter == 4080 || frameCounter == 4200 || frameCounter == 4320 || frameCounter == 4440 || frameCounter == 4960 || frameCounter == 5080 || frameCounter == 5200 || frameCounter == 5320 || frameCounter == 5440 || frameCounter == 5960 || frameCounter == 6080 || frameCounter == 6200 || frameCounter == 6320 || frameCounter == 6440 || frameCounter == 6960 || frameCounter == 7080 || frameCounter == 7200 || frameCounter == 7320 || frameCounter == 7440 || frameCounter == 7960 || frameCounter == 8080 || frameCounter == 8200 || frameCounter == 8320 || frameCounter == 8440 || frameCounter == 8960 || frameCounter == 9080 || frameCounter == 9200 || frameCounter == 9320 || frameCounter == 9440)
	{
		currentXPos = currentXPos - 190;

		if (currentXPos <= -245)
		{
			isActive = false;
			return true;
		}
		m_ProjectileSprite.setPosition(sf::Vector2f(currentXPos, currentYPos));
		waveSound.play();
	}

	return false;
}

bool Projectile::UpdateCannonFire(int frameCounter, int attackStart)
{
	if (!isActive)
		return false;

	float currentXPos = m_ProjectileSprite.getPosition().x;
	float currentYPos = m_ProjectileSprite.getPosition().y;


	if ((frameCounter - attackStart) % 120  == 0)
	{
		currentXPos = currentXPos - 190;

		if (currentXPos <= -245)
		{
			isActive = false;
			return true;
		}
		m_ProjectileSprite.setPosition(sf::Vector2f(currentXPos, currentYPos));
		waveSound.play();
	}

	return false;
}