#include "Engine.h"

Engine::Engine()
	:
	enemy1(0), enemy2(1), enemy3(1)
{
	Vector2f resolution;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(resolution.x, resolution.y), "Battle Network", Style::Resize);

	m_MainView.setSize(resolution);
	m_HudView.reset(FloatRect(0, 0, resolution.x, resolution.y));

	m_BackgroundTexture = TextureHolder::GetTexture("graphics/Space-Background-Tiled.png");
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	m_BattleStartTex = TextureHolder::GetTexture("graphics/battle_start.png");
	m_BattleStartSprite.setTexture(m_BattleStartTex);
	m_BattleStartSprite.setScale(sf::Vector2f(5.f, 5.f));
	m_BattleStartSprite.setPosition(sf::Vector2f(600, 400));

	m_WinTex = TextureHolder::GetTexture("graphics/enemy_deleted.png");
	m_WinSprite.setTexture(m_WinTex);
	m_WinSprite.setScale(sf::Vector2f(5.f, 5.f));
	m_WinSprite.setPosition(sf::Vector2f(600, 400));

	m_LossTex = TextureHolder::GetTexture("graphics/game_over.png");
	m_LossSprite.setTexture(m_LossTex);
	m_LossSprite.setScale(sf::Vector2f(5.f, 5.f));
	m_LossSprite.setPosition(sf::Vector2f(530, 400));

	thanksFont.loadFromFile("fonts/FunkyJunk.ttf");

	thanksText.setFont(thanksFont);
	thanksText.setCharacterSize(90);
	thanksText.setFillColor(Color::White);
	thanksText.setPosition(0, 400);
	std::stringstream s;
	s << "    Thanks for Playing! \n Stay Tuned For Updates \n \n   Press Escape To Exit...";
	thanksText.setString(s.str());

	battleMusic.openFromFile("sounds/loop_theme.ogg");
	battleMusic.setLoop(true);
	battleMusic.setVolume(1.5f);

	SetGrid();

	// Set player/enemy references (FIXME - make dynamic)
	player.currentEnemies[0] = &enemy1;
	player.currentEnemies[1] = &enemy2;
	player.currentEnemies[2] = &enemy3;
	numEnemiesAlive = 3;

	enemy1.allyEnemies[0] = &enemy2;
	enemy1.allyEnemies[1] = &enemy3;

	enemy2.allyEnemies[0] = &enemy1;
	enemy2.allyEnemies[1] = &enemy3;

	enemy3.allyEnemies[0] = &enemy1;
	enemy3.allyEnemies[1] = &enemy2;

}

void Engine::run()
{
	StartBattle();
	
	while (m_Window.isOpen())
	{
		CheckGameWon();
		CheckGameLost();
		
		if (endGame)
		{
			input(frameCounter);
			draw();
		}

		else
		{
			frameCounter++;
			if (frameCounter == 10000)
				frameCounter = 0;

			input(frameCounter);

			if (enemy1.CheckForDeath(frameCounter))
				numEnemiesAlive--;
			if (enemy2.CheckForDeath(frameCounter))
				numEnemiesAlive--;
			if (enemy3.CheckForDeath(frameCounter))
				numEnemiesAlive--;


			if (frameCounter > 0 && frameCounter < 1000 || frameCounter > 2000 && frameCounter < 3000 || frameCounter > 4000 && frameCounter < 5000 || frameCounter > 6000 && frameCounter < 7000 || frameCounter > 8000 && frameCounter < 9000)
				enemy1.Attack(frameCounter);
			else
				enemy2.Attack(frameCounter);
			enemy3.Attack(frameCounter, player.getPlayerPos().y);

			bool lastSquare1 = enemy1.shockwave.Update(frameCounter);
			bool lastSquare2 = enemy2.shockwave.Update(frameCounter);
			enemy3.shockwave.UpdateCannonFire(frameCounter, enemy3.currentCounter);

			player.checkPlayerHit(frameCounter);


			enemy1.MoveEnemy(frameCounter);
			enemy2.MoveEnemy(frameCounter);

			UpdateGrid(lastSquare1, lastSquare2);

			//update(dtAsSeconds);
			draw();
		}
	}
}

