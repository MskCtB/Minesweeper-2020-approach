#include "Game.h"

int main()
{
	int Window_Size = (static_cast<int>(CUBE) + 2) * 8 + 2;
	sf::RenderWindow window(sf::VideoMode(Window_Size, Window_Size + CUBE), "Minesweeper", sf::Style::Close);
	window.setFramerateLimit(60);
	Game game;
	
	sf::Clock clock;
	float deltaTime = 0.0f;
	game.Set_Up();

	while (window.isOpen())
	{
		clock.restart();
		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				window.close();
			if (evnt.type == sf::Event::KeyReleased)
				if (evnt.key.code == sf::Keyboard::Space)
				{
					game.Clean();
					game.Set_Up();
					game.alive = true;
					game.UpdateString();
				}
			if (evnt.type == sf::Event::KeyPressed)
				if (evnt.key.code == sf::Keyboard::Escape)
					window.close();
			if (evnt.type == sf::Event::MouseButtonReleased)
			{
				mouse = sf::Mouse::getPosition(window);
				if (evnt.key.code == sf::Mouse::Left)
					game.LeftClick(mouse);
				if (evnt.key.code == sf::Mouse::Right)
					game.RightClick(mouse);
			}
		}
		game.Win();

		if (!game.alive)
			game.GameOver();

		window.clear(sf::Color(0,0,0));
		game.Draw(window);
		if (!game.alive)
			game.DrawGameOver(window);
		window.display();
	}

	return 0;
}