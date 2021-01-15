#include "Player.h"
#include "TextureHolder.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "Engine.h"

Player::Player()
{
	m_PlayerTexture = TextureHolder::GetTexture("graphics/navi_starman_atlas.png");
	m_PlayerSprite.setTexture(m_PlayerTexture);
	m_PlayerSprite.setTextureRect(IntRect(0, 145, 55, 70));
	m_PlayerSprite.setScale(sf::Vector2f(3.f, 3.f));
	m_PlayerSprite.setPosition(sf::Vector2f(-105.f, 270.f));
	currentPlayerPos.x = -105.f;
	currentPlayerPos.y = 270.f;

	healthFont.loadFromFile("fonts/mmbnthick_regular.ttf");

	healthText.setFont(healthFont);
	healthText.setCharacterSize(50);
	healthText.setFillColor(Color::White);
	healthText.setPosition(440.f, 500);

	std::stringstream s;
	s << "" << health;
	healthText.setString(s.str());

	m_BusterFireTexture = TextureHolder::GetTexture("graphics/buster_shoot.png");
	m_BusterFireSprite.setTexture(m_BusterFireTexture);
	m_BusterFireSprite.setTextureRect(IntRect(0, 0, 24, 13));
	m_BusterFireSprite.setScale(sf::Vector2f(3.f, 3.f));
	m_BusterFireSprite.setPosition(sf::Vector2f(50.f, 335.f));

	busterBuffer.loadFromFile("sounds/pew.ogg");
	busterSound.setBuffer(busterBuffer);
	busterSound.setVolume(1.5f);

	deadBuffer.loadFromFile("sounds/deleted.ogg");
	deadSound.setBuffer(deadBuffer);
	deadSound.setVolume(1.5f);

	hurtBuffer.loadFromFile("sounds/explode_once.ogg");
	hurtSound.setBuffer(hurtBuffer);
	hurtSound.setVolume(1.8f);


}

void Player::handleInput(int frame)
{
	if (!canMove)
		return;
	
	if (Keyboard::isKeyPressed(Keyboard::W) && currentPlayerPos.y > 130)
	{
		currentPlayerPos.y = currentPlayerPos.y - 140;
		m_PlayerSprite.setPosition(currentPlayerPos.x, currentPlayerPos.y);
		m_BusterFireSprite.setPosition(currentPlayerPos.x + 155, currentPlayerPos.y + 65);
		healthText.setPosition(currentPlayerPos.x + 550, currentPlayerPos.y + 230);

		return;
	}

	if (Keyboard::isKeyPressed(Keyboard::S) && currentPlayerPos.y < 360)
	{
		currentPlayerPos.y = currentPlayerPos.y + 140;
		m_PlayerSprite.setPosition(currentPlayerPos.x, currentPlayerPos.y);
		m_BusterFireSprite.setPosition(currentPlayerPos.x + 155, currentPlayerPos.y + 65);
		healthText.setPosition(currentPlayerPos.x + 550, currentPlayerPos.y + 230);

		return;
	}

	if (Keyboard::isKeyPressed(Keyboard::A) && currentPlayerPos.x > -105)
	{
		currentPlayerPos.x = currentPlayerPos.x - 190;
		m_PlayerSprite.setPosition(currentPlayerPos.x, currentPlayerPos.y);
		m_BusterFireSprite.setPosition(currentPlayerPos.x + 155, currentPlayerPos.y + 65);
		healthText.setPosition(currentPlayerPos.x + 550, currentPlayerPos.y + 230);

		return;
	}

	if (Keyboard::isKeyPressed(Keyboard::D) && currentPlayerPos.x < 255)
	{
		currentPlayerPos.x = currentPlayerPos.x + 190;
		m_PlayerSprite.setPosition(currentPlayerPos.x, currentPlayerPos.y);
		m_BusterFireSprite.setPosition(currentPlayerPos.x + 155, currentPlayerPos.y + 65);
		healthText.setPosition(currentPlayerPos.x + 550, currentPlayerPos.y + 230);

		return;
	}
}

void Player::Shoot()
{
	if (!canShoot)
		return;
	
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		m_PlayerSprite.setTextureRect(IntRect(0, 0, 55, 70));
		showBusterFire = true;
		busterSound.play();
		checkBusterHit();
	}
}

void Player::NoShoot()
{
	if (!canShoot)
		return;
	
	m_PlayerSprite.setTextureRect(IntRect(0, 145, 55, 70));
	showBusterFire = false;
	
	for (Enemy *enemy : currentEnemies)
		enemy->showHitSprite = false;
}

bool Player::checkBusterHit()
{
	std::vector< Enemy* > tempArray;
	int closestPoint = 10000;
	int enemyHit = -1;
	for (Enemy *enemy : currentEnemies)
	{
		if (currentPlayerPos.y == enemy->getEnemyPos().y)
		{
			tempArray.push_back(enemy);
		}
	}

	if (tempArray.empty())
		return false;

	for (int i = 0; i < tempArray.size(); i++)
	{
		if (tempArray[i]->getEnemyPos().x < closestPoint)
		{
			closestPoint = tempArray[i]->getEnemyPos().x;
			enemyHit = i;
		}
	}
	
	tempArray[enemyHit]->TakeDamage(2);
	return true;
}

void Player::checkPlayerHit(int frameCounter)
{
	for (Enemy *enemy : currentEnemies)
	{

		Vector2f enemyAttackPos = enemy->shockwave.getPosition(); //update to loop through all enemies

		if (currentPlayerPos.x == enemyAttackPos.x - 30 && currentPlayerPos.y == enemyAttackPos.y - 30 && enemy->shockwave.isActive && !recentHit)
		{
			health = health - 10;
			hurtSound.play();
			std::stringstream d;
			d << "" << health;
			healthText.setString(d.str());

			recentHit = true;
			canMove = false;
			canShoot = false;

			m_PlayerSprite.setTextureRect(IntRect(420, 280, 55, 70));

			frameLastHit = frameCounter;
		}
		else if (recentHit)
		{
			if (frameCounter > frameLastHit + 175 || (frameCounter > frameLastHit - 9824 && frameLastHit > 9824))
			{
				recentHit = false;
				m_PlayerSprite.setTextureRect(IntRect(0, 145, 55, 70));
				canMove = true;
				canShoot = true;
			}
		}
	}
}

Sprite Player::getPlayerSprite()
{
	return m_PlayerSprite;
}

Sprite Player::getBusterFireSprite()
{
	return m_BusterFireSprite;
}

bool Player::getShowBusterFire()
{
	return showBusterFire;
}

Text Player::getHealthText()
{
	return healthText;
}

Vector2f Player::getPlayerPos()
{
	return currentPlayerPos;
}