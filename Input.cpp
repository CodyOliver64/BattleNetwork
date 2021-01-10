#include "Engine.h"

void Engine::input(int frame)
{
	Event event;

	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			// Quit game button
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				m_Window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::A))
			{
				player.handleInput(frame);
			}
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				player.Shoot();
			}
		}
		if (event.type == Event::KeyReleased)
		{
			if (event.key.code == Keyboard::Space)
			{
				player.NoShoot();
			}
		}
	}
	
}