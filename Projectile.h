#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Projectile
{

public:
	Projectile();

	Sprite m_ProjectileSprite;
	Texture m_ProjectileTexture;

	SoundBuffer waveBuffer;
	Sound waveSound;

	bool isActive;

	Sprite getProjectileSprite();
	void Launch(float x, float y);
	bool Update(int frameCounter);
	bool UpdateCannonFire(int frameCounter, int attackStart);

	Vector2f getPosition();
};
