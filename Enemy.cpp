#include "Enemy.h"
#include "TextureHolder.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h> 



Sprite Enemy::getSprite()
{
	return m_EnemySprite;
}

Sprite Enemy::getHitSprite()
{
	return m_HitSprite;
}

Text Enemy::getHealthText()
{
	return healthText;
}

Vector2f Enemy::getEnemyPos()
{
	return currentEnemyPos;
}

bool Enemy::getShowHitSprite()
{
	return showHitSprite;
}

Projectile Enemy::getProjectile()
{
	return shockwave;
}


void Enemy::TakeDamage(int damage)
{
	health = health - damage;
	std::stringstream d;
	d << "" << health;
	healthText.setString(d.str());
	showHitSprite = true;
	hurtSound.play();
}

bool Enemy::CheckForDeath(int frameCounter)
{
	if (health <= 0 && !recentDeath)
	{
		recentDeath = true;
		allowMovement = false;

		m_EnemySprite.setTextureRect(IntRect(-10, 55, 54, 58));

		frameOfDeath = frameCounter;
		isAlive = false;
		deadSound.play();
		return true;
	}
	else if (recentDeath)
	{
		if (frameCounter > frameOfDeath + 175 || (frameCounter > frameOfDeath - 9824 && frameOfDeath > 9824))
		{
			m_EnemySprite.setPosition(sf::Vector2f(80000, 80000)); //Remove from screen when dead, keep enemy objects for battle results screen later on
			currentEnemyPos.x = 80000;
			currentEnemyPos.y = 80000;
			m_HitSprite.setPosition(sf::Vector2f(80000, 80000));
			healthText.setPosition(80000, 80000);
		}
		return false;
	}
	return false;
}