void Engine::StartBattle()
{
	int frame = 750;

	battleMusic.play();

	while (frame > 0)
	{
		draw();
		input(frameCounter);
		frame--;
	}

	showIntro = false;
	player.canMove = true;
	player.canShoot = true;
}

bool Engine::CheckGameWon()
{
	if (numEnemiesAlive == 0 && !endGame)
	{
		showWin = true;
		int frame = 750;

		player.canMove = false;
		player.canShoot = false;

		while (frame > 0)
		{
			draw();
			input(frameCounter);
			frame--;
		}

		endGame = true;
		battleMusic.openFromFile("sounds/loop_overworld.ogg");
		battleMusic.play();
		m_BackgroundTexture = TextureHolder::GetTexture("graphics/hqdefault.jpg");
		return true;
	}
	return false;
}

bool Engine::CheckGameLost()
{
	if (player.health <= 0 && !endGame)
	{
		showLoss = true;
		player.deadSound.play();
		int frame = 750;

		player.canMove = false;
		player.canShoot = false;

		while (frame > 0)
		{
			draw();
			input(frameCounter);
			frame--;
		}

		endGame = true;
		battleMusic.openFromFile("sounds/loop_overworld.ogg");
		battleMusic.play();
		m_BackgroundTexture = TextureHolder::GetTexture("graphics/hqdefault.jpg");
		return true;
	}
	return false;
}

void Engine::UpdateGrid(bool lastSquare1, bool lastSquare2)
{
	int x1 = enemy1.shockwave.getProjectileSprite().getPosition().x;
	int y1 = enemy1.shockwave.getProjectileSprite().getPosition().y;

	int x2 = enemy2.shockwave.getProjectileSprite().getPosition().x;
	int y2 = enemy2.shockwave.getProjectileSprite().getPosition().y;

	// Update bottom row
	if ((x1 == 685 && y1 == 440) || (x2 == 685 && y2 == 440))
		m_EnemyGrid8.setTextureRect(IntRect(40, 30, 40, 30));
	else
		m_EnemyGrid8.setTextureRect(IntRect(0, 0, 40, 30));

	if ((x1 == 495 && y1 == 440) || (x2 == 495 && y2 == 440))
		m_EnemyGrid7.setTextureRect(IntRect(40, 30, 40, 30));
	else
		m_EnemyGrid7.setTextureRect(IntRect(0, 0, 40, 30));

	if ((x1 == 305 && y1 == 440) || (x2 == 305 && y2 == 440))
		m_PlayerGrid9.setTextureRect(IntRect(40, 30, 40, 30));
	else
		m_PlayerGrid9.setTextureRect(IntRect(0, 0, 40, 30));

	if ((x1 == 115 && y1 == 440) || (x2 == 115 && y2 == 440))
		m_PlayerGrid8.setTextureRect(IntRect(40, 30, 40, 30));
	else
		m_PlayerGrid8.setTextureRect(IntRect(0, 0, 40, 30));

	if ((x1 == -75 && y1 == 440 && !lastSquare1 && enemy1.shockwave.isActive) || (x2 == -75 && y2 == 440 && !lastSquare2 && enemy2.shockwave.isActive))
		m_PlayerGrid7.setTextureRect(IntRect(40, 30, 40, 30));
	else
		m_PlayerGrid7.setTextureRect(IntRect(0, 0, 40, 30));

	// Update middle row
	if ((x1 == 685 && y1 == 300) || (x2 == 685 && y2 == 300))
		m_EnemyGrid5.setTextureRect(IntRect(40, 30, 40, 30));
	else
		m_EnemyGrid5.setTextureRect(IntRect(0, 0, 40, 30));

	if ((x1 == 495 && y1 == 300) || (x2 == 495 && y2 == 300))
		m_EnemyGrid4.setTextureRect(IntRect(40, 30, 40, 30));
	else
		m_EnemyGrid4.setTextureRect(IntRect(0, 0, 40, 30));

	if ((x1 == 305 && y1 == 300) || (x2 == 305 && y2 == 300))
		m_PlayerGrid6.setTextureRect(IntRect(40, 30, 40, 30));
	else
		m_PlayerGrid6.setTextureRect(IntRect(0, 0, 40, 30));

	if ((x1 == 115 && y1 == 300) || (x2 == 115 && y2 == 300))
		m_PlayerGrid5.setTextureRect(IntRect(40, 30, 40, 30));
	else
		m_PlayerGrid5.setTextureRect(IntRect(0, 0, 40, 30));

	if ((x1 == -75 && y1 == 300 && !lastSquare1 && enemy1.shockwave.isActive) || (x2 == -75 && y2 == 300 && !lastSquare2 && enemy2.shockwave.isActive))
		m_PlayerGrid4.setTextureRect(IntRect(40, 30, 40, 30));
	else
		m_PlayerGrid4.setTextureRect(IntRect(0, 0, 40, 30));

	// Update top row
	if ((x1 == 685 && y1 == 160) || (x2 == 685 && y2 == 160))
		m_EnemyGrid2.setTextureRect(IntRect(40, 30, 40, 30));
	else
		m_EnemyGrid2.setTextureRect(IntRect(0, 0, 40, 30));

	if ((x1 == 495 && y1 == 160) || (x2 == 495 && y2 == 160))
		m_EnemyGrid1.setTextureRect(IntRect(40, 30, 40, 30));
	else
		m_EnemyGrid1.setTextureRect(IntRect(0, 0, 40, 30));

	if ((x1 == 305 && y1 == 160) || (x2 == 305 && y2 == 160))
		m_PlayerGrid3.setTextureRect(IntRect(40, 30, 40, 30));
	else
		m_PlayerGrid3.setTextureRect(IntRect(0, 0, 40, 30));

	if ((x1 == 115 && y1 == 160) || (x2 == 115 && y2 == 160))
		m_PlayerGrid2.setTextureRect(IntRect(40, 30, 40, 30));
	else
		m_PlayerGrid2.setTextureRect(IntRect(0, 0, 40, 30));

	if ((x1 == -75 && y1 == 160 && !lastSquare1 && enemy1.shockwave.isActive) || (x2 == -75 && y2 == 160 && !lastSquare2 && enemy2.shockwave.isActive))
		m_PlayerGrid1.setTextureRect(IntRect(40, 30, 40, 30));
	else
		m_PlayerGrid1.setTextureRect(IntRect(0, 0, 40, 30));
}


