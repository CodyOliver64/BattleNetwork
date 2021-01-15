#pragma once

#include "TextureHolder.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Mettaur.h"
#include "Canodumb.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace sf;

class Engine
{
private:
	TextureHolder th;

	RenderWindow m_Window;
	View m_MainView;
	View m_BGMainView;
	View m_HudView;

	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;

	// Grid Sprites
	Texture m_PlayerGridTex;
	Texture m_EnemyGridTex;


	Sprite m_PlayerGrid1;
	Sprite m_PlayerGrid2;
	Sprite m_PlayerGrid3;
	Sprite m_PlayerGrid4;
	Sprite m_PlayerGrid5;
	Sprite m_PlayerGrid6;
	Sprite m_PlayerGrid7;
	Sprite m_PlayerGrid8;
	Sprite m_PlayerGrid9;

	Sprite m_EnemyGrid1;
	Sprite m_EnemyGrid2;
	Sprite m_EnemyGrid3;
	Sprite m_EnemyGrid4;
	Sprite m_EnemyGrid5;
	Sprite m_EnemyGrid6;
	Sprite m_EnemyGrid7;
	Sprite m_EnemyGrid8;
	Sprite m_EnemyGrid9;

	Texture m_BattleStartTex;
	Sprite m_BattleStartSprite;

	Texture m_WinTex;
	Sprite m_WinSprite;

	Texture m_LossTex;
	Sprite m_LossSprite;

	Font thanksFont;
	Text thanksText;

	Music battleMusic;

	int frameCounter;
	int numEnemiesAlive;
	bool showIntro = true;
	bool showWin = false;
	bool showLoss = false;
	bool endGame = false;
	bool increasedFrame = false;

	void input(int frame);
	void update(float dtAsSeconds);
	void draw();
	void SetGrid();
	void UpdateGrid(bool lastSquare, bool lastSquare2);
	void StartBattle();
	bool CheckGameWon();
	bool CheckGameLost();
	void SetAssets();
public:
	Engine();

	Player player;
	
	Mettaur enemy1;// Fix later to be a random array of enemies
	Mettaur enemy2;
	Canodumb enemy3;

	void run();
};
