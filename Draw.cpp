#include "Engine.h"

void Engine::draw()
{
	if (endGame)
	{
		m_Window.clear(Color::White);

		m_Window.setView(m_BGMainView);
		m_Window.draw(m_BackgroundSprite);
		m_Window.draw(thanksText);
		m_Window.display();
	}
	
	else
	{
		m_Window.clear(Color::White);

		m_Window.setView(m_BGMainView);
		m_Window.draw(m_BackgroundSprite);
		m_Window.setView(m_MainView);

		//draw level here
		m_Window.draw(m_PlayerGrid4);
		m_Window.draw(m_PlayerGrid5);
		m_Window.draw(m_PlayerGrid6);
		m_Window.draw(m_PlayerGrid1);
		m_Window.draw(m_PlayerGrid2);
		m_Window.draw(m_PlayerGrid3);
		m_Window.draw(m_PlayerGrid7);
		m_Window.draw(m_PlayerGrid8);
		m_Window.draw(m_PlayerGrid9);

		m_Window.draw(m_EnemyGrid4);
		m_Window.draw(m_EnemyGrid5);
		m_Window.draw(m_EnemyGrid6);
		m_Window.draw(m_EnemyGrid1);
		m_Window.draw(m_EnemyGrid2);
		m_Window.draw(m_EnemyGrid3);
		m_Window.draw(m_EnemyGrid7);
		m_Window.draw(m_EnemyGrid8);
		m_Window.draw(m_EnemyGrid9);

		//draw characters here
		if (enemy1.shockwave.isActive)
		{
			m_Window.draw(enemy1.shockwave.getProjectileSprite());
		}

		if (enemy2.shockwave.isActive)
		{
			m_Window.draw(enemy2.shockwave.getProjectileSprite());
		}

		if (enemy3.shockwave.isActive)
		{
			m_Window.draw(enemy3.shockwave.getProjectileSprite());
		}

		m_Window.draw(player.getPlayerSprite());
		m_Window.draw(enemy1.getSprite());
		m_Window.draw(enemy2.getSprite());
		m_Window.draw(enemy3.getSprite());

		if (player.getShowBusterFire())
		{
			m_Window.draw(player.getBusterFireSprite());
		}

		if (enemy1.getShowHitSprite())
		{
			m_Window.draw(enemy1.getHitSprite());
		}

		if (enemy2.getShowHitSprite())
		{
			m_Window.draw(enemy2.getHitSprite());
		}

		if (enemy3.getShowHitSprite())
		{
			m_Window.draw(enemy3.getHitSprite());
		}



		//draw Hud here
		m_Window.setView(m_HudView);
		m_Window.draw(enemy1.getHealthText());
		m_Window.draw(enemy2.getHealthText());
		m_Window.draw(enemy3.getHealthText());
		m_Window.draw(player.getHealthText());

		if (showIntro)
			m_Window.draw(m_BattleStartSprite);

		if (showWin)
			m_Window.draw(m_WinSprite);

		if (showLoss)
			m_Window.draw(m_LossSprite);



		m_Window.display();
	}
}