void Engine::SetGrid()
{
	// Set Player Grid
	m_PlayerGridTex = TextureHolder::GetTexture("graphics/tile_atlas_blue.png");
	m_EnemyGridTex = TextureHolder::GetTexture("graphics/tile_atlas_red.png");

	m_PlayerGrid1.setTexture(m_PlayerGridTex);
	m_PlayerGrid1.setTextureRect(IntRect(0, 0, 40, 30));
	m_PlayerGrid1.setScale(sf::Vector2f(5.f, 5.f));
	m_PlayerGrid1.setPosition(sf::Vector2f(-100.f, 255.f));

	m_PlayerGrid2.setTexture(m_PlayerGridTex);
	m_PlayerGrid2.setTextureRect(IntRect(0, 0, 40, 30));
	m_PlayerGrid2.setScale(sf::Vector2f(5.f, 5.f));
	m_PlayerGrid2.setPosition(sf::Vector2f(90.f, 255.f));

	m_PlayerGrid3.setTexture(m_PlayerGridTex);
	m_PlayerGrid3.setTextureRect(IntRect(0, 0, 40, 30));
	m_PlayerGrid3.setScale(sf::Vector2f(5.f, 5.f));
	m_PlayerGrid3.setPosition(sf::Vector2f(280.f, 255.f));


	m_PlayerGrid4.setTexture(m_PlayerGridTex);
	m_PlayerGrid4.setTextureRect(IntRect(0, 0, 40, 30));
	m_PlayerGrid4.setScale(sf::Vector2f(5.f, 5.f));
	m_PlayerGrid4.setPosition(sf::Vector2f(-100.f, 400.f));

	m_PlayerGrid5.setTexture(m_PlayerGridTex);
	m_PlayerGrid5.setTextureRect(IntRect(0, 0, 40, 30));
	m_PlayerGrid5.setScale(sf::Vector2f(5.f, 5.f));
	m_PlayerGrid5.setPosition(sf::Vector2f(90.f, 400.f));

	m_PlayerGrid6.setTexture(m_PlayerGridTex);
	m_PlayerGrid6.setTextureRect(IntRect(0, 0, 40, 30));
	m_PlayerGrid6.setScale(sf::Vector2f(5.f, 5.f));
	m_PlayerGrid6.setPosition(sf::Vector2f(280.f, 400.f));

	m_PlayerGrid7.setTexture(m_PlayerGridTex);
	m_PlayerGrid7.setTextureRect(IntRect(0, 0, 40, 30));
	m_PlayerGrid7.setScale(sf::Vector2f(5.f, 5.f));
	m_PlayerGrid7.setPosition(sf::Vector2f(-100.f, 545.f));

	m_PlayerGrid8.setTexture(m_PlayerGridTex);
	m_PlayerGrid8.setTextureRect(IntRect(0, 0, 40, 30));
	m_PlayerGrid8.setScale(sf::Vector2f(5.f, 5.f));
	m_PlayerGrid8.setPosition(sf::Vector2f(90.f, 545.f));

	m_PlayerGrid9.setTexture(m_PlayerGridTex);
	m_PlayerGrid9.setTextureRect(IntRect(0, 0, 40, 30));
	m_PlayerGrid9.setScale(sf::Vector2f(5.f, 5.f));
	m_PlayerGrid9.setPosition(sf::Vector2f(280.f, 545.f));

	// Set Enemy Grid
	m_EnemyGrid1.setTexture(m_EnemyGridTex);
	m_EnemyGrid1.setTextureRect(IntRect(0, 0, 40, 30));
	m_EnemyGrid1.setScale(sf::Vector2f(5.f, 5.f));
	m_EnemyGrid1.setPosition(sf::Vector2f(470.f, 255.f));

	m_EnemyGrid2.setTexture(m_EnemyGridTex);
	m_EnemyGrid2.setTextureRect(IntRect(0, 0, 40, 30));
	m_EnemyGrid2.setScale(sf::Vector2f(5.f, 5.f));
	m_EnemyGrid2.setPosition(sf::Vector2f(660.f, 255.f));

	m_EnemyGrid3.setTexture(m_EnemyGridTex);
	m_EnemyGrid3.setTextureRect(IntRect(0, 0, 40, 30));
	m_EnemyGrid3.setScale(sf::Vector2f(5.f, 5.f));
	m_EnemyGrid3.setPosition(sf::Vector2f(850.f, 255.f));


	m_EnemyGrid4.setTexture(m_EnemyGridTex);
	m_EnemyGrid4.setTextureRect(IntRect(0, 0, 40, 30));
	m_EnemyGrid4.setScale(sf::Vector2f(5.f, 5.f));
	m_EnemyGrid4.setPosition(sf::Vector2f(470.f, 400.f));

	m_EnemyGrid5.setTexture(m_EnemyGridTex);
	m_EnemyGrid5.setTextureRect(IntRect(0, 0, 40, 30));
	m_EnemyGrid5.setScale(sf::Vector2f(5.f, 5.f));
	m_EnemyGrid5.setPosition(sf::Vector2f(660.f, 400.f));

	m_EnemyGrid6.setTexture(m_EnemyGridTex);
	m_EnemyGrid6.setTextureRect(IntRect(0, 0, 40, 30));
	m_EnemyGrid6.setScale(sf::Vector2f(5.f, 5.f));
	m_EnemyGrid6.setPosition(sf::Vector2f(850.f, 400.f));

	m_EnemyGrid7.setTexture(m_EnemyGridTex);
	m_EnemyGrid7.setTextureRect(IntRect(0, 0, 40, 30));
	m_EnemyGrid7.setScale(sf::Vector2f(5.f, 5.f));
	m_EnemyGrid7.setPosition(sf::Vector2f(470.f, 545.f));

	m_EnemyGrid8.setTexture(m_EnemyGridTex);
	m_EnemyGrid8.setTextureRect(IntRect(0, 0, 40, 30));
	m_EnemyGrid8.setScale(sf::Vector2f(5.f, 5.f));
	m_EnemyGrid8.setPosition(sf::Vector2f(660.f, 545.f));

	m_EnemyGrid9.setTexture(m_EnemyGridTex);
	m_EnemyGrid9.setTextureRect(IntRect(0, 0, 40, 30));
	m_EnemyGrid9.setScale(sf::Vector2f(5.f, 5.f));
	m_EnemyGrid9.setPosition(sf::Vector2f(850.f, 545.f));
}