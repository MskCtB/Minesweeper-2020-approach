#include "Game.h"
#include "Menu.h"



int main()
{
	int Window_Size_X = (static_cast<int>(CUBE) + 2) * 16 + 2;
	int Window_Size_Y = (static_cast<int>(CUBE) + 2) * 12 + 2 + CUBE;
	sf::RenderWindow window(sf::VideoMode(Window_Size_X, Window_Size_Y + 2.0f), "Minesweeper", sf::Style::Close);
	window.setFramerateLimit(60);
	Game game;
	Menu menu(window);
	int gameMode = 0;

	//VIEWS
	sf::View view0(sf::FloatRect(0, 0, menu.GetSizes()[0].x, menu.GetSizes()[0].y));
	sf::View view1(sf::FloatRect(0, 0, menu.GetSizes()[1].x, menu.GetSizes()[1].y));
	sf::View view2(sf::FloatRect(0, 0, menu.GetSizes()[2].x, menu.GetSizes()[2].y));
	sf::View view = view1;
	
	sf::Clock clock;
	float deltaTime = 0.0f;
	game.Set_Up(gameMode);

	//INITIAL VIEW
	window.setView(view);

	while (window.isOpen())
	{
		if (menu.MenuState())
			window.setView(view);

		clock.restart();
		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
				window.close();
			if (evnt.type == sf::Event::KeyReleased)
			{
				if (evnt.key.code == sf::Keyboard::Space)
				{
					game.Clean();
					game.Set_Up(gameMode);
					game.alive = true;
					game.UpdateString();
				}
				if (evnt.key.code == sf::Keyboard::Tilde)
					game.ToggleDev();
				if (evnt.key.code == sf::Keyboard::Escape)
				{
					window.setView(view1);
					menu.TurnOn();
				}
			}
			if (evnt.type == sf::Event::MouseButtonReleased)
			{
				mouse = sf::Mouse::getPosition(window);
				if (evnt.key.code == sf::Mouse::Left && !menu.MenuState())
					game.LeftClick(mouse);
				if (evnt.key.code == sf::Mouse::Right && !menu.MenuState())
					game.RightClick(mouse);
				if (evnt.key.code == sf::Mouse::Left && menu.MenuState())
					switch (menu.MouseClick(mouse, window))
					{
					case 0:
						gameMode = 0;
						window.setView(view0);
						game.Clean();
						game.Set_Up(gameMode);
						game.alive = true;
						game.UpdateString();
						break;
					case 1:
						gameMode = 1;
						window.setView(view1);
						game.Clean();
						game.Set_Up(gameMode);
						game.alive = true;
						game.UpdateString();
						break;
					case 2:
						gameMode = 2;
						window.setView(view2);
						game.Clean();
						game.Set_Up(gameMode);
						game.alive = true;
						game.UpdateString();
						break;
					}
			}
		}
		game.Win();

		if (!game.alive)
			game.GameOver();

		window.clear(sf::Color(0,0,0));
		if (!menu.MenuState())
		{
			game.Draw(window);
			game.DevDraw(window);
			if (!game.alive)
				game.DrawGameOver(window);
		}
		else if (menu.MenuState())
		{
			menu.Draw(window);
		}
		window.display();
	}

	return 0;
}